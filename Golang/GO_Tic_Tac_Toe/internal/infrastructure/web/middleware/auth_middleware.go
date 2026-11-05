package middleware

import (
	"context"
	"net/http"
	"strings"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"

	"github.com/google/uuid"
)

type UserAuthenticator struct {
	jwt domain.JwtProvider
}

func NewUserAuthenticator(jwt domain.JwtProvider) *UserAuthenticator {
	return &UserAuthenticator{
		jwt: jwt,
	}
}

func (a *UserAuthenticator) Authenticate(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		if a.isPublicRoute(r.URL.Path, r.Method) {
			next.ServeHTTP(w, r)
			return
		}

		userID, err := a.authenticateRequest(r)
		if err != nil {
			http.Error(w, `{"error": "`+err.Error()+`}`, http.StatusUnauthorized)
			return
		}

		ctx := context.WithValue(r.Context(), "user_id", userID)
		next.ServeHTTP(w, r.WithContext(ctx))
	})
}

func (a *UserAuthenticator) authenticateRequest(r *http.Request) (uuid.UUID, error) {
	authHeader := r.Header.Get("Authorization")
	if authHeader == "" {
		return uuid.Nil, contracts.ErrHeaderMid
	}

	parts := strings.SplitN(authHeader, " ", 2)
	if len(parts) != 2 || parts[0] != "Bearer" {
		return uuid.Nil, contracts.ErrInvAuth
	}

	token := strings.TrimSpace(parts[1])
	if token == "" {
		return uuid.Nil, contracts.ErrInvAuth
	}

	if err := a.jwt.ValidateAccess(token); err != nil {
		return uuid.Nil, contracts.ErrInvalidCred
	}

	userID, err := a.jwt.GetUUID(token)
	if err != nil {
		return uuid.Nil, contracts.ErrInvalidCred
	}

	return userID, nil
}

func (a *UserAuthenticator) isPublicRoute(path, method string) bool {
	publicRoutes := map[string][]string{
		"/api/auth/register":       {"POST"},
		"/api/auth/login":          {"POST"},
		"/api/auth/refresh/access": {"POST"},
	}

	allowedMethods, exists := publicRoutes[path]
	if !exists {
		return false
	}

	for _, m := range allowedMethods {
		if m == method {
			return true
		}
	}
	return false
}

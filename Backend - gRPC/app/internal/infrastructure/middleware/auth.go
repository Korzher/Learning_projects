package middleware

import (
	"apifromspec/internal/infrastructure/web/auth"
	"apifromspec/internal/infrastructure/web/utils"
	"net/http"
	"strings"
)

func AuthMiddleware(a *auth.Client) func(http.Handler) http.Handler {
	return func(next http.Handler) http.Handler {
		return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
			authHeader := r.Header.Get("Authorization")
			if authHeader == "" {
				utils.RespondJSON(w, http.StatusUnauthorized, "missing authorization header")
				return
			}

			parts := strings.Split(authHeader, " ")
			if len(parts) != 2 || strings.ToLower(parts[0]) != "bearer" {
				utils.RespondJSON(w, http.StatusUnauthorized, "invalid authorization header")
				return
			}

			ctx := r.Context()
			valid, err := a.VerifyToken(ctx, parts[1])
			if err != nil {
				utils.RespondJSON(w, http.StatusUnauthorized, "invalid authorization token")
				return
			}

			if !valid {
				utils.RespondJSON(w, http.StatusUnauthorized, "token is invalid or expired")
				return
			}
			next.ServeHTTP(w, r)
		})
	}
}

package handler

import (
	"apifromspec/internal/infrastructure/web/auth"
	"apifromspec/internal/infrastructure/web/utils"
	"apifromspec/internal/pkg"
	"encoding/json"
	"net/http"
	"strings"
)

type AuthHandler struct {
	client *auth.Client
}

func NewAuthHandler(client *auth.Client) *AuthHandler {
	return &AuthHandler{
		client: client,
	}
}

func (a *AuthHandler) Register(w http.ResponseWriter, r *http.Request) {
	var req pkg.RegisterRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}

	if req.Email == "" || req.Password == "" {
		utils.RespondJSON(w, http.StatusBadRequest, "email and password are required")
		return
	}

	ctx := r.Context()
	token, err := a.client.CreateUser(ctx, req.Email, req.FirstName, req.LastName, req.Phone, req.Password)
	if err != nil {
		utils.RespondJSON(w, http.StatusInternalServerError, err.Error())
		return
	}

	utils.RespondJSON(w, http.StatusCreated, map[string]string{
		"token": token,
	})
}

func (a *AuthHandler) Auth(w http.ResponseWriter, r *http.Request) {
	var req pkg.AuthRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}

	ctx := r.Context()
	token, err := a.client.Authenticate(ctx, req.Email, req.Password)
	if err != nil {
		utils.RespondJSON(w, http.StatusUnauthorized, "authentication failed")
		return
	}

	utils.RespondJSON(w, http.StatusOK, map[string]string{
		"token": token,
	})
}

func (a *AuthHandler) Reset(w http.ResponseWriter, r *http.Request) {
	var req pkg.ResetPasswordRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}

	ctx := r.Context()
	if err := a.client.ResetPassword(ctx, req.Email); err != nil {
		utils.RespondJSON(w, http.StatusInternalServerError, "reset failed")
		return
	}

	utils.RespondJSON(w, http.StatusOK, "password reset email sent")
}

func (a *AuthHandler) ChangePassword(w http.ResponseWriter, r *http.Request) {
	var req pkg.ChangePasswordRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}
	authHeader := r.Header.Get("Authorization")
	parts := strings.Split(authHeader, " ")
	if len(parts) != 2 || strings.ToLower(parts[0]) != "bearer" {
		utils.RespondJSON(w, http.StatusUnauthorized, "invalid token")
		return
	}
	token := parts[1]

	ctx := r.Context()
	if err := a.client.ChangePassword(ctx, token, req.OldPassword, req.NewPassword); err != nil {
		utils.RespondJSON(w, http.StatusInternalServerError, err.Error())
		return
	}
	utils.RespondJSON(w, http.StatusOK, "password changed")
}

func (a *AuthHandler) RegisterRoutes(mux *http.ServeMux) {
	mux.HandleFunc("POST /api/v1/register", a.Register)
	mux.HandleFunc("POST /api/v1/auth", a.Auth)
	mux.HandleFunc("POST /api/v1/reset", a.Reset)
	mux.HandleFunc("POST /api/v1/change", a.ChangePassword)
}

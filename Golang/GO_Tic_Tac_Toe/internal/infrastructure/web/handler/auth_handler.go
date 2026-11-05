package handler

import (
	"encoding/json"
	"net/http"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"
)

type AuthHandler struct {
	userService domain.UserService
}

func NewAuthHandler(userService domain.UserService) *AuthHandler {
	return &AuthHandler{
		userService: userService,
	}
}

func (h *AuthHandler) Register(w http.ResponseWriter, r *http.Request) {
	var req contracts.SignUpRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrInvalidReq})
		return
	}

	ctx := r.Context()
	if err := h.userService.Register(ctx, req); err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: err.Error()})
		return
	}

	respondJSON(w, http.StatusCreated, map[string]string{
		"message": "user registered successfully",
	})
}

func (h *AuthHandler) Login(w http.ResponseWriter, r *http.Request) {
	var req contracts.JwtRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrInvalidReq})
		return
	}
	ctx := r.Context()
	userID, err := h.userService.Login(ctx, req.Username, req.Password)
	if err != nil {
		respondJSON(w, http.StatusUnauthorized, contracts.ErrorResponse{
			Error: err.Error(),
		})
		return
	}

	respondJSON(w, http.StatusOK, contracts.JwtResponse{
		ID:           userID.ID.String(),
		TokenType:    "Bearer",
		AccessToken:  userID.AccessToken,
		RefreshToken: userID.RefreshToken,
	})
}

func (h *AuthHandler) RefreshAccessToken(w http.ResponseWriter, r *http.Request) {
	var req contracts.RefreshJwtRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrInvalidReq})
		return
	}

	ctx := r.Context()
	tokens, err := h.userService.RefreshAccessToken(ctx, req.RefreshToken)
	if err != nil {
		respondJSON(w, http.StatusUnauthorized, contracts.ErrorResponse{Error: err.Error()})
		return
	}

	response := contracts.JwtResponse{
		TokenType:    "Bearer",
		AccessToken:  tokens.AccessToken,
		RefreshToken: tokens.RefreshToken,
	}

	respondJSON(w, http.StatusOK, response)
}

func (h *AuthHandler) RefreshRefreshToken(w http.ResponseWriter, r *http.Request) {
	var req contracts.RefreshJwtRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrInvalidReq})
		return
	}

	ctx := r.Context()
	tokens, err := h.userService.RefreshRefreshToken(ctx, req.RefreshToken)
	if err != nil {
		respondJSON(w, http.StatusUnauthorized, contracts.ErrorResponse{Error: err.Error()})
		return
	}

	response := contracts.JwtResponse{
		TokenType:    "Bearer",
		AccessToken:  tokens.AccessToken,
		RefreshToken: tokens.RefreshToken,
	}

	respondJSON(w, http.StatusOK, response)
}

func (h *AuthHandler) RegisterRoutes(mux *http.ServeMux) {
	mux.HandleFunc("POST /api/auth/register", h.Register)
	mux.HandleFunc("POST /api/auth/login", h.Login)
	mux.HandleFunc("POST /api/auth/refresh/access", h.RefreshAccessToken)
	mux.HandleFunc("POST /api/auth/refresh/refresh", h.RefreshRefreshToken)
}

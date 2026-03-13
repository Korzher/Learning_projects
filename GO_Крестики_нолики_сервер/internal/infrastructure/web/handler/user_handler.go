package handler

import (
	"net/http"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"

	"github.com/google/uuid"
)

type UserHandler struct {
	userService domain.UserService
	jwt         domain.JwtProvider
}

func NewUserHandler(userService domain.UserService, jwt domain.JwtProvider) *UserHandler {
	return &UserHandler{
		userService: userService,
		jwt:         jwt,
	}
}

func (h *UserHandler) GetUser(w http.ResponseWriter, r *http.Request) {
	idStr := extractUserID(r.URL.Path)
	if idStr == "" {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrPlayerID})
		return
	}

	userID, err := uuid.Parse(idStr)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrParseID})
		return
	}

	ctx := r.Context()
	user, err := h.userService.GetUserByID(ctx, userID)
	if err != nil {
		respondJSON(w, http.StatusNotFound, contracts.ErrorResponse{Error: err.Error()})
		return
	}

	response := contracts.UserResponse{
		ID:       user.ID.String(),
		Username: user.Username,
	}

	respondJSON(w, http.StatusOK, response)
}

func (h *UserHandler) GetAllUsers(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()
	users, err := h.userService.GetAllUsers(ctx)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrFetch})
		return
	}

	response := make([]contracts.UserResponse, len(users))
	for i, user := range users {
		response[i] = contracts.UserResponse{
			ID:       user.ID.String(),
			Username: user.Username,
		}
	}

	respondJSON(w, http.StatusOK, response)
}

func (h *UserHandler) GetUserByToken(w http.ResponseWriter, r *http.Request) {
	token := extractToken(r.URL.Path)
	if token == "" {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrToken})
		return
	}

	err := h.jwt.ValidateAccess(token)
	if err != nil {
		respondJSON(w, http.StatusUnauthorized, contracts.ErrorResponse{Error: contracts.ErrInvalidToken})
		return
	}

	ID, err := h.jwt.GetUUID(token)
	if err != nil {
		respondJSON(w, http.StatusUnauthorized, contracts.ErrorResponse{Error: contracts.ErrParseID})
		return
	}

	ctx := r.Context()
	user, err := h.userService.GetUserByID(ctx, ID)
	if err != nil {
		respondJSON(w, http.StatusNotFound, contracts.ErrorResponse{Error: err.Error()})
		return
	}

	response := &contracts.UserResponse{
		ID:       user.ID.String(),
		Username: user.Username,
	}

	respondJSON(w, http.StatusOK, response)
}

func (h *UserHandler) RegisterRoutes(mux *http.ServeMux) {
	mux.HandleFunc("GET /api/users/{id}", h.GetUser)
	mux.HandleFunc("GET /api/users", h.GetAllUsers)
	mux.HandleFunc("GET /api/token/{token}", h.GetUserByToken)
}

func extractUserID(path string) string {
	prefix := "/api/users/"
	if len(path) < len(prefix) {
		return ""
	}
	return path[len(prefix):]
}

func extractToken(path string) string {
	prefix := "/api/token/"
	if len(path) < len(prefix) {
		return ""
	}
	return path[len(prefix):]
}

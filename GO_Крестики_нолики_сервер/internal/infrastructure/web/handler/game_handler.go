package handler

import (
	"encoding/json"
	"net/http"
	"strconv"
	"strings"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"
)

type GameHandler struct {
	service domain.GameService
}

func NewGameHandler(service domain.GameService) *GameHandler {
	return &GameHandler{service: service}
}

func (h *GameHandler) CreateGame(w http.ResponseWriter, r *http.Request) {
	game, err := h.service.CreateGame()
	if err != nil {
		respondJSON(w, http.StatusInternalServerError, contracts.ErrorResponse{Error: err.Error()})
		return
	}
	response := ToGameResponse(game)
	respondJSON(w, http.StatusCreated, response)
}

func (h *GameHandler) GetGame(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.Atoi(extractGameID(r.URL.Path))
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: "inlalid game ID"})
		return
	}

	game, err := h.service.GetGame(id)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: err.Error()})
		return
	}

	response := ToGameResponse(game)
	respondJSON(w, http.StatusOK, response)
}

func (h *GameHandler) MakeMove(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.Atoi(extractGameID(r.URL.Path))
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: "inlalid game ID"})
		return
	}

	var req contracts.MakeMoveRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: "invalid request body"})
		return
	}

	if req.Row < 0 || req.Row > 2 || req.Col < 0 || req.Col > 2 {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: "Invalid coordinates, must be 0-2"})
		return
	}

	game, err := h.service.MakeMove(id, req.Row, req.Col)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: err.Error()})
		return
	}
	response := ToGameResponse(game)
	respondJSON(w, http.StatusOK, response)
}

func (h *GameHandler) RegisterRoutes(mux *http.ServeMux) {
	mux.HandleFunc("POST /api/games", h.CreateGame)
	mux.HandleFunc("GET /api/games/{id}", h.GetGame)
	mux.HandleFunc("POST /api/games/{id}/move", h.MakeMove)
}

func extractGameID(path string) string {
    prefix := "/api/games/"
    if !strings.HasPrefix(path, prefix) {
        return ""
    }
	
    rest := path[len(prefix):]
    if rest == "" {
        return ""
    }

    if idx := strings.Index(rest, "/"); idx != -1 {
        return rest[:idx]
    }
    
    return rest
}

func respondJSON(w http.ResponseWriter, status int, data interface{}) {
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(status)
	json.NewEncoder(w).Encode(data)
}
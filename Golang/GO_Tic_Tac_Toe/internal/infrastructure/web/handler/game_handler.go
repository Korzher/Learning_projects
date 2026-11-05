package handler

import (
	"context"
	"encoding/json"
	"net/http"
	"strconv"
	"strings"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"

	"github.com/google/uuid"
)

type GameHandler struct {
	service domain.GameService
	jwt     domain.JwtProvider
}

func NewGameHandler(service domain.GameService, jwt domain.JwtProvider) *GameHandler {
	return &GameHandler{service: service, jwt: jwt}
}

func (h *GameHandler) CreateGame(w http.ResponseWriter, r *http.Request) {
	var req contracts.CreateGameRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrInvalidReq})
		return
	}

	if req.GameType != "vs_computer" && req.GameType != "vs_player" {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrGameType})
		return
	}

	ctx := r.Context()
	game, err := h.service.CreateGame(ctx, req.GameType)
	if err != nil {
		respondJSON(w, http.StatusInternalServerError, contracts.ErrorResponse{Error: err.Error()})
		return
	}
	response := ToGameResponse(game)
	respondJSON(w, http.StatusCreated, response)
}

func (h *GameHandler) GetGame(w http.ResponseWriter, r *http.Request) {
	idStr := extractGameID(r.URL.Path)
	if idStr == "" {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrGameID})
		return
	}
	id, err := uuid.Parse(idStr)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrInvGameID})
		return
	}
	ctx := r.Context()
	game, err := h.service.GetGame(ctx, id)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: err.Error()})
		return
	}

	response := ToGameResponse(game)
	respondJSON(w, http.StatusOK, response)
}

func (h *GameHandler) MakeMove(w http.ResponseWriter, r *http.Request) {
	idStr := extractGameID(r.URL.Path)
	if idStr == "" {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrGameID})
		return
	}
	id, err := uuid.Parse(idStr)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrInvGameID})
		return
	}

	var req contracts.MakeMoveRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrInvalidReq})
		return
	}

	if req.Row < 0 || req.Row > 2 || req.Col < 0 || req.Col > 2 {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrCoords})
		return
	}
	ctx := r.Context()
	game, err := h.service.MakeMove(ctx, id, req.Row, req.Col)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: err.Error()})
		return
	}
	response := ToGameResponse(game)
	respondJSON(w, http.StatusOK, response)
}

func (h *GameHandler) GetAvailableGames(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()
	games, err := h.service.GetAvailableGames(ctx)
	if err != nil {
		respondJSON(w, http.StatusInternalServerError, contracts.ErrorResponse{Error: err.Error()})
		return
	}

	response := make([]contracts.AvailableGamesResponse, len(games))
	for i, game := range games {
		response[i] = contracts.AvailableGamesResponse{
			ID:        game.ID.String(),
			CreatorID: game.PlayerXID.String(),
		}
	}

	respondJSON(w, http.StatusOK, response)
}

func (h *GameHandler) JoinGame(w http.ResponseWriter, r *http.Request) {
	idStr := extractGameID(r.URL.Path)
	if idStr == "" {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrGameID})
		return
	}

	gameID, err := uuid.Parse(idStr)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrInvGameID})
		return
	}

	ctx := r.Context()
	game, err := h.service.JoinGame(ctx, gameID)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: err.Error()})
		return
	}

	responce := ToGameResponse(game)
	respondJSON(w, http.StatusOK, responce)
}

func (h *GameHandler) GetGamesFinishedByID(w http.ResponseWriter, r *http.Request) {
	token := extractAccessToken(r.URL.Path)
	if token == "" {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrToken})
		return
	}

	err := h.jwt.ValidateAccess(token)
	if err != nil {
		respondJSON(w, http.StatusUnauthorized, contracts.ErrorResponse{Error: contracts.ErrInvalidToken})
		return
	}

	userID, err := h.jwt.GetUUID(token)
	if err != nil {
		respondJSON(w, http.StatusUnauthorized, contracts.ErrorResponse{Error: contracts.ErrInvalidToken})
		return
	}

	ctx := r.Context()
	h.returnByToken(ctx, userID, w)
}

func (h *GameHandler) GetFinishedGames(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()
	userID, ok := ctx.Value("user_id").(uuid.UUID)
	if !ok {
		respondJSON(w, http.StatusUnauthorized, contracts.ErrorResponse{Error: contracts.ErrAuth})
		return
	}
	h.returnByToken(ctx, userID, w)
}

func (h *GameHandler) GetLeaderBoard(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()
	prefix := "/api/games/top/"
	limit, err := strconv.Atoi(r.URL.Path[len(prefix):])
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrInvalidNum})
		return
	}
	if limit <= 0 {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: contracts.ErrInvalidNum})
		return
	}
	winrate, err := h.service.GetLeaderBoard(ctx, limit)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: err.Error()})
		return
	}
	response := make([]contracts.WinRateResponse, len(winrate))
	for i, wr := range winrate {
		response[i] = contracts.WinRateResponse{
			UserID:   wr.UserID.String(),
			Username: wr.Username,
			Winrate:  wr.WinRate,
		}
	}
	respondJSON(w, http.StatusOK, response)
}

func (h *GameHandler) RegisterRoutes(mux *http.ServeMux) {
	mux.HandleFunc("POST /api/games", h.CreateGame)
	mux.HandleFunc("GET /api/games/{id}", h.GetGame)
	mux.HandleFunc("POST /api/games/{id}/move", h.MakeMove)
	mux.HandleFunc("GET /api/games/available", h.GetAvailableGames)
	mux.HandleFunc("POST /api/games/{id}/join", h.JoinGame)
	mux.HandleFunc("GET /api/games/finished/{accessToken}", h.GetGamesFinishedByID)
	mux.HandleFunc("GET /api/games/finished", h.GetFinishedGames)
	mux.HandleFunc("GET /api/games/top/{limit}", h.GetLeaderBoard)
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

func extractAccessToken(path string) string {
	prefix := "/api/games/finished/"
	if !strings.HasPrefix(path, prefix) {
		return ""
	}

	rest := path[len(prefix):]
	if rest == "" {
		return ""
	}

	return rest
}

func respondJSON(w http.ResponseWriter, status int, data interface{}) {
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(status)
	json.NewEncoder(w).Encode(data)
}

func (h *GameHandler) returnByToken(ctx context.Context, userID uuid.UUID, w http.ResponseWriter) {
	games, err := h.service.GetGamesFinishedByID(ctx, userID)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, contracts.ErrorResponse{Error: err.Error()})
		return
	}

	response := make([]contracts.GameInfoResponse, len(games))
	for i, game := range games {
		var winner *string
		if game.WinnerID != nil {
			str := game.WinnerID.String()
			winner = &str
		}
		response[i] = contracts.GameInfoResponse{
			ID:       game.ID.String(),
			Status:   string(game.Status),
			WinnerID: winner,
		}
	}

	respondJSON(w, http.StatusOK, response)
}

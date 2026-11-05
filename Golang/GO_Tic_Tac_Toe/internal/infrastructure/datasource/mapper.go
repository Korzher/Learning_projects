package datasource

import (
	"encoding/json"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"

	"github.com/google/uuid"
)

func ToDomain(model *GameModel) (*domain.Game, error) {
	if model == nil {
		return nil, contracts.ErrNilModel
	}

	id, err := uuid.Parse(model.GameID)
	if err != nil {
		return nil, contracts.ErrInvalidGameFormat
	}

	var tempBoard [3][3]int
	if err := json.Unmarshal([]byte(model.Board), &tempBoard); err != nil {
		return nil, contracts.ErrUnmarshJSON
	}

	var board domain.Board
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			val := tempBoard[i][j]
			if val < 0 || val > 2 {
				return nil, contracts.ErrInvalidBoard
			}
			board[i][j] = domain.CellValue(val)
		}
	}

	status := domain.GameStatus(model.Status)
	if !isValidStatus(status) {
		return nil, contracts.ErrInvalidStatus
	}

	nextPlayer := domain.CellValue(model.NextPlayer)
	if nextPlayer != domain.Empty && nextPlayer != domain.X && nextPlayer != domain.O {
		return nil, contracts.ErrInvalidNext
	}

	var playerXID *uuid.UUID
	if model.PlayerXID != nil {
		id, err := uuid.Parse(*model.PlayerXID)
		if err != nil {
			return nil, contracts.ErrInvalidX
		}
		playerXID = &id
	}

	var playerOID *uuid.UUID
	if model.PlayerOID != nil {
		id, err := uuid.Parse(*model.PlayerOID)
		if err != nil {
			return nil, contracts.ErrInvalidO
		}
		playerOID = &id
	}

	var winnerID *uuid.UUID
	if model.WinnerID != nil {
		id, err := uuid.Parse(*model.WinnerID)
		if err != nil {
			return nil, contracts.ErrInvalidWinner
		}
		winnerID = &id
	}

	return &domain.Game{
		ID:         id,
		Board:      board,
		Status:     status,
		NextPlayer: nextPlayer,
		PlayerXID:  playerXID,
		PlayerOID:  playerOID,
		WinnerID:   winnerID,
		CreatedAt:  model.CreatedAt,
	}, nil
}

func ToModel(game *domain.Game) (*GameModel, error) {
	if game == nil {
		return nil, contracts.ErrNilGame
	}

	var board [3][3]int
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			board[i][j] = int(game.Board[i][j])
		}
	}

	boardJSON, err := json.Marshal(board)
	if err != nil {
		return nil, contracts.ErrMarshJSON
	}

	var playerXIDStr, playerOIDStr, winnerIDStr *string

	if game.PlayerXID != nil {
		str := game.PlayerXID.String()
		playerXIDStr = &str
	}

	if game.PlayerOID != nil {
		str := game.PlayerOID.String()
		playerOIDStr = &str
	}

	if game.WinnerID != nil {
		str := game.WinnerID.String()
		winnerIDStr = &str
	}

	return &GameModel{
		GameID:     game.ID.String(),
		Board:      string(boardJSON),
		Status:     string(game.Status),
		NextPlayer: int(game.NextPlayer),
		PlayerXID:  playerXIDStr,
		PlayerOID:  playerOIDStr,
		WinnerID:   winnerIDStr,
	}, nil
}

func isValidStatus(status domain.GameStatus) bool {
	switch status {
	case domain.StatusInProgress, domain.StatusXWin, domain.StatusOWin, domain.StatusDraw, domain.StatusWaiting:
		return true
	default:
		return false
	}
}

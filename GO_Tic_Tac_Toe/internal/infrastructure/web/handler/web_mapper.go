package handler

import (
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"
	"time"
)

func ToGameResponse(game *domain.Game) contracts.GameResponse {
	var boardStr [3][3]string
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			boardStr[i][j] = cellValueToString(game.Board[i][j])
		}
	}

	nextPlayerStr := cellValueToString(game.NextPlayer)

	var winnerIDStr *string
	if game.WinnerID != nil {
		str := game.WinnerID.String()
		winnerIDStr = &str
	}

	var nextPlayerIDStr *string
	if game.Status == domain.StatusInProgress {
		if game.NextPlayer == domain.X && game.PlayerXID != nil {
			str := game.PlayerXID.String()
			nextPlayerIDStr = &str
		} else if game.NextPlayer == domain.O && game.PlayerOID != nil {
			str := game.PlayerOID.String()
			nextPlayerIDStr = &str
		}
	}

	return contracts.GameResponse{
		ID:           game.ID.String(),
		Board:        boardStr,
		Status:       string(game.Status),
		NextPlayer:   nextPlayerStr,
		NextPlayerID: nextPlayerIDStr,
		WinnerID:     winnerIDStr,
		CreatedAt:    game.CreatedAt.Format(time.RFC3339),
	}
}

func cellValueToString(cell domain.CellValue) string {
	switch cell {
	case domain.X:
		return "X"
	case domain.O:
		return "O"
	case domain.Empty:
		return "_"
	default:
		return "?"
	}
}

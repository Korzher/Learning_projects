package handler

import (
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"
)

func ToGameResponse(game *domain.Game) contracts.GameResponse {
	var board [3][3]int
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			board[i][j] = int(game.Board[i][j])
		}
	}

	return contracts.GameResponse{
		ID: game.ID,
		Board: board,
		Status: string(game.Status),
		NextPlayer: int(game.NextPlayer),
	}
}

func ToDomainBoard(board[3][3]int) domain.Board {
	var result domain.Board
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			result[i][j] = domain.CellValue(board[i][j])
		}
	}

	return result
}
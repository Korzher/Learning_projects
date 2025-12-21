package datasource

import (
	"errors"
	"tic-tac-toe/internal/domain"
)



func ToDomain(model *GameModel) (*domain.Game, error) {
	if model == nil {
        return nil, ErrNilModel
    }


	var board domain.Board
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			val := model.Board[i][j]
            if val < 0 || val > 2 {
                return nil, errors.New("invalid board value")
            }
            board[i][j] = domain.CellValue(val)
		}
	}

	status := domain.GameStatus(model.Status)
    if !isValidStatus(status) {
        return nil, errors.New("invalid game status")
    }

	nextPlayer := domain.CellValue(model.NextPlayer)
    if nextPlayer != domain.Empty && nextPlayer != domain.X && nextPlayer != domain.O {
        return nil, errors.New("invalid next player value")
    }

	return &domain.Game{
		ID: model.ID,
		Board: board,
		Status: status,
		NextPlayer: nextPlayer,
	}, nil
}

func ToModel(game *domain.Game) (*GameModel, error) {
	if game == nil {
        return nil, errors.New("game cannot be nil")
    }

	var board[3][3]int
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			board[i][j] = int(game.Board[i][j])
		}
	}
	return &GameModel{
		ID: game.ID,
		Board: board,
		Status: string(game.Status),
		NextPlayer: int(game.NextPlayer),
	}, nil
}

func isValidStatus(status domain.GameStatus) bool {
    switch status {
    case domain.StatusInProgress, domain.StatusXWin, domain.StatusOWin, domain.StatusDraw:
        return true
    default:
        return false
    }
}
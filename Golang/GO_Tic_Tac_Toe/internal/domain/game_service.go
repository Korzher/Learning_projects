package domain

import (
	"context"

	"github.com/google/uuid"
)

type GameService interface {
	CreateGame(ctx context.Context, gameType string) (*Game, error)
	GetGame(ctx context.Context, GameID uuid.UUID) (*Game, error)
	MakeMove(ctx context.Context, gameID uuid.UUID, row, col int) (*Game, error)
	GetNextMove(gameID uuid.UUID, board Board) (Board, error)
	CheckGameStatus(board Board) GameStatus
	GetAvailableGames(ctx context.Context) ([]*Game, error)
	JoinGame(ctx context.Context, gameID uuid.UUID) (*Game, error)
	GetGamesFinishedByID(ctx context.Context, userID uuid.UUID) ([]*Game, error)
	GetLeaderBoard(ctx context.Context, limit int) ([]*WinRate, error)
}

package domain

import (
	"context"

	"github.com/google/uuid"
)

type GameRepository interface {
	Save(ctx context.Context, game *Game) error
	FindByID(ctx context.Context, id uuid.UUID) (*Game, error)
	FindWaitingGames(ctx context.Context) ([]*Game, error)
	FindFinishedByUserID(ctx context.Context, userID uuid.UUID) ([]*Game, error)
	GetLeaderBoard(ctx context.Context, limit int) ([]*WinRate, error)
}

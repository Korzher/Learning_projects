package datasource

import (
	"time"

	"github.com/google/uuid"
)

type GameModel struct {
	ID         int       `db:"id"`
	GameID     string    `db:"game_id"`
	Board      string    `db:"board"`
	Status     string    `db:"status"`
	NextPlayer int       `db:"next_player"`
	PlayerXID  *string   `db:"player_x_id"`
	PlayerOID  *string   `db:"player_o_id"`
	WinnerID   *string   `db:"winner_id"`
	CreatedAt  time.Time `db:"created_at"`
}

type RefreshToken struct {
	ID        uuid.UUID `db:"id"`
	Token     string    `db:"token"`
	ExpiresAt time.Time `db:"expires_at"`
	IsRevoked bool      `db:"is_revoked"`
	UserID    uuid.UUID `db:"user_id"`
	CreatedAt time.Time `db:"created_at"`
}

type User struct {
	ID           uuid.UUID `db:"id"`
	PasswordHash string    `db:"password_hash"`
	CreatedAt    time.Time `db:"created_at"`
}

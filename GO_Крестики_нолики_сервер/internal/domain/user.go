package domain

import (
	"time"

	"github.com/google/uuid"
)

type User struct {
	ID        uuid.UUID
	Username  string
	Password  string
	CreatedAt time.Time
}

type LoginResult struct {
	ID           uuid.UUID
	AccessToken  string
	RefreshToken string
}

type TokenPayload struct {
	ID        uuid.UUID
	Username  string
	CreatedAt time.Time
}

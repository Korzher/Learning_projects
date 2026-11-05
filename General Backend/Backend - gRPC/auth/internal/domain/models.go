package domain

import (
	"time"

	"github.com/google/uuid"
)

type User struct {
	ID uuid.UUID
	Email string
	FirstName string
	LastName string
	Phone string
	Password string
}

type TokenPayload struct {
	ID        uuid.UUID
	Email     string
	CreatedAt time.Time
}

type AuthResult struct {
	User *User
	AccessToken string
	RefreshToken string
}
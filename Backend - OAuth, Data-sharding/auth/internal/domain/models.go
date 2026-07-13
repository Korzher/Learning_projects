package domain

import (
	"time"

	"github.com/google/uuid"
)

type User struct {
	ID        uuid.UUID
	Email     string
	FirstName string
	LastName  string
	Phone     string
	Password  string
}

type TokenPayload struct {
	ID        uuid.UUID
	Email     string
	CreatedAt time.Time
}

type AuthResult struct {
	User         *User
	AccessToken  string
	RefreshToken string
}

type GoogleUserInfo struct {
	ID        string `json:"id"`
	Email     string `json:"email"`
	FirstName string `json:"given_name"`
	LastName  string `json:"family_name"`
	AvatarURL string `json:"picture"`
}

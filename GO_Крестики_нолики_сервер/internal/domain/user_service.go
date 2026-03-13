package domain

import (
	"context"
	"tic-tac-toe/pkg/contracts"

	"github.com/google/uuid"
)

type UserService interface {
	Register(ctx context.Context, req contracts.SignUpRequest) error
	Login(ctx context.Context, login, password string) (*LoginResult, error)
	GetUserByID(ctx context.Context, id uuid.UUID) (*User, error)
	GetAllUsers(ctx context.Context) ([]*User, error)
	RefreshAccessToken(ctx context.Context, refreshToken string) (*LoginResult, error)
	RefreshRefreshToken(ctx context.Context, refreshToken string) (*LoginResult, error)
}

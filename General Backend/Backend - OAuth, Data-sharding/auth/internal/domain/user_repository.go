package domain

import (
	"context"
	"time"
)

type UserRepository interface {
	CreateUser(ctx context.Context, user *User) error
	AuthenticateUser(ctx context.Context, email string) (*User, error)
	ChangePassword(ctx context.Context, email, password string) error
	SaveOAuthState(ctx context.Context, state string, expiresAt time.Time) error
	GetOAuthState(ctx context.Context, state string) (*time.Time, error)
	DeleteOAuthState(ctx context.Context, state string) error
	CreateOAuthUser(ctx context.Context, user *User) error
}

package domain

import "context"

type UserRepository interface {
	CreateUser(ctx context.Context, user *User) error
	AuthenticateUser(ctx context.Context, email string) (*User, error)
	ChangePassword(ctx context.Context, email, password string) error
}
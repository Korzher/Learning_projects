package domain

import (
	"context"
	"grpc_auth/pkg/contracts"
)

type UserService interface {
	CreateUser(ctx context.Context, req contracts.CreateUserRequest) (*AuthResult, error)
	AuthenticateUser(ctx context.Context, req contracts.AuthenticateRequest) (*AuthResult, error)
	RefreshTokens(ctx context.Context, refreshToken string) (*AuthResult, error)
	ChangePassword(ctx context.Context, req contracts.ChangePasswordRequest) error
	ResetPassword(ctx context.Context, req contracts.ResetPasswordRequest) error
}
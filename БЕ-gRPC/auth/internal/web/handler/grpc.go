package handler

import (
	"context"
	auth "gen"
	"grpc_auth/internal/domain"
	"grpc_auth/pkg/contracts"
	"strings"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/metadata"
	"google.golang.org/grpc/status"
)

type AuthServer struct {
	auth.UnimplementedAuthServiceServer
	service domain.UserService
	jwt     domain.JwtProvider
}

func NewAuthServer(service domain.UserService, jwt domain.JwtProvider) *AuthServer {
	return &AuthServer{
		service: service,
		jwt:     jwt,
	}
}

func (a *AuthServer) CreateUser(ctx context.Context, req *auth.CreateUserRequest) (*auth.CreateUserResponse, error) {
	res, err := a.service.CreateUser(ctx, contracts.CreateUserRequest{
		Email:     req.Email,
		FirstName: req.FirstName,
		LastName:  req.LastName,
		Phone:     req.Phone,
		Password:  req.Password,
	})
	if err != nil {
		return nil, err
	}
	return &auth.CreateUserResponse{
		Token: res.AccessToken,
	}, nil
}

func (a *AuthServer) Authenticate(ctx context.Context, req *auth.AuthenticateRequest) (*auth.AuthenticateResponse, error) {
	res, err := a.service.AuthenticateUser(ctx, contracts.AuthenticateRequest{
		Email:    req.Email,
		Password: req.Password,
	})
	if err != nil {
		return nil, err
	}
	return &auth.AuthenticateResponse{
		Token: res.AccessToken,
	}, nil
}

func (a *AuthServer) VerifyToken(ctx context.Context, req *auth.VerifyTokenRequest) (*auth.VerifyTokenResponse, error) {
	err := a.jwt.ValidateAccess(req.Token)
	if err != nil {
		return &auth.VerifyTokenResponse{
			Valid: false,
		}, err
	}
	return &auth.VerifyTokenResponse{
		Valid: true,
	}, nil
}

func (a *AuthServer) ChangePassword(ctx context.Context, req *auth.ChangePasswordRequest) (*auth.ChangePasswordResponse, error) {
	md, ok := metadata.FromIncomingContext(ctx)
	if !ok {
		return nil, status.Error(codes.Unauthenticated, "metadata is not provided")
	}
	authHeader := md.Get("authorization")
	if len(authHeader) == 0 {
		return nil, status.Error(codes.Unauthenticated, "authorization header is missing")
	}
	token := strings.TrimPrefix(authHeader[0], "Bearer ")

	err := a.service.ChangePassword(ctx, contracts.ChangePasswordRequest{
		Token:       token,
		OldPassword: req.OldPassword,
		NewPassword: req.NewPassword,
	})
	if err != nil {
		return &auth.ChangePasswordResponse{
			Success: false,
			Message: err.Error(),
		}, err
	}
	return &auth.ChangePasswordResponse{
		Success: true,
		Message: "Password changed successfully",
	}, nil
}

func (a *AuthServer) ResetPassword(ctx context.Context, req *auth.ResetPasswordRequest) (*auth.ResetPasswordResponse, error) {
	err := a.service.ResetPassword(ctx, contracts.ResetPasswordRequest{
		Email: req.Email,
	})
	if err != nil {
		return &auth.ResetPasswordResponse{
			Success: false,
			Message: err.Error(),
		}, nil
	}
	return &auth.ResetPasswordResponse{
		Success: true,
		Message: "Password reset instructions sent to email",
	}, nil
}

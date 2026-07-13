package service

import (
	"context"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"fmt"
	"grpc_auth/internal/domain"
	"grpc_auth/internal/web/dto"
	"grpc_auth/pkg/contracts"
	"log"
	"time"

	"golang.org/x/crypto/bcrypt"
)

type UserService struct {
	repo domain.UserRepository
	jwt  domain.JwtProvider
}

func NewUserService(repo domain.UserRepository, jwt domain.JwtProvider) domain.UserService {
	return &UserService{
		repo: repo,
		jwt:  jwt,
	}
}

func (s *UserService) CreateUser(ctx context.Context, req contracts.CreateUserRequest) (*domain.AuthResult, error) {
	if req.Email == "" || req.FirstName == "" || req.LastName == "" || req.Phone == "" || req.Password == "" {
		return nil, errors.New("all fields required")
	}

	if len(req.Email) > 50 {
		return nil, errors.New("email is too long")
	}

	passwordWithSalt := req.Password + "Salt"
	hashedPassword, err := bcrypt.GenerateFromPassword([]byte(passwordWithSalt), bcrypt.DefaultCost)
	if err != nil {
		return nil, errors.New("failed to hash password")
	}
	user := dto.ReqToUser(req)

	user.Password = string(hashedPassword)

	err = s.repo.CreateUser(ctx, user)
	if err != nil {
		return nil, err
	}

	accessToken, refreshToken, err := s.jwt.GeneratePayload(domain.TokenPayload{
		ID:    user.ID,
		Email: user.Email,
	})
	if err != nil {
		return nil, errors.New("failed to generate token")
	}

	return &domain.AuthResult{
		User:         user,
		AccessToken:  accessToken,
		RefreshToken: refreshToken,
	}, nil
}

func (s *UserService) AuthenticateUser(ctx context.Context, req contracts.AuthenticateRequest) (*domain.AuthResult, error) {
	if req.Email == "" || req.Password == "" {
		return nil, errors.New("email and password required")
	}

	user, err := s.repo.AuthenticateUser(ctx, req.Email)
	if err != nil {
		return nil, err
	}

	passwordWithSalt := req.Password + "Salt"

	err = bcrypt.CompareHashAndPassword([]byte(user.Password), []byte(passwordWithSalt))
	if err != nil {
		return nil, errors.New("invalid credentials")
	}

	accessToken, refreshToken, err := s.jwt.GeneratePayload(domain.TokenPayload{
		ID:    user.ID,
		Email: user.Email,
	})
	if err != nil {
		return nil, errors.New("failed to generate token")
	}

	user.Password = ""

	return &domain.AuthResult{
		User:         user,
		AccessToken:  accessToken,
		RefreshToken: refreshToken,
	}, nil
}

func (s *UserService) RefreshTokens(ctx context.Context, refreshToken string) (*domain.AuthResult, error) {
	if err := s.jwt.ValidateRefresh(refreshToken); err != nil {
		return nil, errors.New("invalid refresh token")
	}

	email, err := s.jwt.ExtractEmailFromAccess(refreshToken)
	if err != nil {
		return nil, err
	}

	user, err := s.repo.AuthenticateUser(ctx, email)
	if err != nil {
		return nil, err
	}

	accessToken, newRefreshToken, err := s.jwt.GeneratePayload(domain.TokenPayload{
		ID:    user.ID,
		Email: user.Email,
	})

	return &domain.AuthResult{
		User:         user,
		AccessToken:  accessToken,
		RefreshToken: newRefreshToken,
	}, nil
}

func (s *UserService) ChangePassword(ctx context.Context, req contracts.ChangePasswordRequest) error {
	if req.Token == "" || req.OldPassword == "" || req.NewPassword == "" {
		return errors.New("token, old password and new password required")
	}

	email, err := s.jwt.ExtractEmailFromAccess(req.Token)
	if err != nil {
		return errors.New("invalid token")
	}

	user, err := s.repo.AuthenticateUser(ctx, email)
	if err != nil {
		return err
	}

	oldPasswordWithSalt := req.OldPassword + "Salt"

	err = bcrypt.CompareHashAndPassword([]byte(user.Password), []byte(oldPasswordWithSalt))
	if err != nil {
		return errors.New("invalid credentials")
	}

	newPasswordWithSalt := req.NewPassword + "Salt"
	hashedPassword, err := bcrypt.GenerateFromPassword([]byte(newPasswordWithSalt), bcrypt.DefaultCost)
	if err != nil {
		return fmt.Errorf("failed to hash new password: %w", err)
	}

	err = s.repo.ChangePassword(ctx, email, string(hashedPassword))
	if err != nil {
		return err
	}

	return nil
}

func (s *UserService) ResetPassword(ctx context.Context, req contracts.ResetPasswordRequest) error {
	if req.Email == "" {
		return errors.New("email required")
	}

	user, err := s.repo.AuthenticateUser(ctx, req.Email)
	if err != nil {
		return err
	}

	newPlainPassword := generateTemporaryPassword()
	newPasswordWithSalt := newPlainPassword + "Salt"
	hashedPassword, err := bcrypt.GenerateFromPassword([]byte(newPasswordWithSalt), bcrypt.DefaultCost)
	if err != nil {
		return fmt.Errorf("failed to hash new password: %w", err)
	}

	err = s.repo.ChangePassword(ctx, user.Email, string(hashedPassword))
	if err != nil {
		return err
	}

	log.Printf("Password reset for %s. New password: %s", req.Email, newPlainPassword)

	return nil
}

func generateTemporaryPassword() string {
	b := make([]byte, 8)
	if _, err := rand.Read(b); err != nil {
		return "temp-password-123"
	}
	return hex.EncodeToString(b)
}

func (s *UserService) SaveOAuthState(ctx context.Context, state string, expiresAt time.Time) error {
	return s.repo.SaveOAuthState(ctx, state, expiresAt)
}

func (s *UserService) VerifyOAuthState(ctx context.Context, state string) (bool, error) {
	expiresAt, err := s.repo.GetOAuthState(ctx, state)
	if err != nil {
		return false, err
	}

	if expiresAt == nil || time.Now().After(*expiresAt) {
		return false, nil
	}

	return true, nil
}

func (s *UserService) DeleteOAuthState(ctx context.Context, state string) error {
	return s.repo.DeleteOAuthState(ctx, state)
}

func (s *UserService) CreateOrGetOAuthUser(ctx context.Context, info domain.GoogleUserInfo) (*domain.AuthResult, error) {
	user, err := s.repo.AuthenticateUser(ctx, info.Email)
	if err != nil {
		if err.Error() == "Email not found" {
			user = &domain.User{
				Email:     info.Email,
				FirstName: info.FirstName,
				LastName:  info.LastName,
				Password:  "",
			}
			err = s.repo.CreateOAuthUser(ctx, user)
			if err != nil {
				return nil, err
			}
		} else {
			return nil, err
		}
	}

	accessToken, refreshToken, err := s.jwt.GeneratePayload(domain.TokenPayload{
		ID:    user.ID,
		Email: user.Email,
	})
	if err != nil {
		return nil, errors.New("failed to generate token")
	}
	return &domain.AuthResult{
		User:         user,
		AccessToken:  accessToken,
		RefreshToken: refreshToken,
	}, nil
}

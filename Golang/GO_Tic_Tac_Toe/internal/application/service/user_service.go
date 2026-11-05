package service

import (
	"context"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"
	"time"

	"github.com/google/uuid"
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

func (s *UserService) Register(ctx context.Context, req contracts.SignUpRequest) error {
	if req.Username == "" {
		return contracts.ErrLoginEmpty
	}

	if len(req.Username) > 50 {
		return contracts.ErrLoginTooLong
	}

	if req.Password == "" {
		return contracts.ErrPasswordEmpty
	}
	if len(req.Password) > 255 {
		return contracts.ErrPasswordTooLong
	}

	existing, err := s.repo.FindByUsername(ctx, req.Username)

	if existing != nil {
		return contracts.ErrUserExist
	}

	pass, err := bcrypt.GenerateFromPassword([]byte(req.Password), 12)
	if err != nil {
		return err
	}

	user := &domain.User{
		ID:        uuid.New(),
		Username:  req.Username,
		Password:  string(pass),
		CreatedAt: time.Now(),
	}

	if err := s.repo.Save(ctx, user); err != nil {
		return contracts.ErrFailedToSave
	}

	return nil
}

func (s *UserService) Login(ctx context.Context, login, password string) (*domain.LoginResult, error) {
	user, err := s.repo.FindByUsername(ctx, login)
	if err != nil {
		return nil, err
	}

	err = bcrypt.CompareHashAndPassword([]byte(user.Password), []byte(password))

	if err != nil {
		return nil, contracts.ErrWrongPW
	}

	token := domain.TokenPayload{
		ID:        user.ID,
		Username:  user.Username,
		CreatedAt: user.CreatedAt,
	}

	AccessToken, RefreshToken, err := s.jwt.GeneratePayload(token)
	if err != nil {
		return nil, err
	}

	return &domain.LoginResult{ID: user.ID, AccessToken: AccessToken,
		RefreshToken: RefreshToken}, nil
}

func (s *UserService) RefreshAccessToken(ctx context.Context, refreshToken string) (*domain.LoginResult, error) {
	err := s.jwt.ValidateRefresh(refreshToken)
	if err != nil {
		return nil, contracts.ErrInvalidCred
	}
	userID, err := s.jwt.GetUUID(refreshToken)
	if err != nil {
		return nil, contracts.ErrInvalidCred
	}

	user, err := s.repo.FindByID(ctx, userID)
	if err != nil {
		return nil, err
	}
	if user == nil {
		return nil, contracts.ErrUserNotFound
	}

	token := domain.TokenPayload{
		ID:        user.ID,
		Username:  user.Username,
		CreatedAt: user.CreatedAt,
	}

	accessToken, err := s.jwt.GenerateAccess(token)
	if err != nil {
		return nil, err
	}
	return &domain.LoginResult{AccessToken: accessToken, RefreshToken: refreshToken}, nil
}

func (s *UserService) RefreshRefreshToken(ctx context.Context, refreshToken string) (*domain.LoginResult, error) {
	err := s.jwt.ValidateRefresh(refreshToken)
	if err != nil {
		return nil, contracts.ErrInvalidCred
	}

	userID, err := s.jwt.GetUUID(refreshToken)
	if err != nil {
		return nil, contracts.ErrInvalidCred
	}

	user, err := s.repo.FindByID(ctx, userID)
	if err != nil {
		return nil, err
	}
	if user == nil {
		return nil, contracts.ErrUserNotFound
	}

	token := domain.TokenPayload{
		ID:        user.ID,
		Username:  user.Username,
		CreatedAt: user.CreatedAt,
	}

	accessToken, refreshToken, err := s.jwt.GeneratePayload(token)
	if err != nil {
		return nil, err
	}

	return &domain.LoginResult{AccessToken: accessToken, RefreshToken: refreshToken}, nil

}

func (s *UserService) GetUserByID(ctx context.Context, userID uuid.UUID) (*domain.User, error) {
	user, err := s.repo.FindByID(ctx, userID)
	if err != nil {
		return nil, err
	}
	if user == nil {
		return nil, contracts.ErrUserNotFound
	}
	return user, nil
}

func (s *UserService) GetAllUsers(ctx context.Context) ([]*domain.User, error) {
	users, err := s.repo.FindAll(ctx)
	if err != nil {
		return nil, err
	}

	return users, nil
}

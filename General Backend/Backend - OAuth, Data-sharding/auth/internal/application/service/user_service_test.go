package service

import (
	"context"
	"errors"
	"testing"
	"time"

	"github.com/google/uuid"
	"golang.org/x/crypto/bcrypt"

	"grpc_auth/internal/domain"
	"grpc_auth/pkg/contracts"
)

type fakeUserRepo struct {
	users   map[string]*domain.User
	created []*domain.User
}

func newFakeUserRepo() *fakeUserRepo {
	return &fakeUserRepo{users: make(map[string]*domain.User)}
}

func (f *fakeUserRepo) CreateUser(_ context.Context, u *domain.User) error {
	f.users[u.Email] = u
	f.created = append(f.created, u)
	return nil
}

func (f *fakeUserRepo) AuthenticateUser(_ context.Context, email string) (*domain.User, error) {
	u, ok := f.users[email]
	if !ok {
		return nil, errors.New("Email not found")
	}
	cp := *u
	return &cp, nil
}

func (f *fakeUserRepo) ChangePassword(_ context.Context, email, password string) error {
	if u, ok := f.users[email]; ok {
		u.Password = password
	}
	return nil
}

func (f *fakeUserRepo) SaveOAuthState(_ context.Context, _ string, _ time.Time) error { return nil }

func (f *fakeUserRepo) GetOAuthState(_ context.Context, _ string) (*time.Time, error) {
	return nil, errors.New("state not found")
}

func (f *fakeUserRepo) DeleteOAuthState(_ context.Context, _ string) error { return nil }

func (f *fakeUserRepo) CreateOAuthUser(_ context.Context, u *domain.User) error {
	f.users[u.Email] = u
	return nil
}

type fakeJwtProvider struct{}

func (fakeJwtProvider) GeneratePayload(_ domain.TokenPayload) (string, string, error) {
	return "access-token", "refresh-token", nil
}

func (fakeJwtProvider) GenerateAccess(_ domain.TokenPayload) (string, error) {
	return "access-token", nil
}

func (fakeJwtProvider) GenerateRefresh(_ domain.TokenPayload) (string, error) {
	return "refresh-token", nil
}

func (fakeJwtProvider) ValidateAccess(_ string) error  { return nil }
func (fakeJwtProvider) ValidateRefresh(_ string) error { return nil }

func (fakeJwtProvider) ExtractEmailFromAccess(_ string) (string, error) {
	return "user@test.com", nil
}

func newTestUserService(repo domain.UserRepository) domain.UserService {
	return NewUserService(repo, fakeJwtProvider{})
}

func TestCreateUserMissingFields(t *testing.T) {
	s := newTestUserService(newFakeUserRepo())

	_, err := s.CreateUser(context.Background(), contracts.CreateUserRequest{
		Email: "user@test.com",
	})
	if err == nil {
		t.Fatal("CreateUser() expected error for missing fields, got nil")
	}
}

func TestCreateUserSuccess(t *testing.T) {
	repo := newFakeUserRepo()
	s := newTestUserService(repo)

	res, err := s.CreateUser(context.Background(), contracts.CreateUserRequest{
		Email:     "user@test.com",
		FirstName: "Ivan",
		LastName:  "Petrov",
		Phone:     "+70000000000",
		Password:  "secret",
	})
	if err != nil {
		t.Fatalf("CreateUser() error = %v", err)
	}
	if res == nil {
		t.Fatal("CreateUser() returned nil result")
	}
	if len(repo.created) != 1 {
		t.Fatalf("CreateUser() created %d users, want 1", len(repo.created))
	}

	stored := repo.created[0]
	if stored.Password == "secret" {
		t.Fatal("password must be stored as hash, not plaintext")
	}
	if stored.Password == "" {
		t.Fatal("stored password must not be empty")
	}
	if res.AccessToken != "access-token" || res.RefreshToken != "refresh-token" {
		t.Fatalf("unexpected tokens: access=%q refresh=%q", res.AccessToken, res.RefreshToken)
	}
}

func TestAuthenticateUserMissingFields(t *testing.T) {
	s := newTestUserService(newFakeUserRepo())

	_, err := s.AuthenticateUser(context.Background(), contracts.AuthenticateRequest{})
	if err == nil {
		t.Fatal("AuthenticateUser() expected error for missing fields, got nil")
	}
}

func TestAuthenticateUserSuccess(t *testing.T) {
	repo := newFakeUserRepo()
	hash, err := bcrypt.GenerateFromPassword([]byte("secretSalt"), bcrypt.DefaultCost)
	if err != nil {
		t.Fatalf("bcrypt.GenerateFromPassword() error = %v", err)
	}
	repo.users["user@test.com"] = &domain.User{
		ID:       uuid.New(),
		Email:    "user@test.com",
		Password: string(hash),
	}
	s := newTestUserService(repo)

	res, err := s.AuthenticateUser(context.Background(), contracts.AuthenticateRequest{
		Email:    "user@test.com",
		Password: "secret",
	})
	if err != nil {
		t.Fatalf("AuthenticateUser() error = %v", err)
	}
	if res.User.Password != "" {
		t.Fatal("password must be cleared from the response")
	}
}

func TestAuthenticateUserWrongPassword(t *testing.T) {
	repo := newFakeUserRepo()
	hash, err := bcrypt.GenerateFromPassword([]byte("secretSalt"), bcrypt.DefaultCost)
	if err != nil {
		t.Fatalf("bcrypt.GenerateFromPassword() error = %v", err)
	}
	repo.users["user@test.com"] = &domain.User{
		Email:    "user@test.com",
		Password: string(hash),
	}
	s := newTestUserService(repo)

	_, err = s.AuthenticateUser(context.Background(), contracts.AuthenticateRequest{
		Email:    "user@test.com",
		Password: "wrong",
	})
	if err == nil || err.Error() != "invalid credentials" {
		t.Fatalf("AuthenticateUser() error = %v, want 'invalid credentials'", err)
	}
}

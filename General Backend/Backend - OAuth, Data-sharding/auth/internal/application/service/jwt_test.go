package service

import (
	"strings"
	"testing"
	"time"

	"grpc_auth/internal/domain"

	"github.com/golang-jwt/jwt/v5"
	"github.com/google/uuid"
)

func newTestJwtProvider() *JwtProvider {
	return &JwtProvider{secret: []byte("test-secret")}
}

func TestGenerateAndValidateAccess(t *testing.T) {
	j := newTestJwtProvider()
	token, err := j.GenerateAccess(domain.TokenPayload{
		ID:    uuid.New(),
		Email: "user@test.com",
	})
	if err != nil {
		t.Fatalf("GenerateAccess() error = %v", err)
	}
	if token == "" {
		t.Fatal("GenerateAccess() returned empty token")
	}
	if err := j.ValidateAccess(token); err != nil {
		t.Fatalf("ValidateAccess() error = %v", err)
	}
}

func TestGenerateAndValidateRefresh(t *testing.T) {
	j := newTestJwtProvider()
	token, err := j.GenerateRefresh(domain.TokenPayload{Email: "user@test.com"})
	if err != nil {
		t.Fatalf("GenerateRefresh() error = %v", err)
	}
	if err := j.ValidateRefresh(token); err != nil {
		t.Fatalf("ValidateRefresh() error = %v", err)
	}
}

func TestValidateAccessRejectsRefreshToken(t *testing.T) {
	j := newTestJwtProvider()
	refresh, err := j.GenerateRefresh(domain.TokenPayload{Email: "user@test.com"})
	if err != nil {
		t.Fatalf("GenerateRefresh() error = %v", err)
	}
	if err := j.ValidateAccess(refresh); err == nil {
		t.Fatal("ValidateAccess(refresh token) expected error, got nil")
	}
}

func TestValidateRefreshRejectsAccessToken(t *testing.T) {
	j := newTestJwtProvider()
	access, err := j.GenerateAccess(domain.TokenPayload{
		ID:    uuid.New(),
		Email: "user@test.com",
	})
	if err != nil {
		t.Fatalf("GenerateAccess() error = %v", err)
	}
	if err := j.ValidateRefresh(access); err == nil {
		t.Fatal("ValidateRefresh(access token) expected error, got nil")
	}
}

func TestValidateAccessWithTamperedToken(t *testing.T) {
	j := newTestJwtProvider()
	token, err := j.GenerateAccess(domain.TokenPayload{
		ID:    uuid.New(),
		Email: "user@test.com",
	})
	if err != nil {
		t.Fatalf("GenerateAccess() error = %v", err)
	}

	pos := strings.LastIndexByte(token, '.')
	tampered := token[:pos] + ".tampered-signature"

	if err := j.ValidateAccess(tampered); err == nil {
		t.Fatal("ValidateAccess(tampered token) expected error, got nil")
	}
}

func TestValidateAccessWithExpiredToken(t *testing.T) {
	j := newTestJwtProvider()
	claims := jwt.MapClaims{
		"id":    uuid.New().String(),
		"email": "user@test.com",
		"exp":   time.Now().Add(-time.Hour).Unix(),
		"typ":   "access",
	}
	token, err := jwt.NewWithClaims(jwt.SigningMethodHS256, claims).SignedString(j.secret)
	if err != nil {
		t.Fatalf("failed to sign expired token: %v", err)
	}

	if err := j.ValidateAccess(token); err == nil {
		t.Fatal("ValidateAccess(expired token) expected error, got nil")
	}
}

func TestExtractEmailFromAccess(t *testing.T) {
	j := newTestJwtProvider()
	token, err := j.GenerateAccess(domain.TokenPayload{
		ID:    uuid.New(),
		Email: "user@test.com",
	})
	if err != nil {
		t.Fatalf("GenerateAccess() error = %v", err)
	}

	email, err := j.ExtractEmailFromAccess(token)
	if err != nil {
		t.Fatalf("ExtractEmailFromAccess() error = %v", err)
	}
	if email != "user@test.com" {
		t.Fatalf("ExtractEmailFromAccess() = %q, want %q", email, "user@test.com")
	}
}

func TestGeneratePayloadReturnsBothTokens(t *testing.T) {
	j := newTestJwtProvider()
	access, refresh, err := j.GeneratePayload(domain.TokenPayload{
		ID:    uuid.New(),
		Email: "user@test.com",
	})
	if err != nil {
		t.Fatalf("GeneratePayload() error = %v", err)
	}
	if access == "" || refresh == "" {
		t.Fatal("GeneratePayload() returned empty token")
	}
	if access == refresh {
		t.Fatal("GeneratePayload() access and refresh tokens must differ")
	}
	if err := j.ValidateAccess(access); err != nil {
		t.Fatalf("access token invalid: %v", err)
	}
	if err := j.ValidateRefresh(refresh); err != nil {
		t.Fatalf("refresh token invalid: %v", err)
	}
}

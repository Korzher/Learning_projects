package service

import (
	"errors"
	"grpc_auth/internal/domain"
	"time"

	"github.com/golang-jwt/jwt/v5"
)

type JwtProvider struct {
	secret []byte
}

func NewJwtProvider() domain.JwtProvider {
	return &JwtProvider{
		secret: []byte("Should_not_be_in_code"),
	}
}

func (j *JwtProvider) GeneratePayload(token domain.TokenPayload) (string, string, error) {
	accessToken, err := j.GenerateAccess(token)
	if err != nil {
		return "", "", err
	}

	refreshToken, err := j.GenerateRefresh(token)
	if err != nil {
		return "", "", err
	}
	return accessToken, refreshToken, nil
}

func (j *JwtProvider) GenerateAccess(token domain.TokenPayload) (string, error) {
	claims := jwt.MapClaims{
		"id": token.ID.String(),
		"email": token.Email,
		"exp": time.Now().Add(time.Minute * 30).Unix(),
		"typ": "access",
	}

	jwtToken := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
	accessToken, err := jwtToken.SignedString(j.secret)
	if err != nil {
		return "", err
	}
	return accessToken, nil
}

func (j *JwtProvider) GenerateRefresh(token domain.TokenPayload) (string, error) {
	claims := jwt.MapClaims{
		"email":  token.Email,
		"exp": time.Now().Add(time.Hour * 168).Unix(),
		"typ": "refresh",
	}

	jwtToken := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
	refreshToken, err := jwtToken.SignedString(j.secret)
	if err != nil {
		return "", err
	}
	return refreshToken, nil
}

func (j *JwtProvider) ValidateAccess(token string) error {
	claims, err := j.parseToken(token)
	if err != nil {
		return err
	}

	claimsMap, ok := claims.(jwt.MapClaims)
	if !ok {
		return errors.New("Invalid claims type")
	}

	typ, ok := claimsMap["typ"].(string)
	if !ok || typ != "access" {
		return errors.New("invalid token type")
	}

	return nil
}

func (j *JwtProvider) ValidateRefresh(token string) error {
	claims, err := j.parseToken(token)
	if err != nil {
		return err
	}
	claimsMap, ok := claims.(jwt.MapClaims)
	if !ok {
		return errors.New("Invalid claims type")
	}

	typ, ok := claimsMap["typ"].(string)
	if !ok || typ != "refresh" {
		return errors.New("invalid token type")
	}
	return nil
}

func (j *JwtProvider) ExtractEmailFromAccess(token string) (string, error) {
	claims, err := j.parseToken(token)
	if err != nil {
		return "", err
	}

	claimsMap, ok := claims.(jwt.MapClaims)
	if !ok {
		return "", errors.New("invalid claims type")
	}

	email, ok := claimsMap["email"].(string)
	if !ok {
		return "", errors.New("invalid email claim")
	}

	return email, nil
}

func (j *JwtProvider) parseToken(token string) (jwt.Claims, error) {
	claims := jwt.MapClaims{}

	keyFunc := func(t *jwt.Token) (any, error) {
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, errors.New("Unexpected signing method")
		}
		return j.secret, nil
	}
	parsedToken, err := jwt.ParseWithClaims(token, claims, keyFunc)

	if err != nil {
		return nil, err
	}
	if !parsedToken.Valid {
		return nil, errors.New("invalid token")
	}
	return claims, nil
}

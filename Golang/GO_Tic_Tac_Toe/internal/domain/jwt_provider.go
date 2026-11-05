package domain

import "github.com/google/uuid"

type JwtProvider interface {
	GeneratePayload(token TokenPayload) (string, string, error)
	GenerateAccess(token TokenPayload) (string, error)
	GenerateRefresh(token TokenPayload) (string, error)
	ValidateAccess(token string) error
	ValidateRefresh(token string) error
	GetUUID(token string) (uuid.UUID, error)
}

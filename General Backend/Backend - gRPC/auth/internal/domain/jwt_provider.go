package domain

type JwtProvider interface {
	GeneratePayload(token TokenPayload) (string, string, error)
	GenerateAccess(token TokenPayload) (string, error)
	GenerateRefresh(token TokenPayload) (string, error)
	ValidateAccess(token string) error
	ValidateRefresh(token string) error
	ExtractEmailFromAccess(token string) (string, error)
}
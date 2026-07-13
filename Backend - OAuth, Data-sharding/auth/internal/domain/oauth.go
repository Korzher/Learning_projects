package domain

import "context"

type OAuthProvider interface {
	GetAuthURL(state string) string
	Exchange(ctx context.Context, code string) (*GoogleUserInfo, error)
}

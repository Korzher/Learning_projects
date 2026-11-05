package oauth

import (
	"context"
	"encoding/json"
	"errors"
	"grpc_auth/internal/domain"
	"net/http"
	"os"

	"golang.org/x/oauth2"
	"golang.org/x/oauth2/google"
)

type GoogleOAuth struct {
	config *oauth2.Config
}

func NewGoogleAuth() *GoogleOAuth {
	clientID := os.Getenv("GOOGLE_CLIENT_ID")
	clientSecret := os.Getenv("GOOGLE_CLIENT_SECRET")

	config := &oauth2.Config{
		ClientID:     clientID,
		ClientSecret: clientSecret,
		RedirectURL:  "http://localhost:8080/api/v1/auth/google/callback",
		Scopes: []string{
			"https://www.googleapis.com/auth/userinfo.email",
			"https://www.googleapis.com/auth/userinfo.profile",
		},
		Endpoint: google.Endpoint,
	}
	return &GoogleOAuth{config: config}
}

func (g *GoogleOAuth) GetAuthURL(state string) string {
	return g.config.AuthCodeURL(state)
}

func (g *GoogleOAuth) Exchange(ctx context.Context, code string) (*domain.GoogleUserInfo, error) {
	token, err := g.config.Exchange(ctx, code)
	if err != nil {
		return nil, err
	}

	client := &http.Client{}
	req, err := http.NewRequest("GET", "https://www.googleapis.com/oauth2/v2/userinfo", nil)
	if err != nil {
		return nil, err
	}

	req.Header.Set("Authorization", "Bearer "+token.AccessToken)
	resp, err := client.Do(req)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()

	var userInfo domain.GoogleUserInfo

	if err := json.NewDecoder(resp.Body).Decode(&userInfo); err != nil {
		return nil, err
	}

	if userInfo.ID == "" {
		return nil, errors.New("failed to get user info from google")
	}

	return &userInfo, nil
}

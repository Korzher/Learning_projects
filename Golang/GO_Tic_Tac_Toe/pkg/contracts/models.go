package contracts

type GameResponse struct {
	ID           string       `json:"id"`
	Board        [3][3]string `json:"board"`
	Status       string       `json:"status"`
	NextPlayer   string       `json:"next_player"`
	NextPlayerID *string      `json:"next_player_id"`
	WinnerID     *string      `json:"winner_id"`
	CreatedAt    string       `json:"created_at"`
}

type GameInfoResponse struct {
	ID       string  `json:"id"`
	Status   string  `json:"status"`
	WinnerID *string `json:"winner_id"`
}

type MakeMoveRequest struct {
	Row int `json:"row" validate:"required,min=0,max=2"`
	Col int `json:"col" validate:"required,min=0,max=2"`
}

type ErrorResponse struct {
	Error string `json:"error"`
}

type SignUpRequest struct {
	Username string `json:"username"`
	Password string `json:"password"`
}

type CreateGameRequest struct {
	GameType string `json:"game_type" validate:"required,oneof=vs_computer vs_player"`
}

type UserResponse struct {
	ID       string `json:"id"`
	Username string `json:"username"`
}

type AvailableGamesResponse struct {
	ID        string `json:"id"`
	CreatorID string `json:"creator_id"`
}

type JwtRequest struct {
	Username string `json:"username"`
	Password string `json:"password"`
}

type JwtResponse struct {
	ID           string `json:"id"`
	TokenType    string `json:"type"`
	AccessToken  string `json:"access_token"`
	RefreshToken string `json:"refresh_token"`
}

type RefreshJwtRequest struct {
	RefreshToken string `json:"refresh_token"`
}

type WinRateResponse struct {
	UserID   string  `json:"user_id"`
	Username string  `json:"username"`
	Winrate  float64 `json:"win_rate"`
}

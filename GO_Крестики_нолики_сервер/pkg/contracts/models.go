package contracts

type GameResponse struct {
	ID         int       `json:"id"`
	Board      [3][3]int `json:"board"`
	Status     string    `json:"status"`
	NextPlayer int       `json:"next_player"`
}

type MakeMoveRequest struct {
	Row int `json:"row" validate:"required,min=0,max=2"`
	Col int `json:"col" validate:"required,min=0,max=2"`
}

type ErrorResponse struct {
	Error string `json:"error"`
}
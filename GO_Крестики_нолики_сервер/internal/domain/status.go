package domain

type GameStatus string

const (
	StatusInProgress GameStatus = "IN_PROGRESS"
	StatusXWin       GameStatus = "X_WIN"
	StatusOWin       GameStatus = "O_WIN"
	StatusDraw       GameStatus = "DRAW"
)

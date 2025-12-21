package domain

import (
	"sync/atomic"
)

type Game struct {
	ID  int
	Board Board
	Status GameStatus
	NextPlayer CellValue
}

var gameCounter int64

func NewGame() *Game {
	id := int(atomic.AddInt64(&gameCounter, 1))
	return &Game{
		ID: id,
		Board: Board{},
		Status: StatusInProgress,
		NextPlayer: X,
	}
}
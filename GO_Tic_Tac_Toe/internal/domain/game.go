package domain

import (
	"time"

	"github.com/google/uuid"
)

type Game struct {
	ID         uuid.UUID
	Board      Board
	Status     GameStatus
	NextPlayer CellValue
	PlayerXID  *uuid.UUID
	PlayerOID  *uuid.UUID
	WinnerID   *uuid.UUID
	CreatedAt  time.Time
}

type WinRate struct {
	UserID   uuid.UUID
	Username string
	WinRate  float64
}

func NewGameWithComputer(playerID uuid.UUID) *Game {
	return &Game{
		ID:         uuid.New(),
		Board:      Board{},
		Status:     StatusInProgress,
		NextPlayer: X,
		PlayerXID:  &playerID,
		PlayerOID:  nil,
		WinnerID:   nil,
		CreatedAt:  time.Now(),
	}
}

func NewGameWithPlayer(hostID uuid.UUID) *Game {
	return &Game{
		ID:         uuid.New(),
		Board:      Board{},
		Status:     StatusWaiting,
		NextPlayer: X,
		PlayerXID:  &hostID,
		PlayerOID:  nil,
		WinnerID:   nil,
		CreatedAt:  time.Now(),
	}
}

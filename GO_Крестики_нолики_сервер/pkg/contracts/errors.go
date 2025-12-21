package contracts

import "errors"

var (
    ErrGameNotFound     = errors.New("game not found")
    ErrInvalidMove      = errors.New("invalid move")
    ErrGameFinished     = errors.New("game is already finished")
    ErrNotPlayersTurn   = errors.New("not player's turn")
    ErrCellOccupied     = errors.New("cell is already occupied")
)
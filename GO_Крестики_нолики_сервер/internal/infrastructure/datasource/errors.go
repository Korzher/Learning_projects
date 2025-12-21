package datasource

import "errors"

var (
	ErrGameNotFound    = errors.New("game not found")
	ErrNilGame         = errors.New("game cannot be nil")
	ErrNilModel		   = errors.New("model cannot be nil")
	ErrInvalidGameData = errors.New("invalid game data")
)
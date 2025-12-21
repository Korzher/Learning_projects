package datasource

import (
	"sync"
	"tic-tac-toe/internal/domain"
)

type GameStorage struct {
	store *sync.Map
}

func NewGameStorage() *GameStorage{
	return &GameStorage{
		store: &sync.Map{},
	}
}

func (s *GameStorage) Save(game *domain.Game) error {
	if game == nil {
		return ErrNilGame
	}
	model, err := ToModel(game)
	if err != nil {
		return err
	}
	s.store.Store(game.ID, model)
	return nil
}

func (s *GameStorage) FindByID(id int) (*domain.Game, error) {
	value, ok := s.store.Load(id)
	if !ok {
		return nil, ErrGameNotFound
	}

	model, ok := value.(*GameModel)
	if !ok {
		return nil, ErrInvalidGameData
	}

	return ToDomain(model)
}

func(s *GameStorage) Delete(id int) {
	s.store.Delete(id)
}

package domain

type GameRepository interface {
	Save(game *Game) error
	FindByID(id int) (*Game, error)
	Delete(id int)
}
package datasource

type GameModel struct {
	ID         int
	Board      [3][3]int
	Status     string
	NextPlayer int
}
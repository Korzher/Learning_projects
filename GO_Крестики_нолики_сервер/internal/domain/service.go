package domain

type GameService interface {
	CreateGame() (*Game, error)
	GetGame(GameID int) (*Game, error)
	MakeMove(gameID, row, col int) (*Game, error)
	GetNextMove(gameID int, board Board) (Board, error)
	ValidateBoard(gameId int, newBoard Board) error
	CheckGameStatus(board Board) GameStatus
}
package service

import (
	"errors"
	"tic-tac-toe/internal/domain"
)

type gameService struct {
	repo domain.GameRepository
	minimax *MinimaxAlgorithm
}

func NewGameService(repo domain.GameRepository) domain.GameService {
	return &gameService{
		repo: repo,
		minimax: &MinimaxAlgorithm{},
	}
}

func (s *gameService) CreateGame() (*domain.Game, error) {
	game := domain.NewGame()
	if err := s.repo.Save(game); err != nil {
		return nil, err
	}
	return game, nil
}

func (s *gameService) GetGame(gameID int) (*domain.Game, error) {
	return s.repo.FindByID(gameID)
}

func (s *gameService) MakeMove(gameID int, row, col int) (*domain.Game, error) {
	game, err := s.repo.FindByID(gameID)
	if err != nil {
		return nil, err
	}

	if game.Status != domain.StatusInProgress {
		return nil, errors.New("game is already finished")
	}

	if game.NextPlayer != domain.X {
		return nil, errors.New("not player's turn")
	}

	newBoard := game.Board
	newBoard[row][col] = domain.X
	
	if err := s.ValidateBoard(gameID, newBoard); err != nil {
		return nil, err
	}
	
	game.Board = newBoard
	game.NextPlayer = domain.O
	game.Status = s.CheckGameStatus(game.Board)

	if game.Status == domain.StatusInProgress {
		computerBoard, err := s.GetNextMove(gameID, game.Board)
		if err != nil {
			return nil, err
		}

		game.Board = computerBoard
		game.NextPlayer = domain.X
		game.Status = s.CheckGameStatus(computerBoard)
	}

	if err := s.repo.Save(game); err != nil {
		return nil, err
	}

	return game, nil
}

func (s *gameService) GetNextMove(gameID int, board domain.Board) (domain.Board, error) {
	row, col, err := s.minimax.GetBestMove(board, domain.O)
	if err != nil {
		return domain.Board{}, err
	}

	newBoard := board
	newBoard[row][col] = domain.O
	return newBoard, nil
}

func (s *gameService) ValidateBoard(gameID int, newBoard domain.Board) error {
	game, err := s.repo.FindByID(gameID)
	if err != nil {
		return err
	}

	currentBoard := game.Board
	diffCount := 0

	for row := 0; row < 3; row++ {
		for col := 0; col < 3; col++ {
			if currentBoard[row][col] != newBoard[row][col] {
				if currentBoard[row][col] != domain.Empty {
					return errors.New("can not modify existibg cells")
				}
				if newBoard[row][col] != game.NextPlayer {
					return errors.New("wrong player move")
				}

				diffCount++
			}
		}
	}
	
	if diffCount != 1 {
		return errors.New("exactly one move must be made")
	}
	return nil
}

func (s *gameService) CheckGameStatus(board domain.Board) domain.GameStatus {
	for row := 0; row < 3; row++ {
		if board[row][0] != domain.Empty &&
		board[row][0] == board[row][1] &&
		board[row][1] == board[row][2] {
			if board[row][0] == domain.X {
				return domain.StatusXWin
			}
			return domain.StatusOWin
		}
	}

	for col := 0; col < 3; col++ {
		if board[0][col] != domain.Empty &&
		board[0][col] == board[1][col] &&
		board[1][col] == board[2][col] {
			if board[0][col] == domain.X {
				return domain.StatusXWin
			}
			return domain.StatusOWin
		}
	}

	if board[0][0] != domain.Empty &&
	board[0][0] == board[1][1] &&
	board[1][1] == board[2][2] {
		if board[0][0] == domain.X{
			return domain.StatusXWin
		}
		return domain.StatusOWin
	}

	if board[0][2] != domain.Empty &&
	board[0][2] == board[1][1] &&
	board[1][1] == board[2][0] {
		if board[0][2] == domain.X {
			return domain.StatusXWin
		}
		return domain.StatusOWin
	}

	for row := 0; row < 3; row++ {
		for col := 0; col < 3; col++ {
			if board[row][col] == domain.Empty {
				return domain.StatusInProgress
			}
		}
	}

	return domain.StatusDraw
}
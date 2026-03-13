package service

import (
	"context"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"

	"github.com/google/uuid"
)

type gameService struct {
	repo    domain.GameRepository
	minimax *MinimaxAlgorithm
}

func NewGameService(repo domain.GameRepository) domain.GameService {
	return &gameService{
		repo:    repo,
		minimax: &MinimaxAlgorithm{},
	}
}

func (s *gameService) CreateGame(ctx context.Context, gameType string) (*domain.Game, error) {
	playerID, ok := ctx.Value("user_id").(uuid.UUID)
	if !ok {
		return nil, contracts.ErrUserNotAuth
	}
	var game *domain.Game
	switch gameType {
	case "vs_computer":
		game = domain.NewGameWithComputer(playerID)
	case "vs_player":
		game = domain.NewGameWithPlayer(playerID)
	default:
		return nil, contracts.ErrInvGameType
	}

	if err := s.repo.Save(ctx, game); err != nil {
		return nil, err
	}
	return game, nil
}

func (s *gameService) GetGame(ctx context.Context, gameID uuid.UUID) (*domain.Game, error) {
	return s.repo.FindByID(ctx, gameID)
}

func (s *gameService) MakeMove(ctx context.Context, gameID uuid.UUID, row, col int) (*domain.Game, error) {
	game, err := s.repo.FindByID(ctx, gameID)
	if err != nil {
		return nil, err
	}

	if game.Status != domain.StatusInProgress {
		return nil, contracts.ErrNotInProg
	}

	currentPlayerID, ok := ctx.Value("user_id").(uuid.UUID)
	if !ok {
		return nil, contracts.ErrUserNotAuth
	}

	if !s.isPlayerTurn(game, currentPlayerID) {
		return nil, contracts.ErrNotPlayersTurn
	}

	if game.Board[row][col] != domain.Empty {
		return nil, contracts.ErrCellOccupied
	}

	newBoard := game.Board
	newBoard[row][col] = game.NextPlayer
	game.Board = newBoard
	game.Status = s.CheckGameStatus(game.Board)

	if game.Status == domain.StatusXWin && game.PlayerXID != nil {
		game.WinnerID = game.PlayerXID
	} else if game.Status == domain.StatusOWin && game.PlayerOID != nil {
		game.WinnerID = game.PlayerOID
	}

	if game.Status == domain.StatusInProgress {
		if game.NextPlayer == domain.X {
			game.NextPlayer = domain.O
		} else {
			game.NextPlayer = domain.X
		}

		if game.NextPlayer == domain.O && game.PlayerOID == nil {
			computerBoard, err := s.GetNextMove(gameID, game.Board)
			if err != nil {
				return nil, err
			}

			game.Board = computerBoard
			game.Status = s.CheckGameStatus(computerBoard)
			if game.Status == domain.StatusOWin {
				game.WinnerID = nil
			}
			if game.Status == domain.StatusInProgress {
				game.NextPlayer = domain.X
			}
		}
	}

	if err := s.repo.Save(ctx, game); err != nil {
		return nil, err
	}

	return game, nil
}

func (s *gameService) GetNextMove(gameID uuid.UUID, board domain.Board) (domain.Board, error) {
	row, col, err := s.minimax.GetBestMove(board, domain.O)
	if err != nil {
		return domain.Board{}, err
	}

	newBoard := board
	newBoard[row][col] = domain.O
	return newBoard, nil
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
		if board[0][0] == domain.X {
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

func (s *gameService) GetAvailableGames(ctx context.Context) ([]*domain.Game, error) {
	games, err := s.repo.FindWaitingGames(ctx)
	if err != nil {
		return nil, err
	}

	currentUserID, ok := ctx.Value("user_id").(uuid.UUID)
	if ok {
		filteredGames := []*domain.Game{}
		for _, game := range games {
			if game.PlayerXID != nil && *game.PlayerXID == currentUserID {
				continue
			}
			filteredGames = append(filteredGames, game)
		}
		return filteredGames, nil
	}
	return games, nil
}

func (s *gameService) GetGamesFinishedByID(ctx context.Context, userID uuid.UUID) ([]*domain.Game, error) {
	games, err := s.repo.FindFinishedByUserID(ctx, userID)
	if err != nil {
		return nil, err
	}

	return games, nil
}

func (s *gameService) JoinGame(ctx context.Context, gameID uuid.UUID) (*domain.Game, error) {
	game, err := s.repo.FindByID(ctx, gameID)
	if err != nil {
		return nil, err
	}

	if game.Status != domain.StatusWaiting {
		return nil, contracts.ErrGameNotWait
	}

	playerID, ok := ctx.Value("user_id").(uuid.UUID)
	if !ok {
		return nil, contracts.ErrUserNotAuth
	}

	if game.PlayerXID != nil && *game.PlayerXID == playerID {
		return nil, contracts.ErrYourOwnGame
	}

	game.PlayerOID = &playerID
	game.Status = domain.StatusInProgress

	if err := s.repo.Save(ctx, game); err != nil {
		return nil, err
	}

	return game, nil
}

func (s *gameService) GetLeaderBoard(ctx context.Context, limit int) ([]*domain.WinRate, error) {
	winrate, err := s.repo.GetLeaderBoard(ctx, limit)
	if err != nil {
		return nil, err
	}
	return winrate, nil
}

func (s *gameService) isPlayerTurn(game *domain.Game, playerID uuid.UUID) bool {
	if game.NextPlayer == domain.X && game.PlayerXID != nil && *game.PlayerXID == playerID {
		return true
	}
	if game.NextPlayer == domain.O && game.PlayerOID != nil && *game.PlayerOID == playerID {
		return true
	}
	return false
}

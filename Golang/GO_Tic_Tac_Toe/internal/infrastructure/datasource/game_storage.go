package datasource

import (
	"context"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"

	"github.com/google/uuid"
	"github.com/jackc/pgx/v5"
	"github.com/jackc/pgx/v5/pgxpool"
)

type GameStorage struct {
	pool *pgxpool.Pool
}

func NewGameStorage(pool *pgxpool.Pool) *GameStorage {
	return &GameStorage{
		pool: pool,
	}
}

func (s *GameStorage) Save(ctx context.Context, game *domain.Game) error {
	if game == nil {
		return contracts.ErrNilGame
	}

	model, err := ToModel(game)
	if err != nil {
		return err
	}

	query := `
	INSERT INTO games (game_id, board, status, next_player, player_x_id, player_o_id, winner_id)
	VALUES ($1, $2, $3, $4, $5, $6, $7)
	ON CONFLICT (game_id)
	DO UPDATE SET
		board = EXCLUDED.board,
		status = EXCLUDED.status,
		next_player = EXCLUDED.next_player,
		player_x_id = EXCLUDED.player_x_id,
		player_o_id = EXCLUDED.player_o_id,
		winner_id = EXCLUDED.winner_id,
		updated_at = CURRENT_TIMESTAMP
		RETURNING id
	`

	var dbID int

	err = s.pool.QueryRow(ctx, query,
		model.GameID,
		model.Board,
		model.Status,
		model.NextPlayer,
		model.PlayerXID,
		model.PlayerOID,
		model.WinnerID).Scan(&dbID)

	if err != nil {
		return contracts.ErrFailedToUpdate
	}

	return nil
}

func (s *GameStorage) FindByID(ctx context.Context, id uuid.UUID) (*domain.Game, error) {
	query := `
		SELECT game_id, board, status, next_player, player_x_id, player_o_id, winner_id, created_at
		FROM games
		WHERE game_id = $1
		`

	var model GameModel

	err := s.pool.QueryRow(ctx, query, id.String()).Scan(
		&model.GameID,
		&model.Board,
		&model.Status,
		&model.NextPlayer,
		&model.PlayerXID,
		&model.PlayerOID,
		&model.WinnerID,
		&model.CreatedAt,
	)

	if err == pgx.ErrNoRows {
		return nil, contracts.ErrGameNotFound
	}
	if err != nil {
		return nil, contracts.ErrFailedToQueryG
	}

	return ToDomain(&model)
}

func (s *GameStorage) FindWaitingGames(ctx context.Context) ([]*domain.Game, error) {
	query := `
	SELECT game_id, board, status, next_player, player_x_id, player_o_id, winner_id, created_at
	FROM games
	WHERE status = $1
	ORDER BY game_id ASC
	`

	rows, err := s.pool.Query(ctx, query, domain.StatusWaiting)
	if err != nil {
		return nil, contracts.ErrFailedToQueryG
	}
	defer rows.Close()

	var games []*domain.Game
	for rows.Next() {
		var model GameModel
		err := rows.Scan(
			&model.GameID,
			&model.Board,
			&model.Status,
			&model.NextPlayer,
			&model.PlayerXID,
			&model.PlayerOID,
			&model.WinnerID,
			&model.CreatedAt,
		)
		if err != nil {
			return nil, contracts.ErrFailedScan
		}

		game, err := ToDomain(&model)
		if err != nil {
			return nil, err
		}
		games = append(games, game)
	}
	return games, nil
}

func (s *GameStorage) FindFinishedByUserID(ctx context.Context, userID uuid.UUID) ([]*domain.Game, error) {
	query := `
	SELECT game_id, board, status, next_player, player_x_id, player_o_id, winner_id, created_at
	FROM games
	WHERE
		(winner_id = $1)
		OR (status = $2 AND (player_x_id = $1 OR player_o_id = $1))
	ORDER BY created_at DESC
	`

	rows, err := s.pool.Query(ctx, query, userID, domain.StatusDraw)
	if err != nil {
		return nil, contracts.ErrFailedToQueryG
	}
	defer rows.Close()

	var games []*domain.Game
	for rows.Next() {
		var model GameModel
		err := rows.Scan(
			&model.GameID,
			&model.Board,
			&model.Status,
			&model.NextPlayer,
			&model.PlayerXID,
			&model.PlayerOID,
			&model.WinnerID,
			&model.CreatedAt,
		)
		if err != nil {
			return nil, contracts.ErrFailedScan
		}

		game, err := ToDomain(&model)
		if err != nil {
			return nil, err
		}
		games = append(games, game)
	}
	return games, nil
}

func (s *GameStorage) GetLeaderBoard(ctx context.Context, limit int) ([]*domain.WinRate, error) {
	query := `
	WITH stats AS (
  		SELECT
    		u.id,
			u.username,
			SUM(CASE WHEN g.winner_id = u.id THEN 1 ELSE 0 END) AS wins,
			SUM(CASE WHEN g.winner_id IS NOT NULL AND g.winner_id != u.id AND (g.player_x_id = u.id OR g.player_o_id = u.id) THEN 1 ELSE 0 END) AS losses,
			SUM(CASE WHEN g.status = $1 AND (g.player_x_id = u.id OR g.player_o_id = u.id) THEN 1 ELSE 0 END) AS draws
		FROM users u
		LEFT JOIN games g
			ON g.player_x_id = u.id OR g.player_o_id = u.id
		GROUP BY u.id, u.username
		)
		SELECT
		id,
		username,
		CASE
			WHEN (losses + draws) = 0 AND wins > 0 THEN 100.0
			WHEN (losses + draws) = 0 AND wins = 0 THEN 0.0
			ELSE wins::float / (losses + draws) * 100
		END AS win_rate
		FROM stats
		ORDER BY win_rate DESC
		LIMIT $2	
	`

	rows, err := s.pool.Query(ctx, query, domain.StatusDraw, limit)
	if err != nil {
		return nil, contracts.ErrFailedToQueryG
	}

	defer rows.Close()
	var wr []*domain.WinRate
	for rows.Next() {
		winrate := &domain.WinRate{}
		err := rows.Scan(&winrate.UserID,
			&winrate.Username,
			&winrate.WinRate)
		if err != nil {
			return nil, contracts.ErrFailedScan
		}
		wr = append(wr, winrate)
	}
	return wr, nil
}

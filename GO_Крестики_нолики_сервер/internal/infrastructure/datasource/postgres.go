package datasource

import (
	"context"
	"fmt"
	"os"
	"tic-tac-toe/pkg/contracts"

	"github.com/jackc/pgx/v5/pgxpool"
	"go.uber.org/fx"
)

type Config struct {
	Host     string
	Port     string
	User     string
	Password string
	Database string
	SSLMode  string
}

func NewPostgresConfig() *Config {
	host := os.Getenv("DB_HOST")
	if host == "" {
		host = "localhost"
	}

	return &Config{
		Host:     host,
		Port:     "5432",
		User:     "postgres",
		Password: "postgres",
		Database: "tictactoe",
		SSLMode:  "disable",
	}
}

func NewPostgresPool(lc fx.Lifecycle, config *Config) (*pgxpool.Pool, error) {
	connString := fmt.Sprintf(
		"postgres://%s:%s@%s:%s/%s?sslmode=%s",
		config.User,
		config.Password,
		config.Host,
		config.Port,
		config.Database,
		config.SSLMode,
	)

	poolConfig, err := pgxpool.ParseConfig(connString)
	if err != nil {
		return nil, contracts.ErrFailedParseDB
	}

	pool, err := pgxpool.NewWithConfig(context.Background(), poolConfig)
	if err != nil {
		return nil, contracts.ErrFailedCon
	}

	if err := pool.Ping(context.Background()); err != nil {
		return nil, contracts.ErrFailedPing
	}

	lc.Append(fx.Hook{
		OnStop: func(ctx context.Context) error {
			fmt.Println("Closing database connection")
			pool.Close()
			return nil
		},
	})
	return pool, nil
}

func CreateTable(lc fx.Lifecycle, pool *pgxpool.Pool) {
	lc.Append(fx.Hook{
		OnStart: func(ctx context.Context) error {
			usersTableSQL := `
			CREATE TABLE IF NOT EXISTS users (
				id UUID PRIMARY KEY,
				username VARCHAR(50) NOT NULL UNIQUE,
				password VARCHAR(255) NOT NULL,
				created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
			);
			`

			gamesTableSQL := `
			CREATE TABLE IF NOT EXISTS games (
				id SERIAL PRIMARY KEY,
				game_id TEXT NOT NULL UNIQUE,
				board TEXT NOT NULL,
				status VARCHAR(20) NOT NULL,
				next_player INTEGER NOT NULL,
				player_x_id UUID,
				player_o_id UUID,
				winner_id UUID,
				created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
			);
			`

			_, err := pool.Exec(ctx, usersTableSQL)
			if err != nil {
				return contracts.ErrFailedTable
			}

			_, err = pool.Exec(ctx, gamesTableSQL)
			if err != nil {
				return contracts.ErrFailedTable
			}

			return nil
		},
	})
}

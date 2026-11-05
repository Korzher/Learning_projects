package datasource

import (
	"context"
	"errors"
	"fmt"
	"os"

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
		Database: "grpc_auth",
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
		return nil, errors.New("failed to parse db-connection string")
	}

	pool, err := pgxpool.NewWithConfig(context.Background(), poolConfig)
	if err != nil {
		return nil, errors.New("failed to create connection")
	}

	if err := pool.Ping(context.Background()); err != nil {
		return nil, errors.New("failed to ping db")
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

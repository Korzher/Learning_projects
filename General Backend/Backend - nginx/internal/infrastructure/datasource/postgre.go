package datasource

import (
	"context"
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

func NewPostgreConfig() *Config {
	host := os.Getenv("DB_HOST")
	if host == "" {
		host = "localhost"
	}

	return &Config{
		Host:     host,
		Port:     "5432",
		User:     "postgres",
		Password: "postgres",
		Database: "techshop",
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
		return nil, err
	}

	pool, err := pgxpool.NewWithConfig(context.Background(), poolConfig)
	if err != nil {
		return nil, err
	}

	if err := pool.Ping(context.Background()); err != nil {
		return nil, err
	}

	lc.Append(fx.Hook{
		OnStop: func(ctx context.Context) error {
			fmt.Println("Closing Database connection")
			pool.Close()
			return nil
		},
	})
	return pool, nil
}

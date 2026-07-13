package datasource

import (
	"context"
	"fmt"
	"os"

	"github.com/jackc/pgx/v5/pgxpool"
)

func NewShardedPools() ([4]*pgxpool.Pool, error) {
	pools := [4]*pgxpool.Pool{}
	dbHost := os.Getenv("DB_HOST")
	if dbHost == "" {
		dbHost = "localhost"
	}

	for i := 0; i < 4; i++ {
		connStr := fmt.Sprintf(
			"postgres://postgres:postgres@%s:5432/images_shard_%d?sslmode=disable",
			dbHost, i,
		)

		pool, err := pgxpool.New(context.Background(), connStr)
		if err != nil {
			return [4]*pgxpool.Pool{}, err
		}
		pools[i] = pool
	}
	return pools, nil
}

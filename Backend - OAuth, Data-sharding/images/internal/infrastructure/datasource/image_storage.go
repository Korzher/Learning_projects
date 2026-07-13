package datasource

import (
	"context"
	"errors"
	"images/internal/domain"

	"github.com/google/uuid"
	"github.com/jackc/pgx/v5/pgxpool"
)

type ImageStorage struct {
	pools [4]*pgxpool.Pool
}

func NewImageStorage(pools [4]*pgxpool.Pool) domain.ImageRepository {
	return &ImageStorage{pools: pools}
}

func (s *ImageStorage) getShardIndex(id uuid.UUID) int {
	firstChar := id.String()[0]
	var sum int
	if firstChar >= '0' && firstChar <= '9' {
		sum = int(firstChar - '0')
	} else if firstChar >= 'a' && firstChar <= 'f' {
		sum = int(firstChar - 'a' + 10)
	}
	return sum / 4
}

func (s *ImageStorage) AddImage(ctx context.Context, image []byte) (uuid.UUID, error) {
	id := uuid.New()
	shardIndex := s.getShardIndex(id)
	pool := s.pools[shardIndex]

	query := "INSERT INTO images (id, data) VALUES ($1, $2)"
	_, err := pool.Exec(ctx, query, id, image)
	if err != nil {
		return uuid.Nil, err
	}
	return id, nil
}

func (s *ImageStorage) ChangeImage(ctx context.Context, image []byte, imageID uuid.UUID) error {
	shardIndex := s.getShardIndex(imageID)
	pool := s.pools[shardIndex]

	query := "UPDATE images SET data = $1 WHERE id = $2"
	_, err := pool.Exec(ctx, query, image, imageID)
	return err
}

func (s *ImageStorage) DeleteImage(ctx context.Context, imageID uuid.UUID) error {
	shardIndex := s.getShardIndex(imageID)
	pool := s.pools[shardIndex]

	query := "DELETE FROM images WHERE id = $1"
	result, err := pool.Exec(ctx, query, imageID)
	if err != nil {
		return err
	}
	if result.RowsAffected() == 0 {
		return errors.New("id does not exist")
	}
	return nil
}

func (s *ImageStorage) GetImageByIID(ctx context.Context, imageID uuid.UUID) ([]byte, error) {
	shardIndex := s.getShardIndex(imageID)
	pool := s.pools[shardIndex]

	var data []byte
	query := "SELECT data FROM images WHERE id = $1"
	err := pool.QueryRow(ctx, query, imageID).Scan(&data)
	if err != nil {
		return nil, err
	}
	return data, nil
}

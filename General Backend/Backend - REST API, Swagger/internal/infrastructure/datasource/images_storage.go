package datasource

import (
	"apifromspec/internal/pkg"
	"context"
	"database/sql"
	"errors"
	"fmt"

	"github.com/google/uuid"
)

type ImageStorage struct {
	db DBExecutor
}

func NewImageStorage(db DBExecutor) *ImageStorage {
	return &ImageStorage{
		db: db,
	}
}

func (i *ImageStorage) AddImage(ctx context.Context, image []byte) (uuid.UUID, error) {
	id := uuid.New()
	_, err := i.db.Exec(ctx, `
	INSERT INTO image_table (id, image)
	VALUES ($1, $2)
	`, id, image)
	if err != nil {
		return uuid.Nil, err
	}
	return id, err
}

func (i *ImageStorage) ChangeImage(ctx context.Context, image []byte, imageID uuid.UUID) error {
	res, err := i.db.Exec(ctx, `
	UPDATE image_table
	SET image = $2
	WHERE id = $1
	`, imageID, image)
	if err != nil {
		return err
	}
	if res.RowsAffected() == 0 {
		return pkg.ErrImageNotFound
	}
	return nil
}

func (i *ImageStorage) DeleteImage(ctx context.Context, imageID uuid.UUID) error {
	res, err := i.db.Exec(ctx, `
		DELETE FROM image_table
		WHERE id = $1
		`, imageID)
	if err != nil {
		return err
	}
	if res.RowsAffected() == 0 {
		return errors.New("ID does not exist")
	}
	return nil
}

func (i *ImageStorage) GetImageByPID(ctx context.Context, productID uuid.UUID) ([]byte, error) {
	var img []byte
	err := i.db.QueryRow(ctx, `
	SELECT it.image
	FROM product_table pt
	JOIN image_table it ON pt.image_id = it.id
	WHERE pt.id = $1`, productID).Scan(&img)
	if err != nil {
		if errors.Is(err, sql.ErrNoRows) {
			return nil, pkg.ErrImageNotFound
		}
		return nil, fmt.Errorf("failed to get image for product %s: %w", productID, err)
	}
	return img, nil
}

func (i *ImageStorage) GetImageByIID(ctx context.Context, imageID uuid.UUID) ([]byte, error) {
	var img []byte
	err := i.db.QueryRow(ctx, `
	SELECT image
	FROM image_table
	WHERE id = $1`, imageID).Scan(&img)
	if err != nil {
		if errors.Is(err, sql.ErrNoRows) {
			return nil, pkg.ErrImageNotFound
		}
		return nil, fmt.Errorf("failed to get image with id %s: %w", imageID, err)
	}
	return img, nil
}

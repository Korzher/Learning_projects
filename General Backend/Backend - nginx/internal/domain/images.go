package domain

import (
	"context"

	"github.com/google/uuid"
)

type Image struct {
	ID    uuid.UUID
	Image []byte
}

type ImageRepository interface {
	AddImage(ctx context.Context, image []byte) (uuid.UUID, error)
	ChangeImage(ctx context.Context, image []byte, ImageID uuid.UUID) error
	DeleteImage(ctx context.Context, imageID uuid.UUID) error
	GetImageByPID(ctx context.Context, ProductID uuid.UUID) ([]byte, error)
	GetImageByIID(ctx context.Context, ImageID uuid.UUID) ([]byte, error)
}

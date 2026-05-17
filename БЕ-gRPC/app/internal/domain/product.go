package domain

import (
	"context"
	"time"

	"github.com/google/uuid"
)

type Product struct {
	ID             uuid.UUID
	Name           string
	Category       string
	Price          int64
	AvailableStock int
	SupplierID     uuid.UUID
	ImageID        uuid.UUID
	LastUpdateDate time.Time
}

type ProductRepository interface {
	AddProduct(ctx context.Context, product *Product) error
	SubtractProduct(ctx context.Context, id uuid.UUID, amount int) error
	GetProduct(ctx context.Context, id uuid.UUID) (Product, error)
	GetAllProducts(ctx context.Context) ([]Product, error)
	DeleteProduct(ctx context.Context, id uuid.UUID) error
}

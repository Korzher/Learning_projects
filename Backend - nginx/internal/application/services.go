package application

import (
	"apifromspec/internal/domain"
	"apifromspec/internal/infrastructure/datasource"
	"context"
	"fmt"

	"github.com/google/uuid"
	"github.com/jackc/pgx/v5"
	"github.com/jackc/pgx/v5/pgxpool"
)

type ProductService struct {
	pool           *pgxpool.Pool
	imageStorage   domain.ImageRepository
	productStorage domain.ProductRepository
}

func NewProductService(
	pool *pgxpool.Pool,
	is domain.ImageRepository,
	ps domain.ProductRepository,
) *ProductService {
	return &ProductService{
		pool:           pool,
		imageStorage:   is,
		productStorage: ps,
	}
}

func (s *ProductService) CreateProduct(ctx context.Context, product *domain.Product, image []byte) error {
	tx, err := s.pool.BeginTx(ctx, pgx.TxOptions{})
	if err != nil {
		return err
	}
	defer tx.Rollback(ctx)

	imageRepo := datasource.NewImageStorage(tx)
	productRepo := datasource.NewProductStorage(tx)

	if len(image) > 0 {
		imageID, err := imageRepo.AddImage(ctx, image)
		if err != nil {
			return fmt.Errorf("failed to add image: %w", err)
		}
		product.ImageID = imageID
	}

	if err := productRepo.AddProduct(ctx, product); err != nil {
		return fmt.Errorf("failed to add product: %w", err)
	}

	if err := tx.Commit(ctx); err != nil {
		return fmt.Errorf("commit failed: %w", err)
	}
	return nil
}

func (s *ProductService) AddImageToProduct(ctx context.Context, productID uuid.UUID, image []byte) error {
	tx, err := s.pool.BeginTx(ctx, pgx.TxOptions{})
	if err != nil {
		return err
	}
	defer tx.Rollback(ctx)

	imageRepoTX := datasource.NewImageStorage(tx)
	productRepoTx := datasource.NewProductStorage(tx)

	imageID, err := imageRepoTX.AddImage(ctx, image)
	if err != nil {
		return err
	}

	if err := productRepoTx.SetProductImage(ctx, productID, imageID); err != nil {
		return err
	}

	if err := tx.Commit(ctx); err != nil {
		return err
	}
	return nil
}

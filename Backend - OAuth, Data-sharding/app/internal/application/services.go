package application

import (
	"apifromspec/internal/domain"
	"apifromspec/internal/infrastructure/web/images"
	"context"
	"fmt"

	"github.com/google/uuid"
)

type ProductService struct {
	productStorage domain.ProductRepository
	imagesClient   *images.Client
}

func NewProductService(
	ps domain.ProductRepository,
	ic *images.Client,
) *ProductService {
	return &ProductService{
		productStorage: ps,
		imagesClient:   ic,
	}
}

func (s *ProductService) CreateProduct(ctx context.Context, product *domain.Product, image []byte) error {
	if len(image) > 0 {
		imageID, err := s.imagesClient.AddImage(ctx, image)
		if err != nil {
			return fmt.Errorf("failed to add image: %w", err)
		}
		parsedId, err := uuid.Parse(imageID)
		product.ImageID = parsedId
	}

	if err := s.productStorage.AddProduct(ctx, product); err != nil {
		return fmt.Errorf("failed to add product: %w", err)
	}
	return nil
}

func (s *ProductService) AddImageToProduct(ctx context.Context, productID uuid.UUID, image []byte) error {
	imageID, err := s.imagesClient.AddImage(ctx, image)
	if err != nil {
		return err
	}

	parsedID, err := uuid.Parse(imageID)
	if err != nil {
		return err
	}

	return s.productStorage.SetProductImage(ctx, productID, parsedID)
}

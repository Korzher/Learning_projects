package application

import (
	"apifromspec/internal/domain"
	"context"
	"fmt"

	"github.com/google/uuid"
)

type ImageService interface {
	AddImage(ctx context.Context, image []byte) (string, error)
}

type ProductService struct {
	productStorage domain.ProductRepository
	imagesClient   ImageService
}

func NewProductService(
	ps domain.ProductRepository,
	ic ImageService,
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
		if err != nil {
			return err
		}
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

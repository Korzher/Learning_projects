package application

import (
	"context"
	"errors"
	"testing"

	"apifromspec/internal/domain"

	"github.com/google/uuid"
)

type fakeImageService struct {
	imageID string
	err     error
}

func (f fakeImageService) AddImage(_ context.Context, _ []byte) (string, error) {
	return f.imageID, f.err
}

type fakeProductStorage struct {
	added    []*domain.Product
	setImage []struct{ productID, imageID uuid.UUID }
	err      error
}

func (f *fakeProductStorage) AddProduct(_ context.Context, p *domain.Product) error {
	if f.err != nil {
		return f.err
	}
	f.added = append(f.added, p)
	return nil
}

func (f *fakeProductStorage) SetProductImage(_ context.Context, pID, iID uuid.UUID) error {
	if f.err != nil {
		return f.err
	}
	f.setImage = append(f.setImage, struct{ productID, imageID uuid.UUID }{pID, iID})
	return nil
}

func (f *fakeProductStorage) SubtractProduct(_ context.Context, _ uuid.UUID, _ int) error { return nil }
func (f *fakeProductStorage) GetProduct(_ context.Context, _ uuid.UUID) (domain.Product, error) {
	return domain.Product{}, nil
}
func (f *fakeProductStorage) GetAllProducts(_ context.Context) ([]domain.Product, error) {
	return nil, nil
}
func (f *fakeProductStorage) DeleteProduct(_ context.Context, _ uuid.UUID) error { return nil }

func TestCreateProductWithImage(t *testing.T) {
	storage := &fakeProductStorage{}
	s := NewProductService(storage, fakeImageService{imageID: uuid.New().String()})

	prod := &domain.Product{Name: "Laptop Air"}
	if err := s.CreateProduct(context.Background(), prod, []byte{1, 2, 3}); err != nil {
		t.Fatalf("CreateProduct() error = %v", err)
	}

	if prod.ImageID == uuid.Nil {
		t.Error("CreateProduct() must set ImageID when image is provided")
	}
	if len(storage.added) != 1 {
		t.Fatalf("AddProduct called %d times, want 1", len(storage.added))
	}
}

func TestCreateProductImageError(t *testing.T) {
	storage := &fakeProductStorage{}
	s := NewProductService(storage, fakeImageService{err: errors.New("grpc unavailable")})

	prod := &domain.Product{Name: "Laptop"}
	if err := s.CreateProduct(context.Background(), prod, []byte{1}); err == nil {
		t.Fatal("CreateProduct() expected error when image service fails, got nil")
	}
	if len(storage.added) != 0 {
		t.Fatal("product must not be added if image upload failed")
	}
}

func TestCreateProductWithoutImage(t *testing.T) {
	storage := &fakeProductStorage{}
	s := NewProductService(storage, fakeImageService{})

	prod := &domain.Product{Name: "Laptop"}
	if err := s.CreateProduct(context.Background(), prod, nil); err != nil {
		t.Fatalf("CreateProduct() error = %v", err)
	}
	if len(storage.added) != 1 {
		t.Fatalf("AddProduct called %d times, want 1", len(storage.added))
	}
	if prod.ImageID != uuid.Nil {
		t.Error("ImageID must stay nil when no image provided")
	}
}

func TestAddImageToProduct(t *testing.T) {
	storage := &fakeProductStorage{}
	imageID := uuid.New().String()
	s := NewProductService(storage, fakeImageService{imageID: imageID})

	productID := uuid.New()
	if err := s.AddImageToProduct(context.Background(), productID, []byte{9, 9}); err != nil {
		t.Fatalf("AddImageToProduct() error = %v", err)
	}

	if len(storage.setImage) != 1 {
		t.Fatalf("SetProductImage called %d times, want 1", len(storage.setImage))
	}
	if storage.setImage[0].productID != productID {
		t.Errorf("SetProductImage productID = %v, want %v", storage.setImage[0].productID, productID)
	}
	if storage.setImage[0].imageID.String() != imageID {
		t.Errorf("SetProductImage imageID = %v, want %s", storage.setImage[0].imageID, imageID)
	}
}

func TestAddImageToProductFixedError(t *testing.T) {
	storage := &fakeProductStorage{}
	s := NewProductService(storage, fakeImageService{imageID: "not-a-uuid"})

	if err := s.AddImageToProduct(context.Background(), uuid.New(), []byte{1}); err == nil {
		t.Fatal("AddImageToProduct() expected error for invalid image ID, got nil")
	}
	if len(storage.setImage) != 0 {
		t.Fatal("SetProductImage must not be called when image ID is invalid")
	}
}

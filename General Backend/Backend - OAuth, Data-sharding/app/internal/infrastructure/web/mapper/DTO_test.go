package mapper

import (
	"testing"
	"time"

	"apifromspec/internal/domain"
	"apifromspec/internal/pkg"

	"github.com/google/uuid"
)

func TestCollectResponse(t *testing.T) {
	now := time.Now()
	clients := []domain.Client{
		{
			ID:               uuid.New(),
			ClientName:       "Ivan",
			ClientSurname:    "Petrov",
			Birthday:         now,
			Gender:           domain.Male,
			RegistrationDate: now,
			AddressID:        uuid.New(),
		},
		{
			ID:               uuid.New(),
			ClientName:       "Anna",
			ClientSurname:    "Sidorova",
			Birthday:         now,
			Gender:           domain.Female,
			RegistrationDate: now,
			AddressID:        uuid.New(),
		},
	}

	res := CollectResponse(clients)

	if len(res) != len(clients) {
		t.Fatalf("CollectResponse() length = %d, want %d", len(res), len(clients))
	}
	for i, got := range res {
		want := clients[i]
		if got.ID != want.ID {
			t.Errorf("res[%d].ID = %v, want %v", i, got.ID, want.ID)
		}
		if got.ClientName != want.ClientName {
			t.Errorf("res[%d].ClientName = %q, want %q", i, got.ClientName, want.ClientName)
		}
		if got.ClientSurname != want.ClientSurname {
			t.Errorf("res[%d].ClientSurname = %q, want %q", i, got.ClientSurname, want.ClientSurname)
		}
		if !got.Birthday.Equal(want.Birthday) {
			t.Errorf("res[%d].Birthday = %v, want %v", i, got.Birthday, want.Birthday)
		}
		if got.Gender != want.Gender {
			t.Errorf("res[%d].Gender = %q, want %q", i, got.Gender, want.Gender)
		}
		if got.AddressID != want.AddressID {
			t.Errorf("res[%d].AddressID = %v, want %v", i, got.AddressID, want.AddressID)
		}
		if !got.RegistrationDate.Equal(want.RegistrationDate) {
			t.Errorf("res[%d].RegistrationDate = %v, want %v", i, got.RegistrationDate, want.RegistrationDate)
		}
	}
}

func TestCollectResponseEmpty(t *testing.T) {
	res := CollectResponse(nil)
	if res == nil || len(res) != 0 {
		t.Fatalf("CollectResponse(nil) = %v, want empty non-nil slice", res)
	}
}

func TestReqToProduct(t *testing.T) {
	supplierID := uuid.New()

	req := pkg.AddProductRequest{
		Name:           "Laptop Air",
		Category:       "Laptops",
		Price:          120000,
		AvailableStock: 10,
		SupplierID:     supplierID,
		Image:          []byte{1, 2, 3},
	}

	prod, image := ReqToProduct(req)

	if prod == nil {
		t.Fatal("ReqToProduct() returned nil product")
	}
	if prod.ID == uuid.Nil {
		t.Error("ReqToProduct() must assign a new UUID id")
	}
	if prod.Name != req.Name || prod.Category != req.Category {
		t.Errorf("ReqToProduct() mapped name/category incorrectly: %+v", prod)
	}
	if prod.Price != req.Price {
		t.Errorf("ReqToProduct() price = %d, want %d", prod.Price, req.Price)
	}
	if prod.AvailableStock != req.AvailableStock {
		t.Errorf("ReqToProduct() stock = %d, want %d", prod.AvailableStock, req.AvailableStock)
	}
	if prod.SupplierID != supplierID {
		t.Errorf("ReqToProduct() supplierID = %v, want %v", prod.SupplierID, supplierID)
	}
	if prod.ImageID != uuid.Nil {
		t.Errorf("ReqToProduct() ImageID = %v, want nil", prod.ImageID)
	}
	if len(image) != 3 || image[0] != 1 {
		t.Errorf("ReqToProduct() image passthrough wrong: %v", image)
	}
}

package handler

import (
	"apifromspec/internal/domain"
	"apifromspec/internal/pkg"
	"testing"
	"time"

	"github.com/google/uuid"
)

func TestValidateClientRequest(t *testing.T) {
	yesterday := time.Now().Add(-24 * time.Hour)
	tomorrow := time.Now().Add(24 * time.Hour)

	tests := []struct {
		name    string
		req     *pkg.AddClientRequest
		wantErr bool
	}{
		{
			name: "valid request",
			req: &pkg.AddClientRequest{
				ClientName:    "Ivan",
				ClientSurname: "Ivanov",
				Birthday:      yesterday,
				Gender:        domain.Male,
				Country:       "Russia",
				City:          "Moscow",
				Street:        "Lenina",
			},
			wantErr: false,
		},
		{
			name: "missing name",
			req: &pkg.AddClientRequest{
				ClientSurname: "Vasilieva",
				Birthday:      yesterday,
				Gender:        domain.Female,
				Country:       "Russia",
				City:          "Saint-Petersburg",
				Street:        "Sennaya",
			},
			wantErr: true,
		},
		{
			name: "missing surname",
			req: &pkg.AddClientRequest{
				ClientName: "Ivan",
				Birthday:   yesterday,
				Gender:     domain.Male,
				Country:    "Russia",
				City:       "Saint-Petersburg",
				Street:     "Sennaya",
			},
			wantErr: true,
		},
		{
			name: "missing birthday",
			req: &pkg.AddClientRequest{
				ClientName:    "Anastasiya",
				ClientSurname: "Vasilieva",
				Gender:        domain.Female,
				Country:       "Russia",
				City:          "Saint-Petersburg",
				Street:        "Sennaya",
			},
			wantErr: true,
		},
		{
			name: "birthday in the future",
			req: &pkg.AddClientRequest{
				ClientName:    "Anastasiya",
				ClientSurname: "Vasilieva",
				Birthday:      tomorrow,
				Gender:        domain.Female,
				Country:       "Russia",
				City:          "Saint-Petersburg",
				Street:        "Sennaya",
			},
			wantErr: true,
		},
		{
			name: "missing country",
			req: &pkg.AddClientRequest{
				ClientName:    "Anastasiya",
				ClientSurname: "Vasilieva",
				Birthday:      yesterday,
				Gender:        domain.Female,
				City:          "Saint-Petersburg",
				Street:        "Sennaya",
			},
			wantErr: true,
		},
		{
			name: "missing city",
			req: &pkg.AddClientRequest{
				ClientName:    "Anastasiya",
				ClientSurname: "Vasilieva",
				Birthday:      yesterday,
				Gender:        domain.Female,
				Country:       "Russia",
				Street:        "Sennaya",
			},
			wantErr: true,
		},
		{
			name: "missing street",
			req: &pkg.AddClientRequest{
				ClientName:    "Anastasiya",
				ClientSurname: "Vasilieva",
				Birthday:      yesterday,
				Gender:        domain.Female,
				Country:       "Russia",
				City:          "Saint-Petersburg",
			},
			wantErr: true,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			err := validateClientRequest(*tt.req)
			if (err != nil) != tt.wantErr {
				t.Errorf("validateClientRequest failed at %s", tt.name)
			}
		})
	}
}

func TestValidateProductRequest(t *testing.T) {
	Supplier := uuid.New()
	tests := []struct {
		name    string
		req     pkg.AddProductRequest
		wantErr bool
	}{
		{
			name: "valid request",
			req: pkg.AddProductRequest{
				Name:           "Laptop Air",
				Category:       "Laptops",
				Price:          120000,
				AvailableStock: 10,
				SupplierID:     Supplier,
			},
		},
		{
			name: "missing name",
			req: pkg.AddProductRequest{
				Category:       "Laptops",
				Price:          120000,
				AvailableStock: 10,
				SupplierID:     Supplier,
			},
			wantErr: true,
		},
		{
			name: "missing category",
			req: pkg.AddProductRequest{
				Name:           "Laptop Air",
				Price:          120000,
				AvailableStock: 10,
				SupplierID:     Supplier,
			},
			wantErr: true,
		},
		{
			name: "zero price",
			req: pkg.AddProductRequest{
				Name:           "Laptop Air",
				Category:       "Laptops",
				Price:          0,
				AvailableStock: 10,
				SupplierID:     Supplier,
			},
			wantErr: true,
		},
		{
			name: "negative price",
			req: pkg.AddProductRequest{
				Name:           "Laptop Air",
				Category:       "Laptops",
				Price:          -100,
				AvailableStock: 10,
				SupplierID:     Supplier,
			},
			wantErr: true,
		},
		{
			name: "negative stock",
			req: pkg.AddProductRequest{
				Name:           "Laptop Air",
				Category:       "Laptops",
				Price:          120000,
				AvailableStock: -1,
				SupplierID:     Supplier,
			},
			wantErr: true,
		},
		{
			name: "nil supplier",
			req: pkg.AddProductRequest{
				Name:           "Laptop Air",
				Category:       "Laptops",
				Price:          120000,
				AvailableStock: 10,
			},
			wantErr: true,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			err := validateProductRequest(tt.req)
			if (err != nil) != tt.wantErr {
				t.Errorf("validateProductRequest failed at %s", tt.name)
			}
		})
	}
}

func TestValidateSupplierRequest(t *testing.T) {
	tests := []struct {
		name    string
		req     pkg.AddSupplierRequest
		wantErr bool
	}{
		{
			name: "valid request",
			req: pkg.AddSupplierRequest{
				Name:        "Tech Wholesale",
				PhoneNumber: "+70001112233",
				Country:     "Russia",
				City:        "Moscow",
				Street:      "Tverskaya",
			},
		},
		{
			name: "missing name",
			req: pkg.AddSupplierRequest{
				PhoneNumber: "+70001112233",
				Country:     "Russia",
				City:        "Moscow",
				Street:      "Tverskaya",
			},
			wantErr: true,
		},
		{
			name: "missing phone",
			req: pkg.AddSupplierRequest{
				Name:    "Tech Wholesale",
				Country: "Russia",
				City:    "Moscow",
				Street:  "Tverskaya",
			},
			wantErr: true,
		},
		{
			name: "missing country",
			req: pkg.AddSupplierRequest{
				Name:        "Tech Wholesale",
				PhoneNumber: "+70001112233",
				City:        "Moscow",
				Street:      "Tverskaya",
			},
			wantErr: true,
		},
		{
			name: "missing city",
			req: pkg.AddSupplierRequest{
				Name:        "Tech Wholesale",
				PhoneNumber: "+70001112233",
				Country:     "Russia",
				Street:      "Tverskaya",
			},
			wantErr: true,
		},
		{
			name: "missing street",
			req: pkg.AddSupplierRequest{
				Name:        "Tech Wholesale",
				PhoneNumber: "+70001112233",
				Country:     "Russia",
				City:        "Moscow",
			},
			wantErr: true,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			err := validateSupplierRequest(tt.req)
			if (err != nil) != tt.wantErr {
				t.Errorf("validateSupplierRequest failed at %s", tt.name)
			}
		})
	}
}

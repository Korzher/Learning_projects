package domain

import (
	"context"

	"github.com/google/uuid"
)

type Supplier struct {
	ID          uuid.UUID
	Name        string
	AddressID   uuid.UUID
	PhoneNumber string
}

type SupplierRepository interface {
	AddSupplier(ctx context.Context, supplier *Supplier) error
	AddressChange(ctx context.Context, ID uuid.UUID, NewAddress uuid.UUID) error
	DeleteSupplier(ctx context.Context, ID uuid.UUID) error
	GetAllSuppliers(ctx context.Context) ([]Supplier, error)
	GetSupplier(ctx context.Context, ID uuid.UUID) (Supplier, error)
}

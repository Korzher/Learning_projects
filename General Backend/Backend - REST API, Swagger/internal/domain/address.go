package domain

import (
	"context"

	"github.com/google/uuid"
)

type Address struct {
	ID      uuid.UUID
	Country string
	City    string
	Street  string
}

type AddressRepository interface {
	GetAddress(ctx context.Context, country, city, street string) (uuid.UUID, error)
}

package domain

import (
	"context"
	"time"

	"github.com/google/uuid"
)

type Gender string

const (
	Male   Gender = "M"
	Female Gender = "F"
)

type Client struct {
	ID               uuid.UUID
	ClientName       string
	ClientSurname    string
	Birthday         time.Time
	Gender           Gender
	RegistrationDate time.Time
	AddressID        uuid.UUID
}

type ClientRepository interface {
	AddClient(ctx context.Context, client *Client) error
	DeleteClient(ctx context.Context, ID uuid.UUID) error
	GetClient(ctx context.Context, name, surname string) ([]Client, error)
	GetAllClients(ctx context.Context, limit, offset int) ([]Client, int, error)
	AddressChange(ctx context.Context, ID uuid.UUID, NewAddress uuid.UUID) error
}

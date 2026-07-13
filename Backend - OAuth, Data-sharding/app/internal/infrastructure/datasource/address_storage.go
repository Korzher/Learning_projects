package datasource

import (
	"context"

	"github.com/google/uuid"
)

type AddressStorage struct {
	db DBExecutor
}

func NewAddressStorage(db DBExecutor) *AddressStorage {
	return &AddressStorage{
		db: db,
	}
}

func (a *AddressStorage) GetAddress(ctx context.Context, country, city, street string) (uuid.UUID, error) {
	var id uuid.UUID

	query := `
		WITH new_address AS (
			INSERT INTO address_table (country, city, street)
			VALUES ($1, $2, $3)
			ON CONFLICT (country, city, street) DO NOTHING
			RETURNING id
		)
		SELECT id FROM new_address
		UNION ALL
		SELECT id FROM address_table
		WHERE country = $1 AND city = $2 AND street = $3
		LIMIT 1
	`

	err := a.db.QueryRow(ctx, query, country, city, street).Scan(&id)

	if err != nil {
		return uuid.Nil, err
	}
	return id, nil
}

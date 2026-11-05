package datasource

import (
	"apifromspec/internal/domain"
	"apifromspec/internal/pkg"
	"context"
	"errors"
	"fmt"

	"github.com/google/uuid"
	"github.com/jackc/pgx/v5"
	"github.com/jackc/pgx/v5/pgconn"
)

type SupplierStorage struct {
	db DBExecutor
}

func NewSupplierStorage(db DBExecutor) *SupplierStorage {
	return &SupplierStorage{
		db: db,
	}
}

func (s *SupplierStorage) AddSupplier(ctx context.Context, supplier *domain.Supplier) error {
	_, err := s.db.Exec(ctx, `
        INSERT INTO supplier_table (id, name, address_id, phone_number)
        VALUES ($1, $2, $3, $4)
    `, supplier.ID, supplier.Name, supplier.AddressID, supplier.PhoneNumber)
	if err != nil {
		var pgErr *pgconn.PgError
		if errors.As(err, &pgErr) && pgErr.Code == "23505" {
			return pkg.ErrSupplierAlreadyExists
		}
		return err
	}
	return nil
}

func (s *SupplierStorage) AddressChange(ctx context.Context, ID uuid.UUID, NewAddressID uuid.UUID) error {
	tx, err := s.db.Begin(ctx)
	if err != nil {
		return err
	}
	defer tx.Rollback(ctx)
	var currentAddressID uuid.UUID
	lockQuery := `SELECT address_id FROM supplier_table WHERE id = $1 FOR UPDATE`
	err = tx.QueryRow(ctx, lockQuery, ID).Scan(&currentAddressID)
	if err != nil {
		if errors.Is(err, pgx.ErrNoRows) {
			return pkg.ErrIDNotFound
		}
		return err
	}
	updateQuery := `UPDATE supplier_table SET address_id = $1 WHERE id = $2`
	_, err = tx.Exec(ctx, updateQuery, NewAddressID, ID)
	if err != nil {
		return err
	}
	return tx.Commit(ctx)
}

func (s *SupplierStorage) DeleteSupplier(ctx context.Context, ID uuid.UUID) error {
	tag, err := s.db.Exec(ctx, `
	DELETE FROM supplier_table 
	WHERE id = $1`,
		ID)
	if err != nil {
		return err
	}
	if tag.RowsAffected() == 0 {
		return pkg.ErrIDNotFound
	}
	return nil
}

func (s *SupplierStorage) GetSupplier(ctx context.Context, ID uuid.UUID) (domain.Supplier, error) {
	var sup domain.Supplier
	err := s.db.QueryRow(ctx, `
        SELECT id, name, address_id, phone_number
        FROM supplier_table
        WHERE id = $1
    `, ID).Scan(&sup.ID, &sup.Name, &sup.AddressID, &sup.PhoneNumber)
	if err != nil {
		if errors.Is(err, pgx.ErrNoRows) {
			return domain.Supplier{}, pkg.ErrIDNotFound
		}
		return domain.Supplier{}, pkg.ErrFailToFetch
	}
	return sup, nil
}

func (s *SupplierStorage) GetAllSuppliers(ctx context.Context) ([]domain.Supplier, error) {
	rows, err := s.db.Query(ctx, `
        SELECT id, name, address_id, phone_number
        FROM supplier_table
        ORDER BY name
    `)
	if err != nil {
		return nil, fmt.Errorf("failed to query suppliers: %w", err)
	}
	defer rows.Close()

	var suppliers []domain.Supplier
	for rows.Next() {
		var sup domain.Supplier
		err := rows.Scan(&sup.ID, &sup.Name, &sup.AddressID, &sup.PhoneNumber)
		if err != nil {
			return nil, fmt.Errorf("failed to scan supplier row: %w", err)
		}
		suppliers = append(suppliers, sup)
	}
	if err = rows.Err(); err != nil {
		return nil, fmt.Errorf("rows iteration error: %w", err)
	}
	return suppliers, nil
}

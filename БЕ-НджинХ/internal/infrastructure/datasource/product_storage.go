package datasource

import (
	"apifromspec/internal/domain"
	"apifromspec/internal/pkg"
	"context"
	"errors"
	"fmt"

	"github.com/google/uuid"
	"github.com/jackc/pgx/v5"
)

type ProductStorage struct {
	db DBExecutor
}

func NewProductStorage(db DBExecutor) *ProductStorage {
	return &ProductStorage{
		db: db,
	}
}

// Картинка добавляется на этапе разборки http или где-то там
func (p *ProductStorage) AddProduct(ctx context.Context, product *domain.Product) error {
	_, err := p.db.Exec(ctx, `
	INSERT INTO product_table
	(id, name, category, price, available_stock, supplier_id, image_id, last_update_date)
	VALUES ($1, $2, $3, $4, $5, $6, $7, $8)
	`,
		product.ID,
		product.Name,
		product.Category,
		product.Price,
		product.AvailableStock,
		product.SupplierID,
		product.ImageID,
		product.LastUpdateDate,
	)
	return err
}

func (p *ProductStorage) SubtractProduct(ctx context.Context, id uuid.UUID, amount int) error {
	tag, err := p.db.Exec(ctx, `
	UPDATE product_table
	SET available_stock = available_stock - $1,
		last_update_date = CURRENT_TIMESTAMP
	WHERE id = $2 AND available_stock >= $1
	`, amount, id)
	if err != nil {
		return fmt.Errorf("failed to update stock: %w", err)
	}

	if tag.RowsAffected() == 0 {
		return pkg.ErrInsufficientStock
	}
	return nil
}

func (p *ProductStorage) GetProduct(ctx context.Context, id uuid.UUID) (domain.Product, error) {
	var product domain.Product
	var imageID *uuid.UUID

	err := p.db.QueryRow(ctx, `
	SELECT id, name, category, price, available_stock, last_update_date, supplier_id, image_id
	FROM product_table
	WHERE id = $1
	`, id).Scan(
		&product.ID,
		&product.Name,
		&product.Category,
		&product.Price,
		&product.AvailableStock,
		&product.LastUpdateDate,
		&product.SupplierID,
		&imageID,
	)

	if err != nil {
		if errors.Is(err, pgx.ErrNoRows) {
			return domain.Product{}, pkg.ErrIDNotFound
		}
		return domain.Product{}, pkg.ErrFailToFetch
	}

	if imageID != nil {
		product.ImageID = *imageID
	}

	return product, nil
}

func (p *ProductStorage) GetAllProducts(ctx context.Context) ([]domain.Product, error) {
	rows, err := p.db.Query(ctx, `
	SELECT id, name, category, price, available_stock, last_update_date, supplier_id, image_id
	FROM product_table
	ORDER BY last_update_date DESC`)
	if err != nil {
		return nil, fmt.Errorf("failed to query product: %w", err)
	}
	defer rows.Close()

	var products []domain.Product
	for rows.Next() {
		var product domain.Product
		var imageID *uuid.UUID
		err := rows.Scan(
			&product.ID,
			&product.Name,
			&product.Category,
			&product.Price,
			&product.AvailableStock,
			&product.LastUpdateDate,
			&product.SupplierID,
			&imageID,
		)
		if err != nil {
			return nil, fmt.Errorf("failed to scan product row: %w", err)
		}

		if imageID != nil {
			product.ImageID = *imageID
		}

		products = append(products, product)
	}

	if err = rows.Err(); err != nil {
		return nil, fmt.Errorf("rows iteration error: %w", err)
	}

	return products, nil
}

func (p *ProductStorage) DeleteProduct(ctx context.Context, id uuid.UUID) error {
	tag, err := p.db.Exec(ctx, `
	DELETE FROM product_table
	WHERE id = $1
	`, id)
	if err != nil {
		return fmt.Errorf("failed to delete product: %w", err)
	}

	if tag.RowsAffected() == 0 {
		return pkg.ErrIDNotFound
	}
	return nil
}

func (p *ProductStorage) SetProductImage(ctx context.Context, productID, imageID uuid.UUID) error {
	res, err := p.db.Exec(ctx, `
	UPDATE product_table
	Set image_id = $2
	WHERE id = $1
	`, productID, imageID)
	if err != nil {
		return err
	}
	if res.RowsAffected() == 0 {
		return fmt.Errorf("product %v not found", productID)
	}
	return nil
}

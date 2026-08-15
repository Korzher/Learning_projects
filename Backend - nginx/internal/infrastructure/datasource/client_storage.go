package datasource

import (
	"apifromspec/internal/domain"
	"apifromspec/internal/pkg"
	"context"
	"errors"

	"github.com/google/uuid"
	"github.com/jackc/pgx/v5"
	"github.com/jackc/pgx/v5/pgconn"
)

type ClientStorage struct {
	db DBExecutor
}

func NewClientStorage(db DBExecutor) *ClientStorage {
	return &ClientStorage{
		db: db,
	}
}

func (c *ClientStorage) AddClient(ctx context.Context, client *domain.Client) error {
	_, err := c.db.Exec(ctx, `
	INSERT INTO client_table
	(id, client_name, client_surname, birthday, gender, address_id)
	VALUES ($1, $2, $3, $4, $5, $6)
	`,
		client.ID,
		client.ClientName,
		client.ClientSurname,
		client.Birthday,
		client.Gender,
		client.AddressID,
	)
	if err != nil {
		var pgErr *pgconn.PgError
		if errors.As(err, &pgErr) && pgErr.Code == "23505" {
			return pkg.ErrClientAlreadyExists
		}
		return err
	}
	return nil
}

func (c *ClientStorage) DeleteClient(ctx context.Context, ID uuid.UUID) error {
	res, err := c.db.Exec(ctx, `
	DELETE FROM client_table
	WHERE id = $1`,
		ID)
	if err != nil {
		return err
	}
	if res.RowsAffected() == 0 {
		return pkg.ErrIDNotFound
	}
	return nil
}

func (c *ClientStorage) GetClient(ctx context.Context, name, surname string) ([]domain.Client, error) {
	rows, err := c.db.Query(ctx, `
	SELECT id, client_name, client_surname, birthday, gender, registration_date, address_id
	FROM client_table
	WHERE client_name = $1 AND client_surname = $2
	ORDER BY registration_date ASC`, name, surname)
	if err != nil {
		return nil, err
	}
	defer rows.Close()
	var clients []domain.Client
	for rows.Next() {
		var client domain.Client
		err := rows.Scan(
			&client.ID,
			&client.ClientName,
			&client.ClientSurname,
			&client.Birthday,
			&client.Gender,
			&client.RegistrationDate,
			&client.AddressID,
		)
		if err != nil {
			return nil, err
		}
		clients = append(clients, client)
	}
	if err := rows.Err(); err != nil {
		return nil, err
	}
	return clients, nil
}

func (c *ClientStorage) GetAllClients(ctx context.Context, limit, offset int) ([]domain.Client, int, error) {
	query := `
        SELECT 
            id, client_name, client_surname, birthday, gender, registration_date, address_id,
            COUNT(*) OVER() as total_count
        FROM client_table
        ORDER BY registration_date
        LIMIT CASE WHEN $1 > 0 THEN $1 ELSE NULL END
        OFFSET CASE WHEN $2 > 0 THEN $2 ELSE 0 END
    `

	rows, err := c.db.Query(ctx, query, limit, offset)
	if err != nil {
		return nil, 0, err
	}
	defer rows.Close()

	var clients []domain.Client
	var total int

	for rows.Next() {
		var client domain.Client
		err := rows.Scan(
			&client.ID,
			&client.ClientName,
			&client.ClientSurname,
			&client.Birthday,
			&client.Gender,
			&client.RegistrationDate,
			&client.AddressID,
			&total,
		)
		if err != nil {
			return nil, 0, err
		}
		clients = append(clients, client)
	}
	if err := rows.Err(); err != nil {
		return nil, 0, err
	}
	return clients, total, nil
}

func (c *ClientStorage) AddressChange(ctx context.Context, ID uuid.UUID, NewAddressID uuid.UUID) error {
	tx, err := c.db.Begin(ctx)
	if err != nil {
		return err
	}
	defer tx.Rollback(ctx)
	var currentAddressID uuid.UUID
	lockQuery := `SELECT address_id FROM client_table WHERE id = $1 FOR UPDATE`
	err = tx.QueryRow(ctx, lockQuery, ID).Scan(&currentAddressID)
	if err != nil {
		if errors.Is(err, pgx.ErrNoRows) {
			return pkg.ErrIDNotFound
		}
		return err
	}
	updateQuery := `UPDATE client_table SET address_id = $1 WHERE id = $2`
	_, err = tx.Exec(ctx, updateQuery, NewAddressID, ID)
	if err != nil {
		return err
	}

	return tx.Commit(ctx)
}

package datasource

import (
	"context"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/pkg/contracts"
	"time"

	"github.com/google/uuid"
	"github.com/jackc/pgx/v5"
	"github.com/jackc/pgx/v5/pgxpool"
)

type UserStorage struct {
	pool *pgxpool.Pool
}

func NewUserStorage(pool *pgxpool.Pool) domain.UserRepository {
	return &UserStorage{pool: pool}
}

func (s *UserStorage) Save(ctx context.Context, user *domain.User) error {
	query := `
	INSERT INTO users (id, username, password)
	VALUES ($1, $2, $3)
	`

	_, err := s.pool.Exec(ctx, query,
		user.ID,
		user.Username,
		user.Password)

	if err != nil {
		if err.Error() == "ERROR: duplicate key value violates unique constraint \"users_username_key\"" {
			return contracts.ErrUserExist
		}
		return contracts.ErrFailedToSave
	}

	return nil
}

func (s *UserStorage) FindByUsername(ctx context.Context, username string) (*domain.User, error) {
	query := `
	SELECT id, username, password
	FROM users
	WHERE username = $1`

	var id uuid.UUID
	var dbUsername, password string

	err := s.pool.QueryRow(ctx, query, username).Scan(&id, &dbUsername, &password)
	if err == pgx.ErrNoRows {
		return nil, contracts.ErrUserNotFound
	}

	if err != nil {
		return nil, err
	}

	return &domain.User{
		ID:       id,
		Username: dbUsername,
		Password: password,
	}, nil
}

func (s *UserStorage) FindByID(ctx context.Context, ID uuid.UUID) (*domain.User, error) {
	query := `
	SELECT id, username, password
	FROM users
	WHERE id = $1`

	var id uuid.UUID
	var dbUsername, password string
	var createdAt time.Time

	err := s.pool.QueryRow(ctx, query, ID).Scan(&id, &dbUsername, &password)
	if err == pgx.ErrNoRows {
		return nil, contracts.ErrUserNotFound
	}
	if err != nil {
		return nil, contracts.ErrFailedToQueryID
	}
	return &domain.User{
		ID:        id,
		Username:  dbUsername,
		Password:  password,
		CreatedAt: createdAt,
	}, nil
}

func (s *UserStorage) FindAll(ctx context.Context) ([]*domain.User, error) {
	query := `SELECT id, username FROM users ORDER BY username`

	rows, err := s.pool.Query(ctx, query)
	if err != nil {
		return nil, contracts.ErrFailedToQueryUs
	}
	defer rows.Close()

	var users []*domain.User
	for rows.Next() {
		var id uuid.UUID
		var username string

		err := rows.Scan(&id, &username)
		if err != nil {
			return nil, contracts.ErrFailedToScan
		}

		users = append(users, &domain.User{
			ID:       id,
			Username: username,
		})
	}

	return users, nil
}

package datasource

import (
	"context"
	"errors"
	"grpc_auth/internal/domain"

	"github.com/jackc/pgx/v5"
	"github.com/jackc/pgx/v5/pgconn"
	"github.com/jackc/pgx/v5/pgxpool"
)

type UserStorage struct {
	pool *pgxpool.Pool
}

func NewUserStorage(pool *pgxpool.Pool) domain.UserRepository {
	return &UserStorage{pool: pool}
}


func (u *UserStorage) CreateUser(ctx context.Context, user *domain.User) error {
	query := `
	INSERT INTO user_table (email, first_name, last_name, phone, user_password)
	VALUES ($1, $2, $3, $4, $5)
	RETURNING id
	`

	err := u.pool.QueryRow(ctx, query,
		user.Email,
		user.FirstName,
		user.LastName,
		user.Phone,
		user.Password).Scan(&user.ID)
		
	if err != nil {
		var pgErr *pgconn.PgError
		if errors.As(err, &pgErr) && pgErr.Code == "23505" {
			return errors.New("email already exists")
		}
		return err
	}
	return nil
}

func (u *UserStorage) AuthenticateUser(ctx context.Context, email string) (*domain.User, error) {
	query := `
    SELECT id, email, first_name, last_name, phone, user_password
    FROM user_table
    WHERE email = $1
    `
	var user domain.User
    err := u.pool.QueryRow(ctx, query, email).Scan(
        &user.ID,
        &user.Email,
        &user.FirstName,
        &user.LastName,
        &user.Phone,
        &user.Password,
    )

	if err != nil {
        if errors.Is(err, pgx.ErrNoRows) {
            return nil, errors.New("Email not found")
        }
        return nil, errors.New("failed to get user")
    }
    
    return &user, nil
}

func (u *UserStorage) ChangePassword(ctx context.Context, email, password string) error {
	query := `
	UPDATE user_table
	SET user_password = $1
	WHERE email = $2
	`

	cmdTag, err := u.pool.Exec(ctx, query, password, email)
    if err != nil {
        return errors.New("failed to update password")
    }
    
    if cmdTag.RowsAffected() == 0 {
        return errors.New("user with this email does not exist")
    }
    
    return nil
}

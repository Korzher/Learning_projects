package di

import (
	"grpc_auth/internal/application/service"
	"grpc_auth/internal/domain"
	"grpc_auth/internal/infrastructure/datasource"
	"grpc_auth/internal/web/handler"

	"github.com/jackc/pgx/v5/pgxpool"
	"go.uber.org/fx"
)

var Module = fx.Module("auth",
	fx.Provide(
		datasource.NewPostgresConfig,
		datasource.NewPostgresPool,
		func (pool *pgxpool.Pool) domain.UserRepository{
			return datasource.NewUserStorage(pool)
		}, service.NewUserService,
		service.NewJwtProvider,
		handler.NewAuthServer,
	))
package di

import (
	"github.com/jackc/pgx/v5/pgxpool"
	"go.uber.org/fx"

	"tic-tac-toe/internal/application/service"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/internal/infrastructure/datasource"
	"tic-tac-toe/internal/infrastructure/web/handler"
	"tic-tac-toe/internal/infrastructure/web/middleware"
)

var Module = fx.Module("tic-tac-toe",
	fx.Provide(
		datasource.NewPostgresConfig,
		datasource.NewPostgresPool,
		func(pool *pgxpool.Pool) domain.GameRepository {
			return datasource.NewGameStorage(pool)
		}, service.NewGameService,
		func(pool *pgxpool.Pool) domain.UserRepository {
			return datasource.NewUserStorage(pool)
		}, service.NewUserService,
		service.NewJwtProvider,
		middleware.NewUserAuthenticator,
		handler.NewGameHandler,
		handler.NewAuthHandler,
		handler.NewUserHandler,
	),
	fx.Invoke(datasource.CreateTable),
)

package di

import (
	"go.uber.org/fx"

	"tic-tac-toe/internal/application/service"
	"tic-tac-toe/internal/domain"
	"tic-tac-toe/internal/infrastructure/datasource"
	"tic-tac-toe/internal/infrastructure/web/handler"
)

var Module = fx.Module("tic-tac-toe",
	fx.Provide(
		datasource.NewGameStorage,
		func(storage *datasource.GameStorage) domain.GameRepository {
			return storage
		}, service.NewGameService,
		handler.NewGameHandler,
	))
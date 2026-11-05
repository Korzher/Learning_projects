package di

import (
	"apifromspec/internal/application"
	"apifromspec/internal/domain"
	"apifromspec/internal/infrastructure/datasource"
	"apifromspec/internal/infrastructure/web/auth"
	"apifromspec/internal/infrastructure/web/handler"
	"apifromspec/internal/infrastructure/web/mapper"
	"context"

	"github.com/jackc/pgx/v5/pgxpool"
	"go.uber.org/fx"
)

var Module = fx.Module("techshop",
	fx.Provide(
		datasource.NewPostgreConfig,
		datasource.NewPostgresPool,
		func(pool *pgxpool.Pool) datasource.DBExecutor { return pool },

		fx.Annotate(datasource.NewClientStorage, fx.As(new(domain.ClientRepository))),
		fx.Annotate(datasource.NewImageStorage, fx.As(new(domain.ImageRepository))),
		fx.Annotate(datasource.NewProductStorage, fx.As(new(domain.ProductRepository))),
		fx.Annotate(datasource.NewSupplierStorage, fx.As(new(domain.SupplierRepository))),
		fx.Annotate(datasource.NewAddressStorage, fx.As(new(domain.AddressRepository))),
		application.NewProductService,
		mapper.NewAddressHandler,
		handler.NewClientHandler,
		handler.NewImageHandler,
		handler.NewProductHandler,
		handler.NewSupplierHandler,
		auth.NewClient,
		handler.NewAuthHandler,
	),
	fx.Invoke(func(lc fx.Lifecycle, client *auth.Client) {
		lc.Append(fx.Hook{
			OnStop: func(ctx context.Context) error {
				return client.Close()
			},
		})
	}),
)

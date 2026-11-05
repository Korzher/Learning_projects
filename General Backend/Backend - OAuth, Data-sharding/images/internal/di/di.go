package di

import (
	"context"
	"images/internal/infrastructure/datasource"
	"images/internal/infrastructure/web/handler"

	"github.com/jackc/pgx/v5/pgxpool"
	"go.uber.org/fx"
)

var Module = fx.Module("images",
	fx.Provide(
		datasource.NewShardedPools,
		datasource.NewImageStorage,
		handler.NewImagesServer,
	),
	fx.Invoke(func(lc fx.Lifecycle, pools [4]*pgxpool.Pool) {
		lc.Append(fx.Hook{
			OnStop: func(ctx context.Context) error {
				for _, pool := range pools {
					pool.Close()
				}
				return nil
			},
		})
	}),
)

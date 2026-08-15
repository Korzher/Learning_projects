package main

import (
	_ "apifromspec/docs"
	"apifromspec/internal/di"
	"apifromspec/internal/infrastructure/middleware"
	"apifromspec/internal/infrastructure/web/auth"
	"apifromspec/internal/infrastructure/web/handler"
	"context"
	"fmt"
	"net/http"
	"time"

	httpSwagger "github.com/swaggo/http-swagger"

	"go.uber.org/fx"
)

//@title            School 21 ApiFromSpec docs
//@version          1.0
//@description      Реализация RestAPI на Go с использование Swagger для документации
//@termsOfService   http://swagger.io/terms

//@contact.name     desmonsu

// @host      localhost:8080
// @BasePath  /api/v1

func registerHTTPHandler(
	lc fx.Lifecycle,
	clientHandler *handler.ClientHandler,
	imagesHandler *handler.ImageHandler,
	productHandler *handler.ProductHandler,
	supplierHandler *handler.SupplierHandler,
	authHandler *handler.AuthHandler,
	client *auth.Client,
) {
	mux := http.NewServeMux()
	mux.Handle("/swagger/", httpSwagger.WrapHandler)
	authHandler.RegisterRoutes(mux)
	authorized := http.NewServeMux()
	clientHandler.RegisterRoutes(authorized)
	imagesHandler.RegisterRoutes(authorized)
	productHandler.RegisterRoutes(authorized)
	supplierHandler.RegisterRoutes(authorized)

	mux.Handle("/", middleware.AuthMiddleware(client)(authorized))

	server := &http.Server{
		Addr:    ":8080",
		Handler: mux,
	}

	lc.Append(fx.Hook{
		OnStart: func(ctx context.Context) error {
			fmt.Println("Starting techshop server on :8080")
			fmt.Println("Address http://localhost:8080")

			go func() {
				if err := server.ListenAndServe(); err != nil && err != http.ErrServerClosed {
					fmt.Printf("Server error: %v\n", err)
				}
			}()

			return nil
		},
		OnStop: func(ctx context.Context) error {
			fmt.Println("Stopping server...")
			shutdownCtx, cancel := context.WithTimeout(ctx, 5*time.Second)
			defer cancel()
			return server.Shutdown(shutdownCtx)
		},
	})
}

func main() {
	app := fx.New(
		di.Module,
		fx.Invoke(registerHTTPHandler),
	)
	app.Run()
}

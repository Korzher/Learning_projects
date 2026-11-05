package main

import (
	_ "apifromspec/docs"
	"apifromspec/internal/di"
	"apifromspec/internal/infrastructure/web/handler"
	"context"
	"fmt"
	"net/http"
	"os"
	"os/signal"
	"syscall"
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
) {
	mux := http.NewServeMux()
	mux.Handle("/swagger/", httpSwagger.WrapHandler)
	clientHandler.RegisterRoutes(mux)
	imagesHandler.RegisterRoutes(mux)
	productHandler.RegisterRoutes(mux)
	supplierHandler.RegisterRoutes(mux)

	server := &http.Server{
		Addr:              ":8080",
		Handler:           mux,
		ReadTimeout:       5 * time.Second,
		WriteTimeout:      10 * time.Second,
		IdleTimeout:       120 * time.Second,
		ReadHeaderTimeout: 2 * time.Second,
	}

	lc.Append(fx.Hook{
		OnStart: func(ctx context.Context) error {
			fmt.Println("Starting techshop server on :8080")
			fmt.Println("Address http://localhost:8080")

			go func() {
				sigChan := make(chan os.Signal, 1)
				signal.Notify(sigChan, syscall.SIGINT, syscall.SIGTERM)
				<-sigChan

				fmt.Println("\nReceived shutdown signal, shutting down gracefully...")

				shutdownCtx, cancel := context.WithTimeout(context.Background(), 30*time.Second)
				defer cancel()

				if err := server.Shutdown(shutdownCtx); err != nil {
					fmt.Printf("Server forced to shutdown: %v\n", err)
				}
				fmt.Println("Server exited gracefully")
			}()
			if err := server.ListenAndServe(); err != nil && err != http.ErrServerClosed {
				return fmt.Errorf("server startup failed: %w", err)
			}
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

package main

import (
	"context"
	"fmt"
	"net/http"
	"tic-tac-toe/internal/di"
	"tic-tac-toe/internal/infrastructure/web/handler"

	"go.uber.org/fx"
)

func registerHTTPHandler(
	lc fx.Lifecycle,
	handler *handler.GameHandler,
) {
	mux := http.NewServeMux()
	handler.RegisterRoutes(mux)

	server := &http.Server{
		Addr: ":8080",
		Handler: mux,
	}

	lc.Append(fx.Hook{
		OnStart: func(ctx context.Context) error{
			fmt.Println("Starting tic-tac-toe server on :8080")
			go func() {
				if err := server.ListenAndServe(); err != nil && err != http.ErrServerClosed {
					fmt.Printf("Server error: %v\n", err)
				}
			}()
			return nil
		},
		OnStop: func(ctx context.Context) error {
			fmt.Println("Shutting down server...")
			return server.Shutdown(ctx)
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
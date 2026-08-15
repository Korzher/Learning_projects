package main

import (
	"context"
	"fmt"
	"net/http"
	"tic-tac-toe/internal/di"
	"tic-tac-toe/internal/infrastructure/web/handler"
	"tic-tac-toe/internal/infrastructure/web/middleware"

	"go.uber.org/fx"
)

func registerHTTPHandler(
	lc fx.Lifecycle,
	gameHandler *handler.GameHandler,
	authHandler *handler.AuthHandler,
	userHandler *handler.UserHandler,
	authMiddleware *middleware.UserAuthenticator,
) {
	mux := http.NewServeMux()
	gameHandler.RegisterRoutes(mux)
	authHandler.RegisterRoutes(mux)
	userHandler.RegisterRoutes(mux)
	wrappedMux := authMiddleware.Authenticate(mux)

	server := &http.Server{
		Addr:    ":8080",
		Handler: wrappedMux,
	}

	lc.Append(fx.Hook{
		OnStart: func(ctx context.Context) error {
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

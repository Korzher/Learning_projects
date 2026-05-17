package main

import (
	"context"
	auth "gen"
	"grpc_auth/internal/di"
	"grpc_auth/internal/web/handler"
	"log"
	"net"

	"go.uber.org/fx"
	"google.golang.org/grpc"
)

func main() {
	fx.New(
		di.Module,
		fx.Invoke(RunServer),
	).Run()
}

func RunServer(lc fx.Lifecycle, srv *handler.AuthServer) {
	gSrv := grpc.NewServer()
	auth.RegisterAuthServiceServer(gSrv, srv)
	lc.Append(fx.Hook{
		OnStart: func(ctx context.Context) error {
			lis, err := net.Listen("tcp", ":50051")
			if err != nil {
				return err
			}
			log.Printf("Starting gRPC server on :50051")
			go gSrv.Serve(lis)
			return nil
		},
		OnStop: func(ctx context.Context) error {
			gSrv.GracefulStop()
			return nil
		},
	})
}
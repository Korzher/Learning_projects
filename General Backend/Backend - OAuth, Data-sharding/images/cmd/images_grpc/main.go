package main

import (
	"context"
	"gen"
	"images/internal/di"
	"images/internal/infrastructure/web/handler"
	"log"
	"net"

	"go.uber.org/fx"
	"google.golang.org/grpc"
)

func RunServ(lc fx.Lifecycle, srv *handler.ImageServer) {
	gSrv := grpc.NewServer()
	gen.RegisterImageServiceServer(gSrv, srv)
	lc.Append(fx.Hook{
		OnStart: func(ctx context.Context) error {
			lis, err := net.Listen("tcp", ":50052")
			if err != nil {
				return err
			}
			log.Printf("Starting images of :50052")
			go gSrv.Serve(lis)
			return nil
		},
		OnStop: func(ctx context.Context) error {
			gSrv.GracefulStop()
			return nil
		},
	})
}

func main() {
	fx.New(
		di.Module,
		fx.Invoke(RunServ),
	).Run()
}

package auth

import (
	"apifromspec/internal/pkg"
	"context"
	pb "gen"
	"os"
	"time"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"google.golang.org/grpc/metadata"
)

type Client struct {
	client pb.AuthServiceClient
	conn   *grpc.ClientConn
}

func NewClient() (*Client, error) {
	addr := os.Getenv("addr")
	if addr == "" {
		addr = "auth:50051"
	}
	conn, err := grpc.NewClient(addr,
		grpc.WithTransportCredentials(insecure.NewCredentials()),
		grpc.WithConnectParams(grpc.ConnectParams{
			MinConnectTimeout: 5 * time.Second,
		}),
	)
	if err != nil {
		return nil, pkg.ErrFailedGRPC
	}

	client := pb.NewAuthServiceClient(conn)
	return &Client{
		client: client,
		conn:   conn,
	}, nil
}

func (c *Client) Close() error {
	return c.conn.Close()
}

func (c *Client) CreateUser(ctx context.Context, email, firstName, lastName, phone, password string) (string, error) {
	resp, err := c.client.CreateUser(ctx, &pb.CreateUserRequest{
		Email:     email,
		FirstName: firstName,
		LastName:  lastName,
		Phone:     phone,
		Password:  password,
	})
	if err != nil {
		return "", err
	}
	return resp.Token, nil
}

func (c *Client) Authenticate(ctx context.Context, email, password string) (string, error) {
	resp, err := c.client.Authenticate(ctx, &pb.AuthenticateRequest{
		Email:    email,
		Password: password,
	})
	if err != nil {
		return "", err
	}
	return resp.Token, nil
}

func (c *Client) VerifyToken(ctx context.Context, token string) (bool, error) {
	resp, err := c.client.VerifyToken(ctx, &pb.VerifyTokenRequest{
		Token: token,
	})
	if err != nil {
		return false, err
	}
	return resp.Valid, nil
}

func (c *Client) ChangePassword(ctx context.Context, token, oldPassword, newPassword string) error {
	md := metadata.Pairs("authorization", "Bearer " + token)
	ctx = metadata.NewOutgoingContext(ctx, md)
	_, err := c.client.ChangePassword(ctx, &pb.ChangePasswordRequest{
		OldPassword: oldPassword,
		NewPassword: newPassword,
	})
	return err
}

func (c *Client) ResetPassword(ctx context.Context, email string) error {
	_, err := c.client.ResetPassword(ctx, &pb.ResetPasswordRequest{
		Email: email,
	})
	return err
}

package images

import (
	"context"
	"gen"
	"os"
	"time"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

type Client struct {
	client gen.ImageServiceClient
	conn   *grpc.ClientConn
}

func NewClient() (*Client, error) {
	addr := os.Getenv("images_addr")
	if addr == "" {
		addr = "localhost:50052"
	}
	conn, err := grpc.NewClient(addr,
		grpc.WithTransportCredentials(insecure.NewCredentials()),
		grpc.WithConnectParams(grpc.ConnectParams{
			MinConnectTimeout: 5 * time.Second,
		}),
	)
	if err != nil {
		return nil, err
	}

	client := gen.NewImageServiceClient(conn)
	return &Client{
		client: client,
		conn:   conn,
	}, nil
}

func (c *Client) Close() error {
	return c.conn.Close()
}

func (c *Client) AddImage(ctx context.Context, image []byte) (string, error) {
	resp, err := c.client.AddImage(ctx, &gen.AddImageRequest{Image: image})
	if err != nil {
		return "", err
	}
	return resp.ImageId, nil
}

func (c *Client) GetImageByImageID(ctx context.Context, imageID string) ([]byte, error) {
	resp, err := c.client.GetImageByImageID(ctx, &gen.GetImageByImageIDRequest{ImageId: imageID})
	if err != nil {
		return nil, err
	}
	return resp.Image, nil
}

func (c *Client) ChangeImage(ctx context.Context, imageID string, image []byte) error {
	_, err := c.client.ChangeImage(ctx, &gen.ChangeImageRequest{
		ImageId: imageID,
		Image:   image,
	})
	return err
}

func (c *Client) DeleteImage(ctx context.Context, imageID string) error {
	_, err := c.client.DeleteImage(ctx, &gen.DeleteImageRequest{ImageId: imageID})
	return err
}

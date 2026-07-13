package handler

import (
	"context"
	"gen"
	"images/internal/domain"

	"github.com/google/uuid"
)

type ImageServer struct {
	gen.UnimplementedImageServiceServer
	repo domain.ImageRepository
}

func NewImagesServer(repo domain.ImageRepository) *ImageServer {
	return &ImageServer{repo: repo}
}

func (s *ImageServer) AddImage(ctx context.Context, req *gen.AddImageRequest) (*gen.AddImageResponse, error) {
	id, err := s.repo.AddImage(ctx, req.Image)
	if err != nil {
		return nil, err
	}
	return &gen.AddImageResponse{ImageId: id.String()}, nil
}

func (s *ImageServer) GetImageByImageID(ctx context.Context, req *gen.GetImageByImageIDRequest) (*gen.GetImageResponse, error) {
	imageID, err := uuid.Parse(req.ImageId)
	if err != nil {
		return nil, err
	}

	data, err := s.repo.GetImageByIID(ctx, imageID)
	if err != nil {
		return nil, err
	}
	return &gen.GetImageResponse{Image: data}, nil
}

func (s *ImageServer) ChangeImage(ctx context.Context, req *gen.ChangeImageRequest) (*gen.ChangeImageResponse, error) {
	ImageID, err := uuid.Parse(req.ImageId)
	if err != nil {
		return nil, err
	}
	err = s.repo.ChangeImage(ctx, req.Image, ImageID)
	if err != nil {
		return &gen.ChangeImageResponse{Success: false, Message: err.Error()}, nil
	}
	return &gen.ChangeImageResponse{Success: true, Message: "Image changed successfully"}, nil
}

func (s *ImageServer) DeleteImage(ctx context.Context, req *gen.DeleteImageRequest) (*gen.DeleteImageResponse, error) {
	imageID, err := uuid.Parse(req.ImageId)
	if err != nil {
		return nil, err
	}

	err = s.repo.DeleteImage(ctx, imageID)
	if err != nil {
		return &gen.DeleteImageResponse{Success: false, Message: err.Error()}, nil
	}
	return &gen.DeleteImageResponse{Success: true, Message: "Image deleted successfully"}, nil
}

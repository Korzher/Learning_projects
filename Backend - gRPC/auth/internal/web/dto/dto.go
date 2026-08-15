package dto

import (
	"grpc_auth/internal/domain"
	"grpc_auth/pkg/contracts"
)

func ReqToUser(req contracts.CreateUserRequest) *domain.User {
	return &domain.User{
		Email: req.Email,
		FirstName: req.FirstName,
		LastName: req.LastName,
		Phone: req.Phone,
		Password: req.Password,
	}
}
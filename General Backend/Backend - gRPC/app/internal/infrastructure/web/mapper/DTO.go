package mapper

import (
	"apifromspec/internal/domain"
	"apifromspec/internal/pkg"
	"context"
	"time"

	"github.com/google/uuid"
)

type AddressHandler struct {
	repo domain.AddressRepository
}

func NewAddressHandler(repo domain.AddressRepository) *AddressHandler {
	return &AddressHandler{
		repo: repo,
	}
}

func (a *AddressHandler) ReqToClient(ctx context.Context, req pkg.AddClientRequest) (*domain.Client, error) {
	addressID, err := a.repo.GetAddress(ctx, req.Country, req.City, req.Street)
	if err != nil {
		return nil, err
	}

	return &domain.Client{
		ClientName:    req.ClientName,
		ClientSurname: req.ClientSurname,
		Birthday:      req.Birthday,
		Gender:        req.Gender,
		AddressID:     addressID,
	}, nil
}

func (a *AddressHandler) ReqToAddress(ctx context.Context, req pkg.AddressChangeRequest) (uuid.UUID, error) {
	addressID, err := a.repo.GetAddress(ctx, req.Country, req.City, req.Street)
	if err != nil {
		return uuid.Nil, err
	}
	return addressID, nil
}

func (a *AddressHandler) ReqToSupplier(ctx context.Context, req pkg.AddSupplierRequest) (*domain.Supplier, error) {
	addressID, err := a.repo.GetAddress(ctx, req.Country, req.City, req.Street)
	if err != nil {
		return nil, pkg.ErrAddressNotFound
	}

	return &domain.Supplier{
		Name:        req.Name,
		PhoneNumber: req.PhoneNumber,
		AddressID:   addressID,
	}, nil
}

func CollectResponse(clients []domain.Client) []pkg.GetClientsResponse {
	response := make([]pkg.GetClientsResponse, len(clients))
	for i, client := range clients {
		response[i] = pkg.GetClientsResponse{
			ID:               client.ID,
			ClientName:       client.ClientName,
			ClientSurname:    client.ClientSurname,
			Birthday:         client.Birthday,
			Gender:           client.Gender,
			AddressID:        client.AddressID,
			RegistrationDate: client.RegistrationDate,
		}
	}
	return response
}

func ReqToProduct(req pkg.AddProductRequest) (*domain.Product, []byte) {
	prod := &domain.Product{
		ID:             uuid.New(),
		Name:           req.Name,
		Category:       req.Category,
		Price:          req.Price,
		AvailableStock: req.AvailableStock,
		SupplierID:     req.SupplierID,
		ImageID:        uuid.Nil,
		LastUpdateDate: time.Now(),
	}

	return prod, req.Image
}

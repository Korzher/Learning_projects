package pkg

import (
	"apifromspec/internal/domain"
	"time"

	"github.com/google/uuid"
)

// Клиенты
type AddClientRequest struct {
	ClientName    string        `json:"client_name" example:"Ivan" description:"Имя клиента"`
	ClientSurname string        `json:"client_surname" example:"Petrov" description:"Фамилия клиента"`
	Birthday      time.Time     `json:"birthday" example:"1990-01-15T00:00:00Z" description:"Дата рождения в формате RFC3339"`
	Gender        domain.Gender `json:"gender" example:"M" description:"Пол: M, F"`
	Country       string        `json:"country" example:"Russia" description:"Страна проживания"`
	City          string        `json:"city" example:"Moscow" description:"Город проживания"`
	Street        string        `json:"street" example:"Tverskaya" description:"Улица и номер дома"`
}

type DeleteClientRequest struct {
	ID uuid.UUID `json:"id"`
}

type GetClientsRequest struct {
	ClientName    string `json:"client_name" example:"Ivan" description:"Имя клиента"`
	ClientSurname string `json:"client_surname" example:"Petrov" description:"Фамилия клиента"`
}

type GetClientsResponse struct {
	ID               uuid.UUID     `json:"id" example:"550e8400-e29b-41d4-a716-446655440000"`
	ClientName       string        `json:"client_name" example:"Ivan"`
	ClientSurname    string        `json:"client_surname" example:"Petrov"`
	Birthday         time.Time     `json:"birthday" example:"1990-01-15T00:00:00Z"`
	Gender           domain.Gender `json:"gender" example:"M"`
	AddressID        uuid.UUID     `json:"address_id" example:"660f8400-e29b-41d4-a716-446655440011"`
	RegistrationDate time.Time     `json:"registration_date" example:"2026-04-28T10:00:00Z"`
}

type Pagination struct {
	Total      int `json:"total" example:"5"`
	Limit      int `json:"limit" example:"3"`
	Offset     int `json:"offset" example:"0"`
	NextOffset int `json:"next_offset" example:"1"`
}

type GetClientsMeta struct {
	Data       []GetClientsResponse `json:"data"`
	Pagination Pagination           `json:"pagination"`
}

type AddressChangeRequest struct {
	Country string `json:"country" example:"Russia"`
	City    string `json:"city" example:"Saint Petersburg"`
	Street  string `json:"street" example:"Nevskiy Prospect"`
}

// Товары
type AddProductRequest struct {
	Name           string    `json:"name" example:"Laptop Air"`
	Category       string    `json:"category" example:"Laptops"`
	Price          int64     `json:"price" example:"120000"`
	AvailableStock int       `json:"available_stock" example:"10"`
	SupplierID     uuid.UUID `json:"supplier_id" example:"550e8400-e29b-41d4-a716-446655440000"`
	Image          []byte    `json:"image" swaggertype:"string" format:"base64"`
}

type SubtractProductRequest struct {
	Amount int `json:"amount" example:"3"`
}

type GetProductRequest struct {
	ID uuid.UUID `json:"id"`
}

type GetProductResponse struct {
	ID             uuid.UUID `json:"id" example:"770e8400-e29b-41d4-a716-446655440022"`
	Name           string    `json:"name" example:"Laptop Air"`
	Category       string    `json:"category" example:"Laptops"`
	Price          int64     `json:"price" example:"120000"`
	AvailableStock int       `json:"available_stock" example:"10"`
	SupplierID     uuid.UUID `json:"supplier_id" example:"550e8400-e29b-41d4-a716-446655440000"`
	ImageID        uuid.UUID `json:"image_id" example:"880e8400-e29b-41d4-a716-446655440033"`
	LastUpdateDate time.Time `json:"last_update_date" example:"2026-04-28T12:00:00Z"`
}

type DeleteProductRequest struct {
	ID uuid.UUID `json:"id"`
}

// Поставщики
type AddSupplierRequest struct {
	Name        string `json:"name" example:"Tech Wholesale"`
	PhoneNumber string `json:"phone_number" example:"+70001112233"`
	Country     string `json:"country" example:"Russia"`
	City        string `json:"city" example:"Moscow"`
	Street      string `json:"street" example:"Tverskaya"`
}

type DeleteSupplierRequest struct {
	ID uuid.UUID `json:"id"`
}

type GetSuplierByIDRequest struct {
	ID uuid.UUID `json:"id"`
}

type GetSupplierResponse struct {
	ID          uuid.UUID `json:"id" example:"550e8400-e29b-41d4-a716-446655440000"`
	Name        string    `json:"name" example:"Tech Wholesale"`
	AddressID   uuid.UUID `json:"address_id" example:"660f8400-e29b-41d4-a716-446655440011"`
	PhoneNumber string    `json:"phone_number" example:"+70001112233"`
}

// Картинки
type AddImageRequest struct {
	ProductID uuid.UUID `json:"product_id" example:"770e8400-e29b-41d4-a716-446655440022"`
	Image     []byte    `json:"image" swaggertype:"string" format:"base64"`
}

type ChangeImageRequest struct {
	Image []byte `json:"image" swaggertype:"string" format:"base64"`
}

type GetImageByProductRequest struct {
	ProductID uuid.UUID `json:"product_id"`
}

type GetImageByIDRequest struct {
	ID uuid.UUID `json:"id"`
}

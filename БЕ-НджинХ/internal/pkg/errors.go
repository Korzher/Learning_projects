package pkg

import "errors"

var (
	ErrIDNotFound            = errors.New("ID does not exist")
	ErrClientAlreadyExists   = errors.New("client already exists")
	ErrSupplierAlreadyExists = errors.New("supplier already exists")
	ErrInvalidGender         = errors.New("invalid gender, must be M or F")
	ErrAddressNotFound       = errors.New("address was not found")
	ErrInsufficientStock     = errors.New("insufficient stock or product not found")
	ErrImageNotFound         = errors.New("image not found")
	ErrFailToFetch           = errors.New("fail to fetch product")
)

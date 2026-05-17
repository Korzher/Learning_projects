package handler

import (
	"apifromspec/internal/domain"
	"apifromspec/internal/infrastructure/web/mapper"
	"apifromspec/internal/infrastructure/web/utils"
	"apifromspec/internal/pkg"
	"encoding/json"
	"errors"
	"net/http"

	"github.com/google/uuid"
)

type SupplierHandler struct {
	repo           domain.SupplierRepository
	addressHandler *mapper.AddressHandler
}

func NewSupplierHandler(repo domain.SupplierRepository, addressHandler *mapper.AddressHandler) *SupplierHandler {
	return &SupplierHandler{
		repo:           repo,
		addressHandler: addressHandler,
	}
}

// AddSupplier godoc
// @Summary      Добавление поставщика
// @Description  Добавление поставщика в базу данных
// @Tags         suppliers
// @Accept       json
// @Produce      json
// @Param        request body pkg.AddSupplierRequest true "Данные для добавления поставщика"
// @Success      201  {object}  string  "supplier added successfully"
// @Failure      400  {object}  string  "wrong input format"
// @Failure      409  {object}  string  "supplier already exists"
// @Failure      500  {object}  string  "internal error"
// @Router       /suppliers [post]
func (s *SupplierHandler) AddSupplier(w http.ResponseWriter, r *http.Request) {
	var req pkg.AddSupplierRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}

	if err := validateSupplierRequest(req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, err.Error())
		return
	}

	ctx := r.Context()
	supplier, err := s.addressHandler.ReqToSupplier(ctx, req)
	if err != nil {
		utils.RespondJSON(w, http.StatusInternalServerError, "internal error")
		return
	}

	supplier.ID = uuid.New()

	if err := s.repo.AddSupplier(ctx, supplier); err != nil {
		switch {
		case errors.Is(err, pkg.ErrSupplierAlreadyExists):
			utils.RespondJSON(w, http.StatusConflict, "supplier already exists")
		default:
			utils.RespondJSON(w, http.StatusInternalServerError, "failed to add supplier")
		}
		return
	}

	utils.RespondJSON(w, http.StatusCreated, "supplier added successfully")
}

// DeleteSupplier godoc
// @Summary      Удаляет поставщика из базы данных
// @Description  Возвращает информацию об успешности операции
// @Tags         suppliers
// @Accept       json
// @Produce      json
// @Param        id path string true "ID поставщика для удаления"
// @Success      200  {object}  string  "supplier deleted successfully"
// @Failure      400  {object}  string  "wrong input format or can not parse id from URL"
// @Failure      404  {object}  string  "supplier not found"
// @Failure      500  {object}  string  "failed to delete supplier"
// @Router       /suppliers/{id} [delete]
func (s *SupplierHandler) DeleteSupplier(w http.ResponseWriter, r *http.Request) {
	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "can not parse id from URL")
		return
	}

	ctx := r.Context()
	if err := s.repo.DeleteSupplier(ctx, id); err != nil {
		if errors.Is(err, pkg.ErrIDNotFound) {
			utils.RespondJSON(w, http.StatusNotFound, "supplier not found")
			return
		}
		utils.RespondJSON(w, http.StatusInternalServerError, "failed to delete supplier")
		return
	}

	utils.RespondJSON(w, http.StatusOK, "supplier deleted successfully")
}

// GetSupplier godoc
// @Summary      Получение поставщика по id
// @Description  Возвращает найденного поставщика
// @Tags         suppliers
// @Accept       json
// @Produce      json
// @Param        id path string true "ID поставщика" format(uuid)
// @Success      200  {object}  pkg.GetSupplierResponse
// @Failure      400  {object}  string  "can not parse id from URL"
// @Failure      404  {object}  string  "supplier not found"
// @Failure      500  {object}  string  "fail to fetch supplier"
// @Router       /suppliers/{id} [get]
func (s *SupplierHandler) GetSupplier(w http.ResponseWriter, r *http.Request) {
	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "can not parse id from URL")
		return
	}

	ctx := r.Context()

	supplier, err := s.repo.GetSupplier(ctx, id)
	if err != nil {
		if errors.Is(err, pkg.ErrIDNotFound) {
			utils.RespondJSON(w, http.StatusNotFound, "supplier not found")
			return
		}
		utils.RespondJSON(w, http.StatusInternalServerError, "fail to fetch supplier")
		return
	}

	response := &pkg.GetSupplierResponse{
		ID:          supplier.ID,
		Name:        supplier.Name,
		PhoneNumber: supplier.PhoneNumber,
		AddressID:   supplier.AddressID,
	}

	utils.RespondJSON(w, http.StatusOK, response)
}

// GetAllSuppliers godoc
// @Summary      Получение всех поставщиков
// @Description  Возвращает массив поставщиков. Если товары не найдены, возвращает пустой массив.
// @Tags         suppliers
// @Accept       json
// @Produce      json
// @Success      200  {object}  []pkg.GetSupplierResponse
// @Failure      500  {object}  string  "fail to fetch suppliers"
// @Router       /suppliers [get]
func (s *SupplierHandler) GetAllSuppliers(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()

	suppliers, err := s.repo.GetAllSuppliers(ctx)
	if err != nil {
		utils.RespondJSON(w, http.StatusInternalServerError, "fail to fetch suppliers")
		return
	}

	response := make([]pkg.GetSupplierResponse, len(suppliers))
	for i, supplier := range suppliers {
		response[i] = pkg.GetSupplierResponse{
			ID:          supplier.ID,
			Name:        supplier.Name,
			PhoneNumber: supplier.PhoneNumber,
			AddressID:   supplier.AddressID,
		}
	}

	utils.RespondJSON(w, http.StatusOK, response)
}

// AddressChange godoc
// @Summary      Смена адреса для поставщика
// @Description  Заменяет адрес поставщика в базе данных
// @Tags         suppliers
// @Accept       json
// @Produce      json
// @Param        id path string true "ID поставщика" format(uuid)
// @Param        request body pkg.AddressChangeRequest true "Параметры нового адреса поставщика"
// @Success      200  {object}  string  "address changed successfully"
// @Failure      400  {object}  string "wrong input format or validation error"
// @Failure      404  {object}  string "id not found"
// @Failure      500  {object}  string "failed to process address"
// @Router       /suppliers/{id}/address [patch]
func (s *SupplierHandler) AddressChange(w http.ResponseWriter, r *http.Request) {
	var req pkg.AddressChangeRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}

	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "can not parse id from URL")
		return
	}

	if req.Country == "" || req.City == "" || req.Street == "" {
		utils.RespondJSON(w, http.StatusBadRequest, "country, city, street are required")
		return
	}

	ctx := r.Context()
	addressID, err := s.addressHandler.ReqToAddress(ctx, req)
	if err != nil {
		utils.RespondJSON(w, http.StatusInternalServerError, "failed to process address")
		return
	}

	err = s.repo.AddressChange(ctx, id, addressID)
	if err != nil {
		if errors.Is(err, pkg.ErrIDNotFound) {
			utils.RespondJSON(w, http.StatusNotFound, "Id not found")
			return
		}
		utils.RespondJSON(w, http.StatusInternalServerError, "failed to update supplier address")
		return
	}

	utils.RespondJSON(w, http.StatusOK, "address changed successfully")
}

func (s *SupplierHandler) RegisterRoutes(mux *http.ServeMux) {
	mux.HandleFunc("POST /api/v1/suppliers", s.AddSupplier)
	mux.HandleFunc("DELETE /api/v1/suppliers/{id}", s.DeleteSupplier)
	mux.HandleFunc("GET /api/v1/suppliers", s.GetAllSuppliers)
	mux.HandleFunc("GET /api/v1/suppliers/{id}", s.GetSupplier)
	mux.HandleFunc("PATCH /api/v1/suppliers/{id}/address", s.AddressChange)
}

func validateSupplierRequest(req pkg.AddSupplierRequest) error {
	if req.Name == "" {
		return errors.New("supplier_name is required")
	}
	if req.PhoneNumber == "" {
		return errors.New("phone_number is required")
	}
	if req.Country == "" || req.City == "" || req.Street == "" {
		return errors.New("country, city, street are required")
	}
	return nil
}

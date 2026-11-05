package handler

import (
	"apifromspec/internal/application"
	"apifromspec/internal/domain"
	"apifromspec/internal/infrastructure/web/mapper"
	"apifromspec/internal/infrastructure/web/utils"
	"apifromspec/internal/pkg"
	"encoding/json"
	"errors"
	"net/http"

	"github.com/google/uuid"
)

type ProductHandler struct {
	repo    domain.ProductRepository
	service *application.ProductService
}

func NewProductHandler(repo domain.ProductRepository, service *application.ProductService) *ProductHandler {
	return &ProductHandler{
		repo:    repo,
		service: service,
	}
}

// AddProduct godoc
// @Summary      Добавление товара в базу данных
// @Description  Возвращает информацию об успешности операции
// @Tags         products
// @Accept       json
// @Produce      json
// @Param        request body pkg.AddProductRequest true "Данные для добавления товара"
// @Success      201  {object}  domain.Product "product added successfully"
// @Failure      400  {object}  string  "wrong input format or validation error"
// @Failure      500  {object}  string  "failed to create product"
// @Router       /products [post]
func (p *ProductHandler) AddProduct(w http.ResponseWriter, r *http.Request) {
	var req pkg.AddProductRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}

	if err := validateProductRequest(req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, err.Error())
		return
	}

	product, image := mapper.ReqToProduct(req)
	ctx := r.Context()
	if err := p.service.CreateProduct(ctx, product, image); err != nil {
		utils.RespondJSON(w, http.StatusInternalServerError, "failed to create product")
		return
	}

	utils.RespondJSON(w, http.StatusCreated, product)
}

// SubtractProduct godoc
// @Summary      Вычитание товара из базы при наличии
// @Description  Возвращает информацию об успешности операции
// @Tags         products
// @Accept       json
// @Produce      json
// @Param        id path string true "ID товара" format(uuid)
// @Param        request body pkg.SubtractProductRequest true "Данные для вычитания товара"
// @Success      200  {object}  string  "amount decreased successfully"
// @Failure      400  {object}  string  "wrong input format, validation error or insufficient stock"
// @Failure      500  {object}  string  "internal error"
// @Router       /products/{id}/subtract [patch]
func (p *ProductHandler) SubtractProduct(w http.ResponseWriter, r *http.Request) {
	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "can not parse id from URL")
		return
	}

	var req pkg.SubtractProductRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}

	if req.Amount <= 0 {
		utils.RespondJSON(w, http.StatusBadRequest, "amount must be positive")
		return
	}

	ctx := r.Context()
	err = p.repo.SubtractProduct(ctx, id, req.Amount)
	if err != nil {
		if errors.Is(err, pkg.ErrInsufficientStock) {
			utils.RespondJSON(w, http.StatusBadRequest, err.Error())
			return
		}
		utils.RespondJSON(w, http.StatusInternalServerError, "internal error")
		return
	}

	utils.RespondJSON(w, http.StatusOK, "amount decreased successfully")
}

// GetProduct godoc
// @Summary      Получение товара по id
// @Description  Возвращает найденный товар
// @Tags         products
// @Accept       json
// @Produce      json
// @Param        id path string true "ID товара" format(uuid)
// @Success      200  {object}  pkg.GetProductResponse
// @Failure      400  {object}  string  "wrong input format"
// @Failure      404  {object}  string  "product not found"
// @Failure      500  {object}  string  "internal error"
// @Router       /products/{id} [get]
func (p *ProductHandler) GetProduct(w http.ResponseWriter, r *http.Request) {
	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "can not parse id from URL")
		return
	}

	ctx := r.Context()

	product, err := p.repo.GetProduct(ctx, id)
	if err != nil {
		if errors.Is(err, pkg.ErrIDNotFound) {
			utils.RespondJSON(w, http.StatusNotFound, "product not found")
			return
		}
		utils.RespondJSON(w, http.StatusInternalServerError, "fail to fetch product")
		return
	}

	response := &pkg.GetProductResponse{
		ID:             product.ID,
		Name:           product.Name,
		Category:       product.Category,
		Price:          product.Price,
		AvailableStock: product.AvailableStock,
		SupplierID:     product.SupplierID,
		ImageID:        product.ImageID,
		LastUpdateDate: product.LastUpdateDate,
	}

	utils.RespondJSON(w, http.StatusOK, response)
}

// GetAllProducts godoc
// @Summary      Получение всех товаров
// @Description  Возвращает массив товаров. Если товары не найдены, возвращает пустой массив.
// @Tags         products
// @Accept       json
// @Produce      json
// @Success      200  {object}  []pkg.GetProductResponse
// @Failure      500  {object}  string  "fail to fetch products"
// @Router       /products [get]
func (p *ProductHandler) GetAllProducts(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()
	products, err := p.repo.GetAllProducts(ctx)
	if err != nil {
		utils.RespondJSON(w, http.StatusInternalServerError, "fail to fetch products")
		return
	}

	response := make([]pkg.GetProductResponse, len(products))
	for i, product := range products {
		response[i] = pkg.GetProductResponse{
			ID:             product.ID,
			Name:           product.Name,
			Category:       product.Category,
			Price:          product.Price,
			AvailableStock: product.AvailableStock,
			SupplierID:     product.SupplierID,
			ImageID:        product.ImageID,
			LastUpdateDate: product.LastUpdateDate,
		}
	}

	utils.RespondJSON(w, http.StatusOK, response)
}

// DeleteProduct godoc
// @Summary      Удаляет товар из базы данных
// @Description  Возвращает информацию об успешности операции
// @Tags         products
// @Accept       json
// @Produce      json
// @Param        id path string true "ID товара для удаления"
// @Success      200  {object}  string  "product deleted successfully"
// @Failure      400  {object}  string  "wrong input format or can not parse id from URL"
// @Failure      404  {object}  string  "product not found"
// @Failure      500  {object}  string  "failed to delete product"
// @Router       /products/{id} [delete]
func (p *ProductHandler) DeleteProduct(w http.ResponseWriter, r *http.Request) {
	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "can not parse id from URL")
		return
	}

	ctx := r.Context()
	if err := p.repo.DeleteProduct(ctx, id); err != nil {
		if errors.Is(err, pkg.ErrIDNotFound) {
			utils.RespondJSON(w, http.StatusNotFound, "product not found")
			return
		}
		utils.RespondJSON(w, http.StatusInternalServerError, "failed to delete product")
		return
	}

	utils.RespondJSON(w, http.StatusOK, "product deleted successfully")
}

func (p *ProductHandler) RegisterRoutes(mux *http.ServeMux) {
	mux.HandleFunc("POST /api/v1/products", p.AddProduct)
	mux.HandleFunc("GET /api/v1/products", p.GetAllProducts)
	mux.HandleFunc("GET /api/v1/products/{id}", p.GetProduct)
	mux.HandleFunc("PATCH /api/v1/products/{id}/subtract", p.SubtractProduct)
	mux.HandleFunc("DELETE /api/v1/products/{id}", p.DeleteProduct)
}

func validateProductRequest(req pkg.AddProductRequest) error {
	if req.Name == "" {
		return errors.New("product_name is required")
	}
	if req.Category == "" {
		return errors.New("category is required")
	}
	if req.Price <= 0 {
		return errors.New("price must be positive")
	}
	if req.AvailableStock < 0 {
		return errors.New("Stock must not be negative")
	}
	if req.SupplierID == uuid.Nil {
		return errors.New("Supplier must not be nil")
	}
	return nil
}

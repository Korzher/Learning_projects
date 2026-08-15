package handler

import (
	"apifromspec/internal/application"
	"apifromspec/internal/domain"
	"apifromspec/internal/infrastructure/web/utils"
	"apifromspec/internal/pkg"
	"encoding/json"
	"errors"
	"net/http"

	"github.com/google/uuid"
)

type ImageHandler struct {
	repo    domain.ImageRepository
	service *application.ProductService
}

func NewImageHandler(repo domain.ImageRepository, service *application.ProductService) *ImageHandler {
	return &ImageHandler{
		repo:    repo,
		service: service,
	}
}

// AddImage godoc
// @Summary      Добавление изображения продукту
// @Description  Добавление изображения к существующему товару
// @Tags         images
// @Accept       json
// @Produce      json
// @Param        request body pkg.AddImageRequest true "ID продукта и новое изображение в формате base64"
// @Success      201  {object}  string "image added and assigned to product successfully"
// @Failure      400  {object}  string "wrong input format or validation error"
// @Failure      500  {object}  string "failed to add image to product"
// @Router       /image [post]
func (i *ImageHandler) AddImage(w http.ResponseWriter, r *http.Request) {
	var req pkg.AddImageRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}

	if req.ProductID == uuid.Nil {
		utils.RespondJSON(w, http.StatusBadRequest, "product_id is required")
		return
	}

	if len(req.Image) == 0 {
		utils.RespondJSON(w, http.StatusBadRequest, "image data is empty")
		return
	}

	ctx := r.Context()
	err := i.service.AddImageToProduct(ctx, req.ProductID, req.Image)
	if err != nil {
		utils.RespondJSON(w, http.StatusInternalServerError, "failed to add image to product")
		return
	}

	utils.RespondJSON(w, http.StatusCreated, "image added and assigned to product successfully")
}

// ChangeImage godoc
// @Summary      Изменение изображения в базе
// @Description  Изменение существующего  изображения в базе
// @Tags         images
// @Accept       json
// @Produce      json
// @Param        id path string true "ID изображения" format(uuid)
// @Param        request body pkg.ChangeImageRequest true "новое изображение в формате base64"
// @Success      200  {object}  string  "image changed successfully"
// @Failure      400  {object}  string "invalid id format, wrong input format or validation error"
// @Failure      404  {object}  string "image not found"
// @Failure      500  {object}  string "failed to change image"
// @Router       /image/{id} [put]
func (i *ImageHandler) ChangeImage(w http.ResponseWriter, r *http.Request) {
	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "invalid id format")
		return
	}

	var req pkg.ChangeImageRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}

	if len(req.Image) == 0 {
		utils.RespondJSON(w, http.StatusBadRequest, "image is empty")
		return
	}

	ctx := r.Context()
	err = i.repo.ChangeImage(ctx, req.Image, id)
	if err != nil {
		if errors.Is(err, pkg.ErrImageNotFound) {
			utils.RespondJSON(w, http.StatusNotFound, "image not found")
			return
		}
		utils.RespondJSON(w, http.StatusInternalServerError, "failed to change image")
		return
	}

	utils.RespondJSON(w, http.StatusOK, "image changed successfully")
}

// DeleteImage godoc
// @Summary      Удаление изображения
// @Description  Удаление  изображения из базы
// @Tags         images
// @Accept       json
// @Produce      json
// @Param        id path string true "ID изображения" format(uuid)
// @Param        request path uuid true "ID изображения для удаления"
// @Success      200  {object}  string  "image deleted successfully"
// @Failure      400  {object}  string "invalid image id"
// @Failure      404  {object}  string "image not found"
// @Failure      500  {object}  string "failed to delete image"
// @Router       /image/{id} [delete]
func (i *ImageHandler) DeleteImage(w http.ResponseWriter, r *http.Request) {
	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "invalid image id")
		return
	}

	ctx := r.Context()
	err = i.repo.DeleteImage(ctx, id)
	if err != nil {
		if err.Error() == "ID does not exist" {
			utils.RespondJSON(w, http.StatusNotFound, "image not found")
			return
		}
		utils.RespondJSON(w, http.StatusInternalServerError, "failed to delete image")
		return
	}

	utils.RespondJSON(w, http.StatusOK, "image deleted successfully")
}

// GetImageByProductID godoc
// @Summary      Получение изображения по id товара
// @Description  Получение изображения по id товара
// @Tags         images
// @Accept       json
// @Produce      application/octet-stream
// @Param        id path string true "ID товара" format(uuid)
// @Success      200  {file}  file  "изображение в виде файла"
// @Failure      400  {object}  string "invalid product id"
// @Failure      404  {object}  string "image not found"
// @Failure      500  {object}  string "internal server error"
// @Router       /image/product/{id} [get]
func (i *ImageHandler) GetImageByPID(w http.ResponseWriter, r *http.Request) {
	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "invalid product id")
		return
	}

	ctx := r.Context()
	image, err := i.repo.GetImageByPID(ctx, id)
	if err != nil {
		if errors.Is(err, pkg.ErrImageNotFound) {
			utils.RespondJSON(w, http.StatusNotFound, "image not found")
			return
		}
		utils.RespondJSON(w, http.StatusInternalServerError, "failed to retrieve image")
		return
	}

	utils.RespondImage(w, http.StatusOK, image)
}

// GetImageByImageID godoc
// @Summary      Получение изображения по id изображения
// @Description  Получение изображения по id изображения
// @Tags         images
// @Accept       json
// @Produce      application/octet-stream
// @Param        id path string true "ID изображения" format(uuid)
// @Success      200  {file}  file  "изображение в виде файла"
// @Failure      400  {object}  string "invalid image id"
// @Failure      404  {object}  string "image not found"
// @Failure      500  {object}  string "internal server error"
// @Router       /image/{id} [get]
func (i *ImageHandler) GetImageByIID(w http.ResponseWriter, r *http.Request) {
	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		utils.RespondJSON(w, http.StatusBadRequest, "invalid image id")
		return
	}

	ctx := r.Context()
	image, err := i.repo.GetImageByIID(ctx, id)
	if err != nil {
		if errors.Is(err, pkg.ErrImageNotFound) {
			utils.RespondJSON(w, http.StatusNotFound, "image not found")
			return
		}
		utils.RespondJSON(w, http.StatusInternalServerError, "internal server error")
		return
	}
	utils.RespondImage(w, http.StatusOK, image)
}

func (i *ImageHandler) RegisterRoutes(mux *http.ServeMux) {
	mux.HandleFunc("GET /api/v1/image/product/{id}", i.GetImageByPID)
	mux.HandleFunc("GET /api/v1/image/{id}", i.GetImageByIID)
	mux.HandleFunc("POST /api/v1/image", i.AddImage)
	mux.HandleFunc("PUT /api/v1/image/{id}", i.ChangeImage)
	mux.HandleFunc("DELETE /api/v1/image/{id}", i.DeleteImage)
}

package handler

import (
	"apifromspec/internal/domain"
	"apifromspec/internal/infrastructure/web/mapper"
	"apifromspec/internal/pkg"
	"encoding/json"
	"errors"
	"fmt"
	"net/http"
	"strconv"
	"strings"
	"time"

	"github.com/google/uuid"
)

type ClientHandler struct {
	repo           domain.ClientRepository
	addressHandler *mapper.AddressHandler
}

func NewClientHandler(repo domain.ClientRepository, addressHandler *mapper.AddressHandler) *ClientHandler {
	return &ClientHandler{
		repo:           repo,
		addressHandler: addressHandler,
	}
}

// AddClient godoc
// @Summary      Добавление клиента в базу данных
// @Description  Возвращает информацию об успешности операции
// @Tags         clients
// @Accept       json
// @Produce      json
// @Param        request body pkg.AddClientRequest true "Данные для добавления клиента"
// @Success      201  {object}  pkg.GetClientsResponse  "client created successfully"
// @Failure      400  {object}  string  "wrong input format or validation error"
// @Failure      409  {object}  string  "client already exists"
// @Failure      500  {object}  string  "failed to add client"
// @Router       /clients [post]
func (c *ClientHandler) AddClient(w http.ResponseWriter, r *http.Request) {
	var req pkg.AddClientRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		respondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}

	if err := validateClientRequest(req); err != nil {
		respondJSON(w, http.StatusBadRequest, err.Error())
		return
	}

	ctx := r.Context()
	client, err := c.addressHandler.ReqToClient(ctx, req)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, err)
		return
	}

	client.ID = uuid.New()

	if err := c.repo.AddClient(ctx, client); err != nil {
		switch {
		case errors.Is(err, pkg.ErrClientAlreadyExists):
			respondJSON(w, http.StatusConflict, "client already exists")
		default:
			respondJSON(w, http.StatusInternalServerError, "failed to add client")
		}
		return
	}

	respondJSON(w, http.StatusCreated, client)
}

// DeleteClient godoc
// @Summary      Удаляет клиента из базы данных
// @Description  Возвращает информацию об успешности операции
// @Tags         clients
// @Accept       json
// @Produce      json
// @Param        id path string true "ID клиента для удаления"
// @Success      200  {object}  string  "client deleted successfully"
// @Failure      400  {object}  string  "wrong input format or can not parse id from URL"
// @Failure      404  {object}  string  "client not found"
// @Failure      500  {object}  string  "failed to delete client"
// @Router       /clients/{id} [delete]
func (c *ClientHandler) DeleteClient(w http.ResponseWriter, r *http.Request) {
	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, "can not parse id from URL")
		return
	}

	ctx := r.Context()
	if err := c.repo.DeleteClient(ctx, id); err != nil {
		if errors.Is(err, pkg.ErrIDNotFound) {
			respondJSON(w, http.StatusNotFound, "client not found")
			return
		}
		respondJSON(w, http.StatusInternalServerError, "failed to delete client")
		return
	}

	respondJSON(w, http.StatusOK, "client deleted successfully")
}

// GetClients godoc
// @Summary      Получает клиентов из базы данных по имени и фамилии
// @Description  Возвращает массив клиентов, соответствующих запросу. Если клиенты не найдены, возвращает пустой массив.
// @Tags         clients
// @Accept       json
// @Produce      json
// @Param        name query string true "Имя клиента"
// @Param        surname query string true "Фамилия клиента"
// @Success      200  {object}  pkg.GetClientsResponse  "список клиентов (может быть пустым)"
// @Failure      400  {object}  string "name and surname are required"
// @Failure      500  {object}  string "failed to fetch client"
// @Router       /clients/search [get]
func (c *ClientHandler) GetClient(w http.ResponseWriter, r *http.Request) {
	name := strings.TrimSpace(r.URL.Query().Get("name"))
	surname := strings.TrimSpace(r.URL.Query().Get("surname"))

	if name == "" || surname == "" {
		respondJSON(w, http.StatusBadRequest, "name and surname are required")
		return
	}

	ctx := r.Context()

	clients, err := c.repo.GetClient(ctx, name, surname)
	if err != nil {
		respondJSON(w, http.StatusInternalServerError, "failed to fetch client")
		return
	}

	response := mapper.CollectResponse(clients)

	respondJSON(w, http.StatusOK, response)
}

// GetAllClients godoc
// @Summary      Получает всех клиентов из базы данных с пагинацией
// @Description  Возвращает массив клиентов с метаинформацией о пагинации
// @Tags         clients
// @Accept       json
// @Produce      json
// @Param        limit query int false "limit"
// @Param        offset query int false "offset"
// @Success      200  {object}  pkg.GetClientsMeta  "список клиентов с метаинформацией"
// @Failure      500  {object}  string "failed to fetch clients"
// @Router       /clients [get]
func (c *ClientHandler) GetAllClients(w http.ResponseWriter, r *http.Request) {
	limit := 0
	if l, err := strconv.Atoi(r.URL.Query().Get("limit")); err == nil && l > 0 {
		limit = l
	}

	offset := 0
	if o, err := strconv.Atoi(r.URL.Query().Get("offset")); err == nil && o >= 0 {
		offset = o
	}

	ctx := r.Context()

	clients, total, err := c.repo.GetAllClients(ctx, limit, offset)
	if err != nil {
		respondJSON(w, http.StatusInternalServerError, "failed to fetch clients")
		return
	}

	data := mapper.CollectResponse(clients)

	pagination := pkg.Pagination{
		Total:  total,
		Limit:  limit,
		Offset: offset,
		NextOffset: func() int {
			if offset+limit < total && limit > 0 {
				return offset + limit
			}
			return -1
		}(),
	}

	response := pkg.GetClientsMeta{
		Data:       data,
		Pagination: pagination,
	}

	respondJSON(w, http.StatusOK, response)
}

// AddressChange godoc
// @Summary      Смена адреса для клиента
// @Description  Заменяет адрес клиента в базе данных
// @Tags         clients
// @Accept       json
// @Produce      json
// @Param        id path string true "ID клиента" format(uuid)
// @Param        request body pkg.AddressChangeRequest true "Параметры нового адреса клиента"
// @Success      200  {object}  string "address changed successfully"
// @Failure      400  {object}  string "wrong input format or validation error"
// @Failure      404  {object}  string "id not found"
// @Failure      500  {object}  string "failed to process address"
// @Router       /clients/{id}/address [patch]
func (c *ClientHandler) AddressChange(w http.ResponseWriter, r *http.Request) {
	idStr := r.PathValue("id")
	id, err := uuid.Parse(idStr)
	if err != nil {
		respondJSON(w, http.StatusBadRequest, "can not parse id from URL")
		return
	}

	var req pkg.AddressChangeRequest
	decoder := json.NewDecoder(r.Body)
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&req); err != nil {
		respondJSON(w, http.StatusBadRequest, "wrong input format")
		return
	}

	if req.Country == "" || req.City == "" || req.Street == "" {
		respondJSON(w, http.StatusBadRequest, "country, city, street are required")
		return
	}

	ctx := r.Context()
	addressID, err := c.addressHandler.ReqToAddress(ctx, req)
	if err != nil {
		respondJSON(w, http.StatusInternalServerError, "failed to process address")
		return
	}

	err = c.repo.AddressChange(ctx, id, addressID)
	if err != nil {
		if errors.Is(err, pkg.ErrIDNotFound) {
			respondJSON(w, http.StatusNotFound, "Id not found")
			return
		}
		respondJSON(w, http.StatusInternalServerError, "failed to update client address")
		return
	}

	respondJSON(w, http.StatusOK, "address changed successfully")
}

func (c *ClientHandler) RegisterRoutes(mux *http.ServeMux) {
	mux.HandleFunc("POST /api/v1/clients", c.AddClient)
	mux.HandleFunc("DELETE /api/v1/clients/{id}", c.DeleteClient)
	mux.HandleFunc("GET /api/v1/clients", c.GetAllClients)
	mux.HandleFunc("GET /api/v1/clients/search", c.GetClient)
	mux.HandleFunc("PATCH /api/v1/clients/{id}/address", c.AddressChange)
}

func validateClientRequest(req pkg.AddClientRequest) error {
	if req.ClientName == "" {
		return errors.New("client_name is required")
	}
	if req.ClientSurname == "" {
		return errors.New("client_surname is required")
	}
	if req.Birthday.IsZero() {
		return errors.New("birthday is required")
	}
	if req.Birthday.After(time.Now()) {
		return errors.New("birthday cannot be in the future")
	}
	if req.Gender != domain.Male && req.Gender != domain.Female {
		return fmt.Errorf("gender must be either '%s' or '%s'", domain.Male, domain.Female)
	}
	if req.Country == "" || req.City == "" || req.Street == "" {
		return errors.New("country, city, street are required")
	}
	return nil
}

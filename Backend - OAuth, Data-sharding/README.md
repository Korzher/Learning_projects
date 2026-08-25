# TechShop — Backend

REST API и микросервисная архитектура на Go: управление клиентами, товарами и поставщиками, хранение и шардирование изображений, полноценная авторизация (JWT + bcrypt + Google OAuth 2.0).

## Оглавление

- [Возможности](#возможности)
- [Архитектура](#архитектура)
- [Технологический стек](#технологический-стек)
- [Структура репозитория](#структура-репозитория)
- [Требования](#требования)
- [Быстрый старт](#быстрый-старт)
- [Переменные окружения](#переменные-окружения)
- [База данных](#база-данных)
- [API](#api)
- [Авторизация](#авторизация)
- [Шардирование изображений](#шардирование-изображений)
- [Обработка ошибок](#обработка-ошибок)
- [Тестирование](#тестирование)
- [CI/CD](#cicd)
- [Аварийное завершение](#аварийное-завершение)
- [Продакшен-чеклист](#продакшен-чеклист)
- [Дорожная карта](#дорожная-карта)

---

## Возможности

- **REST API** из **26 эндпоинтов** для 5 сущностей с CRUD, фильтрацией и
  пагинацией.
- **20 защищённых эндпоинтов** — JWT-валидация через gRPC-запрос к сервису
  авторизации.
- **3 микросервиса**: `app` (REST), `auth` (gRPC), `images` (gRPC), каждый
  со своей базой данных.
- **Авторизация**: регистрация/вход, JWT (access + refresh), bcrypt,
  Google OAuth 2.0.
- **Шардирование** изображений по **4 базам PostgreSQL** с динамическим
  выбором целевого шарда по UUID.
- **Docker Compose**: запуск окружения из **9 контейнеров**.
- **Swagger UI** для интерактивного тестирования API.
- Миграции схемы БД, graceful shutdown, dependency injection, чистая
  многослойная архитектура.

---

## Архитектура

```text
                    ┌─────────────────────────────────────────────┐
                    │                   app :8080                 │
                    │  REST API (26 endpoint'ов)                  │
                    │  Swagger UI /swagger/                       │
                    │  DI (uber fx), middleware (JWT)             │
                    └───────┬──────────────┬──────────────┬───────┘
                            │ gRPC         │ gRPC         │ SQL
                            ▼              ▼              ▼
              ┌───────────────┐   ┌───────────────┐   ┌──────────────┐
              │  auth :50051  │   │ images :50052 │   │  PostgreSQL  │
              │  JWT, bcrypt  │   │ 4 шарда       │   │  techshop    │
              │  Google OAuth │   └───────┬───────┘   │  (app)       │
              └───────┬───────┘           │ SQL       └──────────────┘
                      │ SQL               │
                      ▼                   ▼
              ┌───────────────┐     ┌───────────────┐
              │  PostgreSQL   │     │  PostgreSQL   │
              │  grpc_auth    │     │  images       │
              └───────────────┘     └───────────────┘
```

**Взаимодействие сервисов:**
- `app` принимает HTTP-запросы, валидирует их и делегирует бизнес-логику.
- `app` общается с `auth` по gRPC для проверки JWT (`VerifyToken`).
- `app` общается с `images` по gRPC для загрузки/чтения изображений.
- Каждый сервис работает с отдельной базой PostgreSQL.

---

## Технологический стек

| Категория | Технологии |
|-----------|-----------|
| Язык | Go 1.25 |
| API | REST (net/http), gRPC, Protocol Buffers |
| Хранилище | PostgreSQL 16 |
| Библиотека | pgx/v5, pgxpool |
| Авторизация | JWT (golang-jwt/v5), bcrypt, Google OAuth 2.0 |
| DI | go.uber.org/fx |
| Документация | swaggo/swag, http-swagger |
| Контейнеризация | Docker, Docker Compose |
| CI/CD | GitHub Actions |

---

## Структура репозитория

```text
.
├── app/                  # REST API
│   ├── cmd/ApiFromSpec/  # точка входа, HTTP-сервер
│   ├── docs/             # сгенерированная Swagger-документация
│   ├── migrations/       # SQL-миграции (golang-migrate)
│   └── internal/
│       ├── application/  # сервисный слой (бизнес-логика)
│       ├── di/           # dependency injection (fx)
│       ├── domain/       # доменные модели и интерфейсы
│       ├── infrastructure/
│       │   ├── datasource/   # Repository/DAO-слой (PostgreSQL)
│       │   ├── middleware/   # JWT middleware
│       │   └── web/          # handlers, mapper, gRPC-клиенты, utils
│       └── pkg/          # общие структуры и ошибки
├── auth/                 # gRPC-сервис авторизации
│   ├── cmd/auth_grpc/
│   ├── migrations/
│   └── internal/
│       ├── application/  # JWT, UserService
│       ├── di/
│       ├── domain/
│       ├── infrastructure/
│       │   ├── datasource/  # PostgreSQL
│       │   └── oauth/       # Google OAuth 2.0
│       └── web/             # gRPC handler, DTO
├── images/               # gRPC-сервис изображений
│   ├── cmd/images_grpc/
│   ├── migrations/
│   └── internal/
│       ├── di/
│       ├── domain/
│       ├── infrastructure/datasource/  # шардирование по 4 БД
│       └── web/                        # gRPC handler
├── gen/                  # сгенерированные Protobuf-контракты
├── proto/                # исходные .proto файлы
│   ├── auth.proto
│   └── images.proto
├── pics/                 # тестовые изображения (base64)
├── .github/workflows/    # CI (GitHub Actions)
├── docker-compose.yml
└── cmd.md                # примеры запросов вручную
```

---

## Требования

- Go 1.25+
- Docker 24+ / Docker Desktop
- Docker Compose v2

Для локального запуска БД без Docker потребуется установленный PostgreSQL 16.

---

## Быстрый старт

```bash
# 1. Склонировать репозиторий
git clone git@github.com:Korzher/Learning_projects.git
cd "Backend - OAuth, Data-sharding"

# 2. Создать локальный .env из примера (опционально, для Google OAuth)
cp .env.example .env

# 3. Поднять всё окружение
docker compose up --build
```

После запуска:

| Сервис | Адрес |
|--------|-------|
| REST API | http://localhost:8080 |
| Swagger UI | http://localhost:8080/swagger/ |
| gRPC auth | localhost:50051 |
| gRPC images | localhost:50052 |
| PostgreSQL (app) | localhost:5432 |
| PostgreSQL (auth) | localhost:5433 |
| PostgreSQL (images) | localhost:5434 |

Остановка: `docker compose down` (с томами: `docker compose down -v`).

---

## Переменные окружения

Конфигурация выполняется через переменные окружения.

### Сервис `app`

| Переменная | По умолчанию | Назначение |
|-----------|--------------|-----------|
| `DB_HOST` | `localhost` | Адрес PostgreSQL (app) |
| `addr` | `localhost:50051` | Адрес gRPC-сервиса auth |
| `images_addr` | `localhost:50052` | Адрес gRPC-сервиса images |

### Сервис `auth`

| Переменная | По умолчанию | Назначение |
|------------|--------------|-----------|
| `DB_HOST` | `localhost` | Адрес PostgreSQL (auth) |
| `GOOGLE_CLIENT_ID` | — | Google OAuth Client ID |
| `GOOGLE_CLIENT_SECRET` | — | Google OAuth Client Secret |

### Сервис `images`

| Переменная | По умолчанию | Назначение |
|------------|--------------|-----------|
| `DB_HOST` | `localhost` | Адрес PostgreSQL (images, 4 шарда) |

Пример `.env.example`:

```env
GOOGLE_CLIENT_ID=
GOOGLE_CLIENT_SECRET=
```

---

## База данных

Три отдельные схемы, по одной на сервис (всего **7 таблиц**):

| Сервис | БД | Таблицы |
|--------|----|---------|
| `app` | `techshop` | `address_table`, `client_table`, `supplier_table`, `product_table` |
| `auth` | `grpc_auth` | `user_table`, `oauth_states` |
| `images` | `images_shard_0..3` | `images` (в каждом шарде) |

Особенности схемы `app`:

- UUID-идентификаторы во всех таблицах.
- Составной уникальный индекс `idx_unique_address` на
  `(country, city, street)` — предотвращает дублирование адресов.

Миграции выполняются автоматически при старте окружения (контейнеры
`migrate*` через [golang-migrate](https://github.com/golang-migrate/migrate)).

---

## API

Базовый путь: `/api/v1`. Swagger UI: `http://localhost:8080/swagger/`.

### Публичные эндпоинты (без JWT)

| Метод | Путь | Описание |
|-------|------|----------|
| POST | `/api/v1/register` | Регистрация |
| POST | `/api/v1/auth` | Вход |
| POST | `/api/v1/reset` | Сброс пароля |
| POST | `/api/v1/change` | Смена пароля |
| GET | `/api/v1/auth/google/login` | Начало Google OAuth |
| GET | `/api/v1/auth/google/callback` | Callback Google OAuth |

### Защищённые эндпоинты (заголовок `Authorization: Bearer <JWT>`)

**Клиенты**
| Метод | Путь | Описание |
|-------|------|----------|
| POST | `/api/v1/clients` | Создать клиента |
| GET | `/api/v1/clients` | Список с пагинацией |
| GET | `/api/v1/clients/search` | Поиск по имени/фамилии |
| PATCH | `/api/v1/clients/{id}/address` | Изменить адрес |
| DELETE | `/api/v1/clients/{id}` | Удалить |

**Товары**
| Метод | Путь | Описание |
|-------|------|----------|
| POST | `/api/v1/products` | Создать товар |
| GET | `/api/v1/products` | Все товары |
| GET | `/api/v1/products/{id}` | Товар по ID |
| PATCH | `/api/v1/products/{id}/subtract` | Списать сток |
| DELETE | `/api/v1/products/{id}` | Удалить |

**Поставщики**
| Метод | Путь | Описание |
|-------|------|----------|
| POST | `/api/v1/suppliers` | Создать поставщика |
| GET | `/api/v1/suppliers` | Все поставщики |
| GET | `/api/v1/suppliers/{id}` | По ID |
| PATCH | `/api/v1/suppliers/{id}/address` | Изменить адрес |
| DELETE | `/api/v1/suppliers/{id}` | Удалить |

**Изображения**
| Метод | Путь | Описание |
|-------|------|----------|
| POST | `/api/v1/image` | Загрузить изображение |
| GET | `/api/v1/image/{id}` | Получить по ID изображения |
| GET | `/api/v1/image/product/{id}` | Получить по ID товара |
| PUT | `/api/v1/image/{id}` | Обновить |
| DELETE | `/api/v1/image/{id}` | Удалить |

---

## Авторизация

- **Регистрация**: пароль хэшируется `bcrypt` (с солью) перед сохранением.
- **JWT**: выдаётся пара `access` (30 мин) и `refresh` (7 суток).
- **Валидация**: `api app` через gRPC вызывает `VerifyToken` сервиса `auth`.
- **Google OAuth 2.0**: логин через Google, защита от CSRF с помощью
  одноразового `state`.
- **Middleware** закрывает 20 эндпоинтов из 26.

```text
Client ──Authorization: Bearer JWT──▶ app (middleware)
                                          │
                                          ▼  gRPC VerifyToken
                                       auth (JWT parse + проверка exp)
                                          │ valid / invalid
                                          ▼
                                     app → handler
```

---

## Шардирование данных

Изображения распределяются по **4 базам** (`images_shard_0..3`).

Функция выбора шарда использует **первый hex-разряд UUID**:

```text
first char:  0-3 → shard 0
             4-7 → shard 1
             8-b → shard 2
             c-f → shard 3
```

---

## Обработка ошибок

- **9 категорий ошибок** объявлены в `app/internal/pkg/errors.go`.
- Корректные HTTP-статусы сопоставляются в обработчиках через `errors.Is`:
  - `400 Bad Request` — невалидный ввод
  - `401 Unauthorized` — отсутствует/недействителен JWT
  - `404 Not Found` — ресурс не найден
  - `409 Conflict` — дубликат записи
  - `500 Internal Server Error` — внутренние сбои
- Единый JSON-ответ через хелпер `RespondJSON`.

---

## Тестирование

Юнит-тесты на стандартной библиотеке (`testing`, table-driven).

```bash
# По каждому модулю
cd app && go test ./... -cover && cd ..
cd auth && go test ./... -cover && cd ..
cd images && go test ./... -cover
```
---

## CI/CD

GitHub Actions (`/.github/workflows/ci.yml`):

| Стадия | Действия |
|--------|----------|
| `test` | `go vet`, юнит-тесты с `-cover` для всех трёх модулей |
| `build` | Сборка Docker-образов `app`, `auth`, `images` |

Запускается на `push` в `main`/`master` и на `pull_request`.

---

## Graceful shutdown

Каждый сервис останавливается корректно:

- `app` — `http.Server.Shutdown` с таймаутом.
- `auth`, `images` — `gRPC GracefulStop`.

За это отвечает `go.uber.org/fx` lifecycle (хуки `OnStart`/`OnStop`).


---

Подробные примеры запросов — в [`cmd.md`](./cmd.md).

FROM golang:1.25.3-alpine

WORKDIR /src
COPY app/go.mod app/go.sum ./app/
COPY gen/go.mod gen/go.sum ./gen/

WORKDIR /src/app
RUN go mod download

WORKDIR /src
COPY app/ ./app/
COPY gen/ ./gen/

WORKDIR /src/app
RUN go build -o techshop ./cmd/ApiFromSpec

EXPOSE 8080
CMD ["./techshop"]
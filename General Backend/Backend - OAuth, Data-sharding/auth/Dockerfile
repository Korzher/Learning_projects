FROM golang:1.25.3-alpine

WORKDIR /src
COPY auth/go.mod auth/go.sum ./auth/
COPY gen/go.mod gen/go.sum ./gen/

WORKDIR /src/auth
RUN go mod download

WORKDIR /src
COPY auth/ ./auth/
COPY gen/ ./gen/

WORKDIR /src/auth
RUN go build -o auth ./cmd/auth_grpc

EXPOSE 50051
CMD ["./auth"]
FROM golang:1.25.3-alpine

WORKDIR /src
COPY images/go.mod images/go.sum ./images/
COPY gen/go.mod gen/go.sum ./gen/

WORKDIR /src/images
RUN go mod download

WORKDIR /src
COPY images/ ./images/
COPY gen/ ./gen/

WORKDIR /src/images
RUN go build -o images ./cmd/images_grpc

EXPOSE 50052
CMD ["./images"]
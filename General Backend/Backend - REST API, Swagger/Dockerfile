FROM golang:1.25.3-alpine

WORKDIR /app

COPY go.mod go.sum ./
RUN go mod download

COPY . .

RUN go build -o techshop ./cmd/ApiFromSpec

EXPOSE 8080

CMD ["./techshop"]
FROM golang:1.25.3-alpine

WORKDIR /app

COPY go.mod go.sum ./
RUN go mod download

COPY . .

RUN go build -o tic-tac-toe ./cmd/tic-tac-toe

EXPOSE 8080

CMD ["./tic-tac-toe"]
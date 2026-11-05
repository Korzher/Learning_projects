package main

import (
	"flag"
	"fmt"
	"os"
	"os/signal"
	"syscall"
	"time"
)

func main() {
	signalChannel := make(chan os.Signal, 1)
	done := make(chan struct{})
	signal.Notify(signalChannel, os.Interrupt, syscall.SIGTERM)
	K := parseFlags()
	go ticker(K, done)
	<-signalChannel
	close(done)
	fmt.Println("Termination")
}

func parseFlags() uint {
	var K uint

	flag.UintVar(&K, "K", 0, "Первое число (обязательно)")

	flag.Parse()

	if K == 0 {
		fmt.Println("Ошибка: необходимо указать положительное число больше ноля")
		fmt.Println("Использование: go run task3.go -K=<число>")
		os.Exit(1)
	}
	return K
}

func ticker(K uint, done <-chan struct{}) {
	i := 1
	left := time.Duration(K) * time.Second
	for {
		select {
		case <-done:
			return
		default:
			time.Sleep(100 * time.Millisecond)
			left = left - 100*time.Millisecond
			if left <= 0 {
				spentTime := i * int(K)
				fmt.Println("Tick", i, "since", spentTime)
				i++
				left = time.Duration(K) * time.Second
			}
		}
	}
}

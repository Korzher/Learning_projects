package main

import (
	"APG-P01/internal/presentation"
	"log"
	"math/rand"

	"time"
)

func main() {
	ui, err := presentation.NewTerminalUI()
	if err != nil {
		log.Fatal("Failed to initialize UI:", err)
	}
	defer ui.Close()
	rng := rand.New(rand.NewSource(time.Now().UnixNano()))

	for {
		if !presentation.GameLoop(ui, rng) {
			break
		}
	}
}

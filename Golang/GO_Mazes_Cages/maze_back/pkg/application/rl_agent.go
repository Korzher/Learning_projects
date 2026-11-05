package application

import (
	"math"
	"math/rand"
)

const (
	RLUp = iota
	RLRight
	RLDown
	RLLeft
)

// добавил статистику
type RLStats struct {
	Episodes     int
	SuccessCount int
	AvgSteps     float64
}

type RLAgent struct {
	Q       map[[3]int]float64
	Alpha   float64
	Gamma   float64
	Epsilon float64
	Stats   RLStats
}

func NewRLAgent() *RLAgent {
	return &RLAgent{
		Q:       make(map[[3]int]float64),
		Alpha:   0.1,
		Gamma:   0.9,
		Epsilon: 0.2,
	}
}

func (a *RLAgent) chooseAction(x, y int) int {
	if rand.Float64() < a.Epsilon {
		return rand.Intn(4)
	}

	best := 0
	bestVal := math.Inf(-1)
	for i := 0; i < 4; i++ {
		v := a.Q[[3]int{x, y, i}]
		if v > bestVal {
			bestVal = v
			best = i
		}
	}
	return best
}

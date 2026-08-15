package application

import "math/rand"

func rlStep(maze *Maze, x, y, action int, endX, endY int) (nx, ny, reward int, done bool) {
	nx, ny = x, y

	var dir Point

	switch action {
	case RLUp:
		dir = Point{0, -1}
	case RLRight:
		dir = Point{1, 0}
	case RLDown:
		dir = Point{0, 1}
	case RLLeft:
		dir = Point{-1, 0}
	}

	if !isValidPoint(maze, x+dir.X, y+dir.Y) || !canMove(maze, x, y, dir) {
		return x, y, -100, false
	}

	nx += dir.X
	ny += dir.Y

	if nx == endX && ny == endY {
		return nx, ny, 100, true
	}

	return nx, ny, -1, false
}

func TrainAgent(agent *RLAgent, maze *Maze, endX, endY int, episodes int) {
	totalSteps := 0
	success := 0

	for e := 0; e < episodes; e++ {
		x := rand.Intn(maze.Width)
		y := rand.Intn(maze.Height)

		steps := 0
		for steps < 1000 {
			steps++

			a := agent.chooseAction(x, y)
			nx, ny, r, done := rlStep(maze, x, y, a, endX, endY)

			old := agent.Q[[3]int{x, y, a}]

			maxNext := -1e9
			for i := 0; i < 4; i++ {
				v := agent.Q[[3]int{nx, ny, i}]
				if v > maxNext {
					maxNext = v
				}
			}

			agent.Q[[3]int{x, y, a}] =
				old + agent.Alpha*(float64(r)+agent.Gamma*maxNext-old)

			x, y = nx, ny

			if done {
				success++
				break
			}
		}

		totalSteps += steps
	}

	agent.Stats = RLStats{
		Episodes:     episodes,
		SuccessCount: success,
		AvgSteps:     float64(totalSteps) / float64(episodes),
	}
}

/*func TrainAgent(agent *RLAgent, maze *Maze, endX, endY int, episodes int) {
	for e := 0; e < episodes; e++ {

		x := rand.Intn(maze.Width)
		y := rand.Intn(maze.Height)

		for step := 0; step < 1000; step++ {
			a := agent.chooseAction(x, y)

			nx, ny, r, done := rlStep(maze, x, y, a, endX, endY)

			old := agent.Q[[3]int{x, y, a}]

			maxNext := -1e9
			for i := 0; i < 4; i++ {
				v := agent.Q[[3]int{nx, ny, i}]
				if v > maxNext {
					maxNext = v
				}
			}

			agent.Q[[3]int{x, y, a}] =
				old + agent.Alpha*(float64(r)+agent.Gamma*maxNext-old)

			x, y = nx, ny

			if done {
				break
			}
		}
	}
}*/

package application

func BuildRLPath(agent *RLAgent, maze *Maze, startX, startY, endX, endY int) [][2]int {
	path := [][2]int{{startX, startY}}
	x, y := startX, startY

	for i := 0; i < 1000; i++ {
		if x == endX && y == endY {
			break
		}

		a := agent.chooseAction(x, y)
		nx, ny, _, _ := rlStep(maze, x, y, a, endX, endY)

		x, y = nx, ny
		path = append(path, [2]int{x, y})
	}

	return path
}

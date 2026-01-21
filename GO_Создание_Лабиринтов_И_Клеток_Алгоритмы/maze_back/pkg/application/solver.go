package application

import (
	"container/list"
)

type Point struct {
	X, Y int
}

// SolveMaze находит путь от start до end в лабиринте (BFS)
func SolveMaze(maze *Maze, startX, startY, endX, endY int) [][2]int {
	if maze == nil || !isValidPoint(maze, startX, startY) || !isValidPoint(maze, endX, endY) {
		return nil
	}

	// BFS
	visited := make([][]bool, maze.Height)
	parent := make([][]Point, maze.Height)
	for i := range visited {
		visited[i] = make([]bool, maze.Width)
		parent[i] = make([]Point, maze.Width)
		for j := range parent[i] {
			parent[i][j] = Point{-1, -1}
		}
	}

	queue := list.New()
	queue.PushBack(Point{startX, startY})
	visited[startY][startX] = true

	directions := []Point{{0, -1}, {1, 0}, {0, 1}, {-1, 0}} // Вверх, вправо, вниз, влево

	for queue.Len() > 0 {
		current := queue.Remove(queue.Front()).(Point)

		// Достигли конца
		if current.X == endX && current.Y == endY {
			return reconstructPath(parent, startX, startY, endX, endY)
		}

		// Проверяем всех соседей
		for _, dir := range directions {
			nx, ny := current.X+dir.X, current.Y+dir.Y

			if isValidPoint(maze, nx, ny) && !visited[ny][nx] && canMove(maze, current.X, current.Y, dir) {
				visited[ny][nx] = true
				parent[ny][nx] = current
				queue.PushBack(Point{nx, ny})
			}
		}
	}

	return nil // Путь не найден
}

func isValidPoint(maze *Maze, x, y int) bool {
	return x >= 0 && x < maze.Width && y >= 0 && y < maze.Height
}

// canMove проверяет, можно ли пройти из (x,y) в направлении dir
func canMove(maze *Maze, x, y int, dir Point) bool {
	cell := maze.Cells[y][x]

	switch {
	case dir.X == -1 && dir.Y == 0: // Влево
		return !cell.Left
	case dir.X == 1 && dir.Y == 0: // Вправо
		return !cell.Right
	case dir.X == 0 && dir.Y == -1: // Вверх
		return !cell.Top
	case dir.X == 0 && dir.Y == 1: // Вниз
		return !cell.Bottom
	}
	return false
}

func reconstructPath(parent [][]Point, startX, startY, endX, endY int) [][2]int {
	path := [][2]int{}

	// Идём от конца к началу
	for x, y := endX, endY; !(x == startX && y == startY); {
		path = append([][2]int{{x, y}}, path...)
		prev := parent[y][x]
		x, y = prev.X, prev.Y
	}

	// Добавляем стартовую точку
	path = append([][2]int{{startX, startY}}, path...)
	return path
}

// интеграция с RL-агентом
func SolveMazeWithRL(maze *Maze, startX, startY, endX, endY int) [][2]int {
	agent := NewRLAgent()
	TrainAgent(agent, maze, endX, endY, 5000)
	return BuildRLPath(agent, maze, startX, startY, endX, endY)
}

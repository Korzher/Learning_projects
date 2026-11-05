package application

import (
	"fmt"
)

func IsPerfect(maze *Maze) bool {
	return allAchiveable(maze) && noCicles(maze)
}

func allAchiveable(maze *Maze) bool {
	if maze == nil {
		return false
	}

	visited := make([][]bool, maze.Height)
	for i := range visited {
		visited[i] = make([]bool, maze.Width)
	}

	totalCells := maze.Height * maze.Width
	visitedCount := 0

	var dfs func(x, y int)

	dfs = func(x, y int) {
		if visited[y][x] {
			return
		}
		visited[y][x] = true
		visitedCount++

		if !maze.Cells[y][x].Top && y > 0 {
			dfs(x, y-1)
		}
		if !maze.Cells[y][x].Right && x < maze.Width-1 {
			dfs(x+1, y)
		}
		if !maze.Cells[y][x].Bottom && y < maze.Height-1 {
			dfs(x, y+1)
		}
		if !maze.Cells[y][x].Left && x > 0 {
			dfs(x-1, y)
		}
	}

	dfs(0, 0)

	return visitedCount == totalCells
}

func Validate(m *Maze) error {
	if m == nil {
		return fmt.Errorf("maze is nil")
	}

	// Проверка размеров
	if m.Width < 1 || m.Height < 1 {
		return fmt.Errorf("maze dimensions must be positive")
	}

	if m.Width > 50 || m.Height > 50 {
		return fmt.Errorf("maze too large: max 50x50, got %dx%d", m.Width, m.Height)
	}

	for y := 0; y < m.Height; y++ {
		for x := 0; x < m.Width; x++ {
			cell := m.Cells[y][x]

			if x < m.Width-1 {
				rightCell := m.Cells[y][x+1]
				if cell.Right != rightCell.Left {
					return fmt.Errorf("wall mismatch at (%d,%d)-(%d,%d)", y, x, y, x+1)
				}
			} else {
				if !cell.Right {
					return fmt.Errorf("missing right border at (%d,%d)", y, x)
				}
			}

			if y < m.Height-1 {
				bottomCell := m.Cells[y+1][x]
				if cell.Bottom != bottomCell.Top {
					return fmt.Errorf("wall mismatch at (%d,%d)-(%d,%d)", y, x, y+1, x)
				}
			} else {
				if !cell.Bottom {
					return fmt.Errorf("missing bottom border at (%d,%d)", y, x)
				}
			}

			if x == 0 && !cell.Left {
				return fmt.Errorf("missing left border at (%d,%d)", y, x)
			}

			if y == 0 && !cell.Top {
				return fmt.Errorf("missing top border at (%d,%d)", y, x)
			}
		}
	}

	return nil
}

func noCicles(m *Maze) bool {
	if err := Validate(m); err != nil {
		return false
	}

	passages := 0
	for y := 0; y < m.Height; y++ {
		for x := 0; x < m.Width; x++ {
			cell := m.Cells[y][x]

			if x < m.Width-1 && !cell.Right {
				passages++
			}

			if y < m.Height-1 && !cell.Bottom {
				passages++
			}
		}
	}

	totalCells := m.Height * m.Width
	return passages == totalCells-1
}

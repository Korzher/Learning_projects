package application

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func writeSize(file *os.File, height, width int) error {
	_, err := fmt.Fprintf(file, "%d %d\n", height, width)
	return err
}

func writeWalls(file *os.File, m *Maze, wallExtractor func(Cell) int) error {
	for i := 0; i < m.Height; i++ {
		for j := 0; j < m.Width; j++ {
			if j > 0 {
				fmt.Fprint(file, " ")
			}
			fmt.Fprint(file, wallExtractor(m.Cells[i][j]))
		}
		fmt.Fprintln(file)
	}
	return nil
}

func readSize(scanner *bufio.Scanner) (int, int, error) {
	var line string
	for scanner.Scan() {
		line = strings.TrimSpace(scanner.Text())
		if line != "" {
			break
		}
	}

	parts := strings.Fields(line)
	if len(parts) != 2 {
		return 0, 0, fmt.Errorf("expected 'height width', got: %s", line)
	}

	height, err := strconv.Atoi(parts[0])
	if err != nil {
		return 0, 0, fmt.Errorf("invalid height: %v", err)
	}

	width, err := strconv.Atoi(parts[1])
	if err != nil {
		return 0, 0, fmt.Errorf("invalid width: %v", err)
	}

	if width < 1 || width > 50 || height < 1 || height > 50 {
		return 0, 0, fmt.Errorf("size must be 1-50, got %dx%d", height, width)
	}

	return height, width, nil
}

func readWalls(scanner *bufio.Scanner, maze *Maze, wallSetter func(*Cell, int)) error {
	for i := 0; i < maze.Height; i++ {
		var line string
		for scanner.Scan() {
			line = strings.TrimSpace(scanner.Text())
			if line != "" {
				break
			}
		}

		parts := strings.Fields(line)
		if len(parts) != maze.Width {
			return fmt.Errorf("line %d: expected %d values, got %d", i+1, maze.Width, len(parts))
		}

		for j, part := range parts {
			value, err := strconv.Atoi(part)
			if err != nil || (value != 0 && value != 1) {
				return fmt.Errorf("invalid wall value at (%d,%d): %s", i, j, part)
			}
			wallSetter(&maze.Cells[i][j], value)
		}
	}
	return nil
}

func fixWallsConsistency(maze *Maze) {
	for i := 0; i < maze.Height; i++ {
		for j := 0; j < maze.Width; j++ {
			if j+1 < maze.Width {
				maze.Cells[i][j+1].Left = maze.Cells[i][j].Right
			}
			if i+1 < maze.Height {
				maze.Cells[i+1][j].Top = maze.Cells[i][j].Bottom
			}
		}
	}
}

func setOuterBorders(maze *Maze) {
	for i := 0; i < maze.Height; i++ {
		maze.Cells[i][0].Left = true
		maze.Cells[i][maze.Width-1].Right = true
	}
	for j := 0; j < maze.Width; j++ {
		maze.Cells[0][j].Top = true
		maze.Cells[maze.Height-1][j].Bottom = true
	}
}

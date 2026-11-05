package application

import (
	"fmt"
	"os"
	"strings"
)

func SaveToFile(m *Maze, filename string) error {
	if m == nil {
		return fmt.Errorf("maze is nil")
	}

	if !strings.HasSuffix(filename, ".txt") {
		filename += ".txt"
	}

	file, err := os.Create(filename)
	if err != nil {
		return fmt.Errorf("cannot create file: %v", err)
	}
	defer file.Close()

	if err := writeSize(file, m.Height, m.Width); err != nil {
		return err
	}

	if err := writeWalls(file, m, func(cell Cell) int {
		if cell.Right {
			return 1
		}
		return 0
	}); err != nil {
		return err
	}

	fmt.Fprintln(file)

	if err := writeWalls(file, m, func(cell Cell) int {
		if cell.Bottom {
			return 1
		}
		return 0
	}); err != nil {
		return err
	}

	return nil
}

package application

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func LoadFromFile(filename string) (*Maze, error) {
	if !strings.HasSuffix(filename, ".txt") {
		return nil, fmt.Errorf("file must have .txt format")
	}

	file, err := os.Open(filename)
	if err != nil {
		return nil, fmt.Errorf("cannot open file")
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	height, width, err := readSize(scanner)
	if err != nil {
		return nil, err
	}

	maze := NewMaze(width, height, false)
	if maze == nil {
		return nil, fmt.Errorf("failed to create maze")
	}

	if err := readWalls(scanner, maze, func(cell *Cell, value int) {
		cell.Right = (value == 1)
	}); err != nil {
		return nil, err
	}

	if err := readWalls(scanner, maze, func(cell *Cell, value int) {
		cell.Bottom = (value == 1)
	}); err != nil {
		return nil, err
	}

	fixWallsConsistency(maze)
	setOuterBorders(maze)

	return maze, nil
}

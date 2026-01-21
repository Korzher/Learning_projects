package application

import (
	"math/rand"
	"time"
)

type Generator struct {
	width  int
	height int
	rand   *rand.Rand
}

func NewGenerator(width, height int) *Generator {
	source := rand.NewSource(time.Now().UnixNano())
	return &Generator{
		width:  width,
		height: height,
		rand:   rand.New(source),
	}
}

func (g *Generator) Generate() *Maze {
	maze := NewMaze(g.width, g.height, true)
	if maze == nil {
		return nil
	}

	sets := make([]int, g.width)
	setCounter := 1
	for i := range sets {
		sets[i] = setCounter
		setCounter++
	}

	for row := 0; row < g.height; row++ {
		for col := 0; col < g.width-1; col++ {
			if sets[col] != sets[col+1] {
				if g.rand.Float32() < 0.5 || row == g.height-1 {
					maze.Cells[row][col].Right = false
					maze.Cells[row][col+1].Left = false

					oldSet := sets[col+1]
					newSet := sets[col]
					for i := 0; i < g.width; i++ {
						if sets[i] == oldSet {
							sets[i] = newSet
						}
					}
				}
			}
		}

		if row < g.height-1 {
			setHasVertical := make(map[int]bool)

			for col := 0; col < g.width; col++ {
				setHasVertical[sets[col]] = false
			}

			for col := 0; col < g.width; col++ {
				currentSet := sets[col]
				createDown := false
				if !setHasVertical[currentSet] {
					createDown = true
					setHasVertical[currentSet] = true
				} else if g.rand.Float32() < 0.3 {
					createDown = true
				}

				if createDown {
					maze.Cells[row][col].Bottom = false
					maze.Cells[row+1][col].Top = false
				}
			}

			for col := 0; col < g.width; col++ {
				if maze.Cells[row][col].Bottom {
					sets[col] = setCounter
					setCounter++
				}
			}
		}
	}

	for i := 0; i < g.height; i++ {
		maze.Cells[i][0].Left = true
		maze.Cells[i][g.width-1].Right = true
	}

	for j := 0; j < g.width; j++ {
		maze.Cells[0][j].Top = true
		maze.Cells[g.height-1][j].Bottom = true
	}

	return maze
}

func GenerateEller(width, height int) *Maze {
	if width < 1 || height < 1 || width > 50 || height > 50 {
		return nil
	}
	generator := NewGenerator(width, height)
	return generator.Generate()
}

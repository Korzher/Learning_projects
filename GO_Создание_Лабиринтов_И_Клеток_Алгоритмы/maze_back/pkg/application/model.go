package application

type Cell struct {
	Top    bool
	Right  bool
	Bottom bool
	Left   bool
}

// Струтура лабиринта
type Maze struct {
	Width  int
	Height int
	Cells  [][]Cell
}

func NewMaze(width, height int, walls bool) *Maze {
	if width <= 0 || height <= 0 {
		return nil
	}

	m := &Maze{
		Width:  width,
		Height: height,
		Cells:  make([][]Cell, height),
	}

	for i := range m.Cells {
		m.Cells[i] = make([]Cell, width)

		for j := range m.Cells[i] {
			m.Cells[i][j] = Cell{
				Top:    walls,
				Right:  walls,
				Bottom: walls,
				Left:   walls,
			}
		}
	}
	return m
}

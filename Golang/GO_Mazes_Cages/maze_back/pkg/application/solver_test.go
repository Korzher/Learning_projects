package application

import "testing"

func TestSolveMaze(t *testing.T) {
	m := GenerateEller(5, 5)
	path := SolveMaze(m, 0, 0, 4, 4)

	if len(path) == 0 {
		t.Fatal("no path found")
	}
}

func TestReconstructPath(t *testing.T) {
	parent := [][]Point{
		{{-1, -1}, {0, 0}},
	}
	path := reconstructPath(parent, 0, 0, 1, 0)
	if len(path) == 0 {
		t.Fatal("path empty")
	}
}

func TestSolveMazeWithRL(t *testing.T) {
	m := GenerateEller(5, 5)

	path := SolveMazeWithRL(m, 0, 0, 4, 4)

	if len(path) == 0 {
		t.Fatal("RL solver returned empty path")
	}

	last := path[len(path)-1]
	if last[0] != 4 || last[1] != 4 {
		t.Fatal("RL solver did not reach exit")
	}
}

func TestSolveMazeNil(t *testing.T) {
	path := SolveMaze(nil, 0, 0, 1, 1)
	if path != nil {
		t.Fatal("expected nil path for nil maze")
	}
}

func TestSolveMazeInvalidCoords(t *testing.T) {
	m := GenerateEller(3, 3)

	path := SolveMaze(m, -1, 0, 2, 2)
	if path != nil {
		t.Fatal("expected nil path for invalid start")
	}
}

func TestSolveMazeNoPath(t *testing.T) {
	m := NewMaze(2, 2, true) // полностью закрытый

	path := SolveMaze(m, 0, 0, 1, 1)

	if path != nil {
		t.Fatal("path should not exist")
	}
}

func TestCanMoveDirections(t *testing.T) {
	m := NewMaze(1, 1, false)
	c := &m.Cells[0][0]

	c.Left = false
	if !canMove(m, 0, 0, Point{-1, 0}) {
		t.Fatal("left")
	}

	c.Right = false
	if !canMove(m, 0, 0, Point{1, 0}) {
		t.Fatal("right")
	}

	c.Top = false
	if !canMove(m, 0, 0, Point{0, -1}) {
		t.Fatal("top")
	}

	c.Bottom = false
	if !canMove(m, 0, 0, Point{0, 1}) {
		t.Fatal("bottom")
	}
}

func TestCanMoveDefault(t *testing.T) {
	m := NewMaze(1, 1, false)

	if canMove(m, 0, 0, Point{5, 5}) {
		t.Fatal("invalid direction should be false")
	}
}

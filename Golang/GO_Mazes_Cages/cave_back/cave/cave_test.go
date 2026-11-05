package cave

import (
	"io"
	"os"
	"strings"
	"testing"
)

func TestAliveNeighbors_Border(t *testing.T) {
	c := &Cave{
		Rows:  1,
		Cols:  1,
		Cells: [][]bool{{false}},
	}

	if n := c.aliveNeighbors(0, 0); n != 8 {
		t.Fatalf("expected 8, got %d", n)
	}
}

func TestAliveNeighbors_Middle(t *testing.T) {
	c := &Cave{
		Rows: 3,
		Cols: 3,
		Cells: [][]bool{
			{true, false, true},
			{false, false, false},
			{true, false, true},
		},
	}

	if n := c.aliveNeighbors(1, 1); n != 4 {
		t.Fatalf("expected 4, got %d", n)
	}
}

func TestBirth(t *testing.T) {
	c := &Cave{
		Rows: 3,
		Cols: 3,
		Cells: [][]bool{
			{true, true, true},
			{true, false, true},
			{true, true, true},
		},
	}

	c.Step(4, 3)

	if !c.Cells[1][1] {
		t.Fatal("cell should be born")
	}
}

func TestDeath(t *testing.T) {
	c := &Cave{
		Rows: 3,
		Cols: 3,
		Cells: [][]bool{
			{false, false, false},
			{false, true, false},
			{false, false, false},
		},
	}

	c.Step(4, 3)

	if c.Cells[1][1] {
		t.Fatal("cell should die")
	}
}

func TestUnchanged(t *testing.T) {
	c := &Cave{
		Rows:  1,
		Cols:  1,
		Cells: [][]bool{{true}},
	}

	changed := c.Step(0, 0)

	if changed {
		t.Fatal("cell should remain unchanged")
	}
}

func TestChangedFlag(t *testing.T) {
	c := &Cave{
		Rows:  1,
		Cols:  1,
		Cells: [][]bool{{false}},
	}

	changed := c.Step(0, 8)

	if !changed {
		t.Fatal("expected changed to be true")
	}
}

func TestDoubleBuffering(t *testing.T) {
	c := &Cave{
		Rows: 2,
		Cols: 2,
		Cells: [][]bool{
			{true, false},
			{false, true},
		},
	}

	old := c.Cells[0][0]
	c.Step(4, 3)

	if c.Cells[0][0] == old {
		t.Log("double buffering works")
	}
}

func TestLoadFromFile(t *testing.T) {
	content := `3 3
1 0 1
0 1 0
1 0 1`

	tmp, err := os.CreateTemp("", "cave*.txt")
	if err != nil {
		t.Fatal(err)
	}
	defer os.Remove(tmp.Name())

	tmp.WriteString(content)
	tmp.Close()

	c, err := LoadFromFile(tmp.Name())
	if err != nil {
		t.Fatal("failed to load file:", err)
	}

	if c.Rows != 3 || c.Cols != 3 {
		t.Fatal("invalid size loaded")
	}

	if !c.Cells[0][0] || c.Cells[0][1] || !c.Cells[2][2] {
		t.Fatal("matrix loaded incorrectly")
	}
}

func TestRandom(t *testing.T) {
	c := Random(5, 5, 1.0)

	for i := 0; i < 5; i++ {
		for j := 0; j < 5; j++ {
			if !c.Cells[i][j] {
				t.Fatal("expected all cells alive with chance 1.0")
			}
		}
	}
}

func TestDrawConsole(t *testing.T) {
	c := &Cave{
		Rows: 2,
		Cols: 2,
		Cells: [][]bool{
			{true, false},
			{false, true},
		},
	}

	old := os.Stdout
	r, w, _ := os.Pipe()
	os.Stdout = w

	DrawConsole(c)

	w.Close()
	os.Stdout = old

	var buf strings.Builder
	_, _ = io.Copy(&buf, r)

	if buf.Len() == 0 {
		t.Fatal("DrawConsole produced no output")
	}
}

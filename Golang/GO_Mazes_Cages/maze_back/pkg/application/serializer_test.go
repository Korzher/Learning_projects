package application

import (
	"bufio"
	"strings"
	"testing"
)

func TestFixWallsConsistency(t *testing.T) {
	m := NewMaze(2, 2, false)
	m.Cells[0][0].Right = true

	fixWallsConsistency(m)

	if !m.Cells[0][1].Left {
		t.Fatal("wall not synchronized")
	}
}

func TestReadSizeEmpty(t *testing.T) {
	sc := bufio.NewScanner(strings.NewReader(""))
	_, _, err := readSize(sc)
	if err == nil {
		t.Fatal("expected error on empty input")
	}
}

func TestReadSizeInvalid(t *testing.T) {
	sc := bufio.NewScanner(strings.NewReader("abc def"))
	_, _, err := readSize(sc)
	if err == nil {
		t.Fatal("expected error on invalid format")
	}
}

func TestReadSizeSecondInvalid(t *testing.T) {
	sc := bufio.NewScanner(strings.NewReader("5 x"))
	_, _, err := readSize(sc)
	if err == nil {
		t.Fatal("expected error on invalid second number")
	}
}

func TestReadSizeOneNumber(t *testing.T) {
	sc := bufio.NewScanner(strings.NewReader("5"))
	_, _, err := readSize(sc)
	if err == nil {
		t.Fatal("expected error on single number")
	}
}

func TestReadSizeNegative(t *testing.T) {
	sc := bufio.NewScanner(strings.NewReader("-3 5"))
	_, _, err := readSize(sc)
	if err == nil {
		t.Fatal("expected error on negative size")
	}
}

func TestReadSizeZero(t *testing.T) {
	sc := bufio.NewScanner(strings.NewReader("0 5"))
	_, _, err := readSize(sc)
	if err == nil {
		t.Fatal("expected error on zero size")
	}
}

func TestReadWallsShort(t *testing.T) {
	m := NewMaze(2, 2, false)
	sc := bufio.NewScanner(strings.NewReader("1 0"))

	err := readWalls(sc, m, func(c *Cell, v int) {})
	if err == nil {
		t.Fatal("expected error on short walls")
	}
}

func TestReadWallsInvalidValue(t *testing.T) {
	m := NewMaze(2, 2, false)
	sc := bufio.NewScanner(strings.NewReader("a b\n1 0"))

	err := readWalls(sc, m, func(c *Cell, v int) {})
	if err == nil {
		t.Fatal("expected error on invalid wall value")
	}
}

func TestReadWallsShortLine(t *testing.T) {
	m := NewMaze(2, 2, false)
	sc := bufio.NewScanner(strings.NewReader("1\n1 0"))

	err := readWalls(sc, m, func(c *Cell, v int) {})
	if err == nil {
		t.Fatal("expected error on short line")
	}
}

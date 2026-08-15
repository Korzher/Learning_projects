package cave

const MaxSize = 50

type Cave struct {
	Rows  int
	Cols  int
	Cells [][]bool // true = живая (стена)
}

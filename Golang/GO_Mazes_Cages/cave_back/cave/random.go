package cave

import "math/rand"

func Random(rows, cols int, chance float64) *Cave {
	cells := make([][]bool, rows)
	for i := 0; i < rows; i++ {
		cells[i] = make([]bool, cols)
		for j := 0; j < cols; j++ {
			cells[i][j] = rand.Float64() < chance
		}
	}
	return &Cave{Rows: rows, Cols: cols, Cells: cells}
}

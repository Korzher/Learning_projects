package cave

func (c *Cave) aliveNeighbors(r, c0 int) int {
	dirs := [8][2]int{
		{-1, -1}, {-1, 0}, {-1, 1},
		{0, -1}, {0, 1},
		{1, -1}, {1, 0}, {1, 1},
	}

	count := 0
	for _, d := range dirs {
		nr, nc := r+d[0], c0+d[1]

		if nr < 0 || nr >= c.Rows || nc < 0 || nc >= c.Cols {
			count++ // границы считаются живыми
		} else if c.Cells[nr][nc] {
			count++
		}
	}
	return count
}

func (c *Cave) Step(birthLimit, deathLimit int) bool {
	next := make([][]bool, c.Rows)
	changed := false

	for i := 0; i < c.Rows; i++ {
		next[i] = make([]bool, c.Cols)
		for j := 0; j < c.Cols; j++ {
			n := c.aliveNeighbors(i, j)

			if c.Cells[i][j] {
				next[i][j] = n >= deathLimit
			} else {
				next[i][j] = n > birthLimit
			}

			if next[i][j] != c.Cells[i][j] {
				changed = true
			}
		}
	}

	c.Cells = next
	return changed
}

package cave

import "fmt"

func DrawConsole(c *Cave) {
	fmt.Println()

	for i := 0; i < c.Rows; i++ {
		for j := 0; j < c.Cols; j++ {
			if c.Cells[i][j] {
				fmt.Print("#")
			} else {
				fmt.Print(".")
			}
		}
		fmt.Println()
	}
	fmt.Println()
}

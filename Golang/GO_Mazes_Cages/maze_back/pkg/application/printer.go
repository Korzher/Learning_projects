package application

import (
	"fmt"
)

func PrintSimple(m *Maze) {
	if m == nil {
		fmt.Println("Maze is nil!")
		return
	}

	fmt.Print("+")
	for x := 0; x < m.Width; x++ {
		if m.Cells[0][x].Top {
			fmt.Print("---+")
		} else {
			fmt.Print("   +")
		}
	}
	fmt.Println()

	for y := 0; y < m.Height; y++ {
		if m.Cells[y][0].Left {
			fmt.Print("|")
		} else {
			fmt.Print(" ")
		}

		for x := 0; x < m.Width; x++ {
			fmt.Print("   ")

			if x == m.Width-1 {
				if m.Cells[y][x].Right {
					fmt.Print("|")
				} else {
					fmt.Print(" ")
				}
			} else {
				if m.Cells[y][x].Right {
					fmt.Print("|")
				} else {
					fmt.Print(" ")
				}
			}
		}
		fmt.Println()

		if y < m.Height-1 {
			fmt.Print("+")
			for x := 0; x < m.Width; x++ {
				if m.Cells[y][x].Bottom {
					fmt.Print("---+")
				} else {
					fmt.Print("   +")
				}
			}
			fmt.Println()
		}
	}

	fmt.Print("+")
	for x := 0; x < m.Width; x++ {
		if m.Cells[m.Height-1][x].Bottom {
			fmt.Print("---+")
		} else {
			fmt.Print("   +")
		}
	}
}

// RL-агент
func PrintWithPath(m *Maze, path [][2]int, startX, startY, endX, endY int) {
	pathMap := make(map[[2]int]bool)
	for _, p := range path {
		pathMap[[2]int{p[0], p[1]}] = true
	}

	fmt.Print("+")
	for x := 0; x < m.Width; x++ {
		if m.Cells[0][x].Top {
			fmt.Print("---+")
		} else {
			fmt.Print("   +")
		}
	}
	fmt.Println()

	for y := 0; y < m.Height; y++ {
		if m.Cells[y][0].Left {
			fmt.Print("|")
		} else {
			fmt.Print(" ")
		}

		for x := 0; x < m.Width; x++ {
			ch := "   "

			if x == startX && y == startY {
				ch = " S "
			} else if x == endX && y == endY {
				ch = " E "
			} else if pathMap[[2]int{x, y}] {
				ch = " * "
			}

			fmt.Print(ch)

			if m.Cells[y][x].Right {
				fmt.Print("|")
			} else {
				fmt.Print(" ")
			}
		}
		fmt.Println()

		if y < m.Height-1 {
			fmt.Print("+")
			for x := 0; x < m.Width; x++ {
				if m.Cells[y][x].Bottom {
					fmt.Print("---+")
				} else {
					fmt.Print("   +")
				}
			}
			fmt.Println()
		}
	}

	fmt.Print("+")
	for x := 0; x < m.Width; x++ {
		if m.Cells[m.Height-1][x].Bottom {
			fmt.Print("---+")
		} else {
			fmt.Print("   +")
		}
	}
	fmt.Println()
}

// статистика
func PrintRLStats(agent *RLAgent) {
	fmt.Println("\nRL Training statistics:")
	fmt.Printf("Episodes: %d\n", agent.Stats.Episodes)
	fmt.Printf("Success rate: %.2f%%\n",
		float64(agent.Stats.SuccessCount)*100/float64(agent.Stats.Episodes))
	fmt.Printf("Average steps: %.2f\n", agent.Stats.AvgSteps)
}

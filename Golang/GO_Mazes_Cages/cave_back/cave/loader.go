package cave

import (
	"bufio"
	"errors"
	"fmt"
	"os"
)

func LoadFromFile(filename string) (*Cave, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	in := bufio.NewReader(file)

	var rows, cols int
	if _, err := fmt.Fscan(in, &rows, &cols); err != nil {
		return nil, errors.New("неверный формат файла")
	}

	if rows < 1 || rows > MaxSize || cols < 1 || cols > MaxSize {
		return nil, errors.New("размер пещеры превышает 50x50")
	}

	cells := make([][]bool, rows)
	for i := 0; i < rows; i++ {
		cells[i] = make([]bool, cols)
		for j := 0; j < cols; j++ {
			var v int
			if _, err := fmt.Fscan(in, &v); err != nil {
				return nil, err
			}
			cells[i][j] = v == 1
		}
	}

	return &Cave{Rows: rows, Cols: cols, Cells: cells}, nil
}

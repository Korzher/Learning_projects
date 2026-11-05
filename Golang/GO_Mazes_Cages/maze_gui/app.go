package main

import (
	"cave/cave"
	"context"
	"encoding/json"
	"fmt"
	"maze/pkg/application"
	"strings"
)

type App struct {
	ctx context.Context
}

func NewApp() *App {
	return &App{}
}

func (a *App) startup(ctx context.Context) {
	a.ctx = ctx
}

func (a *App) Generate(width, height int) string {
	if width < 1 || height < 1 || width > 50 || height > 50 {
		return "Ошибка: размеры 1-50"
	}

	maze := application.GenerateEller(width, height)
	if maze == nil {
		return "Ошибка генерации"
	}

	data := map[string]interface{}{
		"width":   maze.Width,
		"height":  maze.Height,
		"cells":   maze.Cells,
		"message": fmt.Sprintf("Лабиринт %dx%d создан", width, height),
	}

	jsonData, _ := json.Marshal(data)
	return string(jsonData)
}

func (a *App) SaveMaze(jsonStr string, filename string) string {
	var data struct {
		Width  int                  `json:"width"`
		Height int                  `json:"height"`
		Cells  [][]application.Cell `json:"cells"`
	}

	json.Unmarshal([]byte(jsonStr), &data)

	maze := &application.Maze{
		Width:  data.Width,
		Height: data.Height,
		Cells:  data.Cells,
	}

	path := "../../maze_back/pkg/datasource/" + filename
	err := application.SaveToFile(maze, path)
	if err != nil {
		return "Ошибка: " + err.Error()
	}
	return "Сохранено в " + filename
}

func (a *App) LoadMaze(filename string) string {
	path := "../../maze_back/pkg/datasource/" + filename
	maze, err := application.LoadFromFile(path)
	if err != nil {
		return "Ошибка: " + err.Error()
	}

	data := map[string]interface{}{
		"width":  maze.Width,
		"height": maze.Height,
		"cells":  maze.Cells,
	}
	jsonData, _ := json.Marshal(data)
	return string(jsonData)
}

func (a *App) Solve(jsonStr string, startX, startY, endX, endY int) string {
	var data struct {
		Width  int                  `json:"width"`
		Height int                  `json:"height"`
		Cells  [][]application.Cell `json:"cells"`
	}

	json.Unmarshal([]byte(jsonStr), &data)

	maze := &application.Maze{
		Width:  data.Width,
		Height: data.Height,
		Cells:  data.Cells,
	}

	path := application.SolveMaze(maze, startX, startY, endX, endY)
	if path == nil {
		return "[]"
	}

	jsonData, _ := json.Marshal(path)
	return string(jsonData)
}

func (a *App) LoadCave(filename string) string {
	path := "../../cave_back/" + filename
	c, err := cave.LoadFromFile(path)
	if err != nil {
		return "ERROR: " + err.Error()
	}

	var result strings.Builder
	result.WriteString(fmt.Sprintf("%d %d\n", c.Rows, c.Cols))

	for i := 0; i < c.Rows; i++ {
		for j := 0; j < c.Cols; j++ {
			if c.Cells[i][j] {
				result.WriteString("1")
			} else {
				result.WriteString("0")
			}
			if j < c.Cols-1 {
				result.WriteString(" ")
			}
		}
		result.WriteString("\n")
	}

	return result.String()
}

func (a *App) GenerateCave(jsonStr string, birthLimit, deathLimit int, chance float64) string {
	var data struct {
		Width  int     `json:"width"`
		Height int     `json:"height"`
		Cells  [][]int `json:"cells"`
	}

	if err := json.Unmarshal([]byte(jsonStr), &data); err != nil {
		return "Ошибка: неверный формат данных"
	}

	cells := make([][]bool, data.Height)
	for i := 0; i < data.Height; i++ {
		cells[i] = make([]bool, data.Width)
		for j := 0; j < data.Width; j++ {
			cells[i][j] = data.Cells[i][j] == 1
		}
	}

	c := &cave.Cave{
		Rows:  data.Height,
		Cols:  data.Width,
		Cells: cells,
	}

	changed := c.Step(birthLimit, deathLimit)

	resultCells := make([][]int, c.Rows)
	for i := 0; i < c.Rows; i++ {
		resultCells[i] = make([]int, c.Cols)
		for j := 0; j < c.Cols; j++ {
			if c.Cells[i][j] {
				resultCells[i][j] = 1
			} else {
				resultCells[i][j] = 0
			}
		}
	}

	result := map[string]interface{}{
		"width":   c.Cols,
		"height":  c.Rows,
		"cells":   resultCells,
		"changed": changed,
		"type":    "cave",
	}

	jsonData, _ := json.Marshal(result)
	return string(jsonData)
}

func (a *App) CaveStep(jsonStr string, birthLimit, deathLimit int) string {
	return a.GenerateCave(jsonStr, birthLimit, deathLimit, 0)
}

func (a *App) CreateRandomCave(width, height int, chance float64) string {
	if width < 1 || height < 1 || width > 50 || height > 50 {
		return "Ошибка: размеры 1-50"
	}

	c := cave.Random(height, width, chance)

	cells := make([][]int, c.Rows)
	for i := 0; i < c.Rows; i++ {
		cells[i] = make([]int, c.Cols)
		for j := 0; j < c.Cols; j++ {
			if c.Cells[i][j] {
				cells[i][j] = 1
			} else {
				cells[i][j] = 0
			}
		}
	}

	data := map[string]interface{}{
		"width":  c.Cols,
		"height": c.Rows,
		"cells":  cells,
		"type":   "cave",
	}

	jsonData, _ := json.Marshal(data)
	return string(jsonData)
}

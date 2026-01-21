package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"os"
	"path/filepath"
	"strings"

	"cave/cave"
	"maze/pkg/application"
)

type MazeJSON struct {
	Width  int                  `json:"width"`
	Height int                  `json:"height"`
	Cells  [][]application.Cell `json:"cells"`
}

type CaveJSON struct {
	Width  int     `json:"width"`
	Height int     `json:"height"`
	Cells  [][]int `json:"cells"`
	Type   string  `json:"type"`
}

func mazeToJSON(m *application.Maze) MazeJSON {
	return MazeJSON{
		Width:  m.Width,
		Height: m.Height,
		Cells:  m.Cells,
	}
}

func mazeFromJSON(mj MazeJSON) *application.Maze {
	return &application.Maze{
		Width:  mj.Width,
		Height: mj.Height,
		Cells:  mj.Cells,
	}
}

func caveFromJSON(cj CaveJSON) *cave.Cave {
	cells := make([][]bool, cj.Height)
	for i := 0; i < cj.Height; i++ {
		cells[i] = make([]bool, cj.Width)
		for j := 0; j < cj.Width; j++ {
			cells[i][j] = (cj.Cells[i][j] == 1)
		}
	}
	return &cave.Cave{
		Rows:  cj.Height,
		Cols:  cj.Width,
		Cells: cells,
	}
}

func caveToJSON(caveObj *cave.Cave) CaveJSON {
	cells := make([][]int, caveObj.Rows)
	for i := 0; i < caveObj.Rows; i++ {
		cells[i] = make([]int, caveObj.Cols)
		for j := 0; j < caveObj.Cols; j++ {
			if caveObj.Cells[i][j] {
				cells[i][j] = 1
			} else {
				cells[i][j] = 0
			}
		}
	}
	return CaveJSON{
		Width:  caveObj.Cols,
		Height: caveObj.Rows,
		Cells:  cells,
		Type:   "cave",
	}
}

func sendJSONText(w http.ResponseWriter, v any) {
	w.Header().Set("Content-Type", "text/plain; charset=utf-8")
	data, err := json.Marshal(v)
	if err != nil {
		http.Error(w, "internal json error", http.StatusInternalServerError)
		return
	}
	w.Write(data)
}

func sendText(w http.ResponseWriter, message string) {
	w.Header().Set("Content-Type", "text/plain; charset=utf-8")
	fmt.Fprint(w, message)
}

func main() {
	apiMux := http.NewServeMux()
	apiMux.HandleFunc("/api/generate", handleGenerate)
	apiMux.HandleFunc("/api/save-maze", handleSaveMaze)
	apiMux.HandleFunc("/api/load-maze", handleLoadMaze)
	apiMux.HandleFunc("/api/solve", handleSolve)
	apiMux.HandleFunc("/api/load-cave", handleLoadCave)
	apiMux.HandleFunc("/api/cave-step", handleCaveStep)
	apiMux.HandleFunc("/api/create-random-cave", handleCreateRandomCave)

	cwd, _ := os.Getwd()
	staticPath := filepath.Join(cwd, "../frontend/dist")

	fileServer := http.FileServer(http.Dir(staticPath))

	handler := http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		if strings.HasPrefix(r.URL.Path, "/api/") {
			apiMux.ServeHTTP(w, r)
			return
		}

		path := filepath.Join(staticPath, r.URL.Path)
		if info, err := os.Stat(path); err == nil && !info.IsDir() {
			fileServer.ServeHTTP(w, r)
			return
		}
		http.ServeFile(w, r, filepath.Join(staticPath, "index.html"))
	})

	log.Println("Server on localhost:8080")
	if err := http.ListenAndServe(":8080", handler); err != nil {
		log.Fatal(err)
	}
}

func handleGenerate(w http.ResponseWriter, r *http.Request) {
	var req struct {
		Width  int `json:"width"`
		Height int `json:"height"`
	}
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		sendJSONText(w, map[string]string{"error": "invalid json: " + err.Error()})
		return
	}

	m := application.GenerateEller(req.Width, req.Height)
	if m == nil {
		sendJSONText(w, map[string]string{"error": "failed to generate maze"})
		return
	}

	sendJSONText(w, mazeToJSON(m))
}

func handleSaveMaze(w http.ResponseWriter, r *http.Request) {
	var req struct {
		JsonStr  string `json:"jsonStr"`
		Filename string `json:"filename"`
	}
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		sendText(w, "Ошибка парсинга JSON: "+err.Error())
		return
	}
	if req.Filename == "" {
		sendText(w, "Имя файла не задано")
		return
	}

	var mj MazeJSON
	if err := json.Unmarshal([]byte(req.JsonStr), &mj); err != nil {
		sendText(w, "Ошибка парсинга лабиринта: "+err.Error())
		return
	}
	maze := mazeFromJSON(mj)

	path := filepath.Join("datasource", req.Filename)
	if err := application.SaveToFile(maze, path); err != nil {
		sendText(w, "Ошибка сохранения: "+err.Error())
		return
	}
	sendText(w, "Сохранено в "+req.Filename)
}

func handleLoadMaze(w http.ResponseWriter, r *http.Request) {

	var req struct {
		Filename string `json:"filename"`
	}
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		sendJSONText(w, map[string]string{"error": "invalid json: " + err.Error()})
		return
	}
	if req.Filename == "" {
		sendJSONText(w, map[string]string{"error": "empty filename"})
		return
	}

	path := filepath.Join("datasource", req.Filename)
	maze, err := application.LoadFromFile(path)
	if err != nil {
		sendJSONText(w, map[string]string{"error": err.Error()})
		return
	}
	sendJSONText(w, mazeToJSON(maze))
}

func handleSolve(w http.ResponseWriter, r *http.Request) {

	var req struct {
		JsonStr string `json:"jsonStr"`
		StartX  int    `json:"startX"`
		StartY  int    `json:"startY"`
		EndX    int    `json:"endX"`
		EndY    int    `json:"endY"`
	}
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		sendJSONText(w, map[string]string{"error": "invalid json: " + err.Error()})
		return
	}

	var mj MazeJSON
	if err := json.Unmarshal([]byte(req.JsonStr), &mj); err != nil {
		sendJSONText(w, map[string]string{"error": "invalid maze json: " + err.Error()})
		return
	}
	maze := mazeFromJSON(mj)

	path := application.SolveMaze(maze, req.StartX, req.StartY, req.EndX, req.EndY)
	if path == nil {
		sendJSONText(w, map[string]string{"error": "no path found"})
		return
	}
	sendJSONText(w, path)
}

func handleLoadCave(w http.ResponseWriter, r *http.Request) {

	var req struct {
		Filename string `json:"filename"`
	}
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		sendText(w, "ERROR: "+err.Error())
		return
	}

	path := filepath.Join("cave_data", req.Filename)
	content, err := os.ReadFile(path)
	if err != nil {
		sendText(w, "ERROR: "+err.Error())
		return
	}
	sendText(w, string(content))
}

func handleCreateRandomCave(w http.ResponseWriter, r *http.Request) {

	var req struct {
		Width  int     `json:"width"`
		Height int     `json:"height"`
		Chance float64 `json:"chance"`
	}
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		sendText(w, "ERROR: "+err.Error())
		return
	}
	if req.Width < 1 || req.Width > cave.MaxSize || req.Height < 1 || req.Height > cave.MaxSize {
		sendText(w, "ERROR: invalid size")
		return
	}

	cv := cave.Random(req.Height, req.Width, req.Chance)
	var sb strings.Builder
	fmt.Fprintf(&sb, "%d %d\n", cv.Rows, cv.Cols)
	for i := 0; i < cv.Rows; i++ {
		for j := 0; j < cv.Cols; j++ {
			if j > 0 {
				sb.WriteByte(' ')
			}
			if cv.Cells[i][j] {
				sb.WriteByte('1')
			} else {
				sb.WriteByte('0')
			}
		}
		sb.WriteByte('\n')
	}

	sendText(w, sb.String())
}

func handleCaveStep(w http.ResponseWriter, r *http.Request) {

	var req struct {
		JsonStr    string `json:"jsonStr"`
		BirthLimit int    `json:"birthLimit"`
		DeathLimit int    `json:"deathLimit"`
	}
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		sendJSONText(w, map[string]string{"error": "invalid json: " + err.Error()})
		return
	}

	var cj CaveJSON
	if err := json.Unmarshal([]byte(req.JsonStr), &cj); err != nil {
		sendJSONText(w, map[string]string{"error": "invalid cave json: " + err.Error()})
		return
	}

	cv := caveFromJSON(cj)
	_ = cv.Step(req.BirthLimit, req.DeathLimit)

	newCJ := caveToJSON(cv)
	sendJSONText(w, newCJ)
}

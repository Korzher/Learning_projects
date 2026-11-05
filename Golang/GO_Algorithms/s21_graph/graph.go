package s21_graph

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// Graph хранит граф в виде матрицы смежности
// Вершины нумеруются с 1
type Graph struct {
	adj  [][]int
	size int
}

// NewGraph создает пустой граф
func NewGraph() *Graph {
	return &Graph{}
}

// Size возвращает количество вершин
func (g *Graph) Size() int {
	return g.size
}

// AddEdge добавляет ориентированное ребро u -> v произвольного веса
func (g *Graph) AddWeightedEdge(u, v, w int) error {
	if u < 1 || v < 1 || u > g.size || v > g.size {
		return errors.New("vertex out of range")
	}
	g.adj[u][v] = w
	return nil
}

// AddEdge добавляет ориентированное ребро u -> v весом в 1
func (g *Graph) AddEdge(u, v int) error {
	return g.AddWeightedEdge(u, v, 1)
}

// Weight получает вес ребра из матрицы смежности
func (g *Graph) Weight(u, v int) int {
	if u < 1 || v < 1 || u > g.size || v > g.size {
		return 0
	}
	return g.adj[u][v]
}

// Neighbors возвращает список смежных вершин
func (g *Graph) Neighbors(v int) []int {
	res := []int{}
	if v < 1 || v > g.size {
		return res
	}
	for i := 1; i <= g.size; i++ {
		if g.adj[v][i] != 0 {
			res = append(res, i)
		}
	}
	return res
}

// LoadGraphFromFile загружает граф из файла (матрица смежности)
func (g *Graph) LoadGraphFromFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	matrix := [][]int{}

	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}

		fields := strings.Fields(line)
		row := make([]int, len(fields)+1)
		for i, f := range fields {
			val, err := strconv.Atoi(f)
			if err != nil {
				return errors.New("invalid matrix format")
			}
			row[i+1] = val
		}
		matrix = append(matrix, row)
	}

	if err := scanner.Err(); err != nil {
		return err
	}

	size := len(matrix)
	if size == 0 {
		return errors.New("empty graph")
	}

	for _, row := range matrix {
		if len(row)-1 != size {
			return errors.New("matrix must be square")
		}
	}

	adj := make([][]int, size+1)
	for i := 1; i <= size; i++ {
		adj[i] = make([]int, size+1)
		copy(adj[i][1:], matrix[i-1][1:])
	}

	g.adj = adj
	g.size = size
	return nil
}

// ExportGraphToDot выгружает граф в DOT
func (g *Graph) ExportGraphToDot(filename string) error {
	if g.size == 0 {
		return errors.New("graph is empty")
	}

	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	w := bufio.NewWriter(file)
	defer w.Flush()

	fmt.Fprintln(w, "digraph G {")
	for i := 1; i <= g.size; i++ {
		for j := 1; j <= g.size; j++ {
			if g.adj[i][j] != 0 {
				fmt.Fprintf(w, "  %d -> %d;\n", i, j)
			}
		}
	}
	fmt.Fprintln(w, "}")
	return nil
}

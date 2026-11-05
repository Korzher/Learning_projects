package s21_graph

import (
	"os"
	"reflect"
	"testing"
)

func createTempGraphFile(t *testing.T, content string) string {
	file, err := os.CreateTemp("", "graph_*.txt")
	if err != nil {
		t.Fatal(err)
	}
	_, _ = file.WriteString(content)
	file.Close()
	return file.Name()
}

func TestLoadGraphFromFile(t *testing.T) {
	content := "0 1 0\n0 0 1\n1 0 0\n"
	filename := createTempGraphFile(t, content)
	defer os.Remove(filename)

	g := NewGraph()
	if err := g.LoadGraphFromFile(filename); err != nil {
		t.Fatalf("unexpected error: %v", err)
	}

	if g.Size() != 3 {
		t.Errorf("expected size 3, got %d", g.Size())
	}
}

func TestLoadGraphInvalidMatrix(t *testing.T) {
	content := "0 1\n1 0 1\n"
	filename := createTempGraphFile(t, content)
	defer os.Remove(filename)

	g := NewGraph()
	if err := g.LoadGraphFromFile(filename); err == nil {
		t.Errorf("expected error for invalid matrix")
	}
}

func TestNeighbors(t *testing.T) {
	content := "0 1 1\n0 0 0\n0 0 0\n"
	filename := createTempGraphFile(t, content)
	defer os.Remove(filename)

	g := NewGraph()
	_ = g.LoadGraphFromFile(filename)

	expected := []int{2, 3}
	res := g.Neighbors(1)

	if !reflect.DeepEqual(res, expected) {
		t.Errorf("expected %v, got %v", expected, res)
	}
}

func TestAddEdge(t *testing.T) {
	// создаём граф через файл (как требует ТЗ)
	content := "0 0 0\n0 0 0\n0 0 0\n"
	filename := createTempGraphFile(t, content)
	defer os.Remove(filename)

	g := NewGraph()
	if err := g.LoadGraphFromFile(filename); err != nil {
		t.Fatalf("load failed: %v", err)
	}

	// добавляем ребро через публичный метод
	if err := g.AddEdge(1, 2); err != nil {
		t.Fatalf("unexpected error: %v", err)
	}

	// проверяем результат через публичный API
	neighbors := g.Neighbors(1)
	expected := []int{2}

	if !reflect.DeepEqual(neighbors, expected) {
		t.Errorf("expected %v, got %v", expected, neighbors)
	}
}

func TestExportGraphToDot(t *testing.T) {
	content := "0 1\n0 0\n"
	input := createTempGraphFile(t, content)
	defer os.Remove(input)

	output, _ := os.CreateTemp("", "graph_*.dot")
	output.Close()
	defer os.Remove(output.Name())

	g := NewGraph()
	_ = g.LoadGraphFromFile(input)

	if err := g.ExportGraphToDot(output.Name()); err != nil {
		t.Fatalf("export failed: %v", err)
	}
}

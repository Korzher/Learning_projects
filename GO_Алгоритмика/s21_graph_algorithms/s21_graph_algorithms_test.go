package s21_graph_algorithms

import (
	"math"
	"os"
	"reflect"
	"testing"

	"s21/s21_graph"
)

func createTestGraph(t *testing.T) *s21_graph.Graph {
	content := "0 1 1 0 0\n0 0 0 1 0\n0 0 0 0 1\n0 0 0 0 0\n0 0 0 0 0\n"

	file, err := os.CreateTemp("", "graph_*.txt")
	if err != nil {
		t.Fatal(err)
	}
	defer file.Close()

	_, _ = file.WriteString(content)

	g := s21_graph.NewGraph()
	if err := g.LoadGraphFromFile(file.Name()); err != nil {
		t.Fatal(err)
	}

	return g
}

func TestDFS(t *testing.T) {
	ga := New()
	g := createTestGraph(t)

	res := ga.DepthFirstSearch(g, 1)
	expected := []int{1, 2, 4, 3, 5}

	if !reflect.DeepEqual(res, expected) {
		t.Errorf("DFS failed: expected %v, got %v", expected, res)
	}
}

func TestBFS(t *testing.T) {
	ga := New()
	g := createTestGraph(t)

	res := ga.BreadthFirstSearch(g, 1)
	expected := []int{1, 2, 3, 4, 5}

	if !reflect.DeepEqual(res, expected) {
		t.Errorf("BFS failed: expected %v, got %v", expected, res)
	}
}

func TestGetShortestPathBetweenVertices(t *testing.T) {
	ga := New()
	g := createTestGraph(t)

	type args struct {
		from, to int
	}
	tests := []struct {
		name     string
		args     args
		expected int
	}{
		{
			name:     "simple path 1->2",
			args:     args{from: 1, to: 2},
			expected: 1,
		},
		{
			name:     "path 1->4",
			args:     args{from: 1, to: 4},
			expected: 2,
		},
		{
			name:     "path 1->5",
			args:     args{from: 1, to: 5},
			expected: 2,
		},
		{
			name:     "same vertex 3->3",
			args:     args{from: 3, to: 3},
			expected: 0,
		},
		{
			name:     "no path 4->3",
			args:     args{from: 4, to: 3},
			expected: -1,
		},
		{
			name:     "invalid vertex (0)",
			args:     args{from: 0, to: 1},
			expected: -1,
		},
		{
			name:     "invalid vertex (out of range)",
			args:     args{from: 1, to: 100},
			expected: -1,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got := ga.GetShortestPathBetweenVertices(g, tt.args.from, tt.args.to)
			if got != tt.expected {
				t.Errorf("GetShortestPathBetweenVertices(%d, %d) = %d, want %d",
					tt.args.from, tt.args.to, got, tt.expected)
			}
		})
	}
}

func TestGetShortestPathsBetweenAllVertices(t *testing.T) {
	ga := New()
	g := createTestGraph(t)

	dist := ga.GetShortestPathsBetweenAllVertices(g)
	if dist == nil {
		t.Fatalf("GetShortestPathsBetweenAllVertices returned nil")
	}

	type check struct {
		from, to int
		expected int
	}

	checks := []check{
		{from: 1, to: 1, expected: 0},
		{from: 1, to: 2, expected: 1},
		{from: 1, to: 3, expected: 1},
		{from: 1, to: 4, expected: 2},
		{from: 1, to: 5, expected: 2},
		{from: 4, to: 3, expected: -1},
	}

	for _, c := range checks {
		if got := dist[c.from][c.to]; got != c.expected {
			t.Errorf("dist[%d][%d] = %d, want %d", c.from, c.to, got, c.expected)
		}
	}

	n := g.Size()
	diag := make([]int, n)
	for i := 1; i <= n; i++ {
		diag[i-1] = dist[i][i]
	}
	expectedDiag := make([]int, n) // все нули
	if !reflect.DeepEqual(diag, expectedDiag) {
		t.Errorf("diagonal of dist matrix = %v, want %v", diag, expectedDiag)
	}
}

func TestGetLeastSpanningTree(t *testing.T) {
	content := `0 2 3 0 0
                2 0 1 0 0
                3 1 0 5 0
                0 0 5 0 2
                0 0 0 2 0`

	file, err := os.CreateTemp("", "graph_*.txt")
	if err != nil {
		t.Fatal(err)
	}
	defer os.Remove(file.Name())
	file.WriteString(content)
	file.Close()

	g := s21_graph.NewGraph()
	if err := g.LoadGraphFromFile(file.Name()); err != nil {
		t.Fatal(err)
	}

	ga := New()
	mst := ga.GetLeastSpanningTree(g)

	n := g.Size()
	expected := make([][]int, n+1)
	expected[0] = nil

	for i := 1; i <= n; i++ {
		expected[i] = make([]int, n+1)
	}

	expected[1][2] = 2
	expected[2][1] = 2
	expected[2][3] = 1
	expected[3][2] = 1
	expected[3][4] = 5
	expected[4][3] = 5
	expected[4][5] = 2
	expected[5][4] = 2

	if !reflect.DeepEqual(mst, expected) {
		t.Errorf("MST incorrect\nexpected:\n%v\ngot:\n%v", expected, mst)
	}
}

func TestSolveTravelingSalesmanProblem(t *testing.T) {
	t.Run("empty graph", func(t *testing.T) {
		ga := New()
		g := s21_graph.NewGraph()

		file, err := os.CreateTemp("", "empty_graph_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		if err := g.LoadGraphFromFile(file.Name()); err == nil {
			result, err := ga.SolveTravelingSalesmanProblem(g)
			if err == nil {
				t.Error("expected error for empty graph")
			}
			if result != nil {
				t.Error("expected nil result for empty graph")
			}
		}
	})

	t.Run("nil graph", func(t *testing.T) {
		ga := New()
		result, err := ga.SolveTravelingSalesmanProblem(nil)
		if err == nil {
			t.Error("expected error for nil graph")
		}
		if result != nil {
			t.Error("expected nil result for nil graph")
		}
	})

	t.Run("single vertex graph", func(t *testing.T) {
		ga := New()

		content := "0\n"
		file, err := os.CreateTemp("", "single_vertex_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		result, err := ga.SolveTravelingSalesmanProblem(g)
		if err != nil {
			t.Errorf("unexpected error for single vertex: %v", err)
		}
		if result == nil {
			t.Error("expected non-nil result")
		}
		if len(result.Vertices) != 2 || result.Vertices[0] != 1 || result.Vertices[1] != 1 {
			t.Errorf("unexpected vertices: %v", result.Vertices)
		}
		if result.Distance != 0 {
			t.Errorf("expected distance 0, got %v", result.Distance)
		}
	})

	t.Run("complete graph 3 vertices", func(t *testing.T) {
		ga := New()

		content := "0 1 2\n1 0 3\n2 3 0\n"
		file, err := os.CreateTemp("", "complete_3_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		result, err := ga.SolveTravelingSalesmanProblem(g)
		if err != nil {
			t.Errorf("unexpected error: %v", err)
		}
		if result == nil {
			t.Error("expected non-nil result")
		}

		if len(result.Vertices) != 4 {
			t.Errorf("expected 4 vertices in cycle, got %v", len(result.Vertices))
		}
		if result.Vertices[0] != result.Vertices[3] {
			t.Error("cycle doesn't end at starting vertex")
		}

		if result.Distance <= 0 {
			t.Errorf("expected positive distance, got %v", result.Distance)
		}
	})

	t.Run("graph with no Hamiltonian cycle", func(t *testing.T) {
		ga := New()

		content := "0 1 0 0\n1 0 1 0\n0 1 0 1\n0 0 1 0\n"
		file, err := os.CreateTemp("", "no_cycle_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		result, err := ga.SolveTravelingSalesmanProblem(g)
		if err == nil {
			t.Error("expected error for graph without Hamiltonian cycle")
		}
		if result != nil {
			t.Error("expected nil result for graph without Hamiltonian cycle")
		}
	})

	t.Run("fully connected graph 4 vertices", func(t *testing.T) {
		ga := New()

		content := "0 1 1 1\n1 0 1 1\n1 1 0 1\n1 1 1 0\n"
		file, err := os.CreateTemp("", "complete_4_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		result, err := ga.SolveTravelingSalesmanProblem(g)
		if err != nil {
			t.Errorf("unexpected error: %v", err)
		}
		if result == nil {
			t.Error("expected non-nil result")
		}

		if len(result.Vertices) != 5 {
			t.Errorf("expected 5 vertices in cycle (4 + start), got %v", len(result.Vertices))
		}

		visited := make(map[int]bool)
		for i := 0; i < 4; i++ {
			vertex := result.Vertices[i]
			if vertex < 1 || vertex > 4 {
				t.Errorf("vertex out of range: %d", vertex)
			}
			if visited[vertex] && i != 3 {
				t.Errorf("vertex %d visited twice", vertex)
			}
			visited[vertex] = true
		}

		if math.Abs(result.Distance-4) > 0.01 {
			t.Errorf("expected distance ~4, got %v", result.Distance)
		}
	})

	t.Run("graph with isolated vertex", func(t *testing.T) {
		ga := New()

		content := "0 1 0\n1 0 0\n0 0 0\n"
		file, err := os.CreateTemp("", "isolated_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		result, err := ga.SolveTravelingSalesmanProblem(g)
		if err == nil {
			t.Error("expected error for graph with isolated vertex")
		}
		if result != nil {
			t.Error("expected nil result for graph with isolated vertex")
		}
	})

	t.Run("asymmetric graph", func(t *testing.T) {
		ga := New()

		content := "0 5 0\n0 0 3\n2 0 0\n"
		file, err := os.CreateTemp("", "asymmetric_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		result, err := ga.SolveTravelingSalesmanProblem(g)
		if err == nil {
			if result == nil {
				t.Error("expected non-nil result when no error")
			} else {
				n := g.Size()
				if len(result.Vertices) != n+1 {
					t.Errorf("expected %d vertices, got %d", n+1, len(result.Vertices))
				}
				if result.Vertices[0] != result.Vertices[n] {
					t.Error("cycle doesn't end at starting vertex")
				}
				if result.Distance <= 0 {
					t.Errorf("expected positive distance, got %v", result.Distance)
				}
			}
		}
	})

	t.Run("graph with self-loops", func(t *testing.T) {
		ga := New()

		content := "5 1 0\n0 2 1\n0 0 3\n"
		file, err := os.CreateTemp("", "self_loops_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		result, err := ga.SolveTravelingSalesmanProblem(g)
		if err == nil {
			if result != nil {
				n := g.Size()
				if len(result.Vertices) != n+1 {
					t.Errorf("expected %d vertices, got %d", n+1, len(result.Vertices))
				}
			}
		}
	})

	t.Run("graph with zero weights", func(t *testing.T) {
		ga := New()

		content := "0 0 1\n0 0 0\n1 0 0\n"
		file, err := os.CreateTemp("", "zero_weights_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		_, err = ga.SolveTravelingSalesmanProblem(g)
		// Граф не полный, должен вернуть ошибку
		if err == nil {
			t.Error("expected error for incomplete graph")
		}
	})

	t.Run("large complete graph 5 vertices", func(t *testing.T) {
		ga := New()

		// Большой полный граф
		content := "0 2 3 1 4\n2 0 5 6 7\n3 5 0 8 9\n1 6 8 0 10\n4 7 9 10 0\n"
		file, err := os.CreateTemp("", "large_complete_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		result, err := ga.SolveTravelingSalesmanProblem(g)
		if err != nil {
			t.Errorf("unexpected error for complete graph: %v", err)
		}
		if result == nil {
			t.Error("expected non-nil result for complete graph")
		} else {
			// Проверяем базовые свойства
			n := g.Size()
			if len(result.Vertices) != n+1 {
				t.Errorf("expected %d vertices, got %d", n+1, len(result.Vertices))
			}
			if result.Vertices[0] != result.Vertices[n] {
				t.Error("cycle doesn't end at starting vertex")
			}
			if result.Distance <= 0 {
				t.Errorf("expected positive distance, got %v", result.Distance)
			}

			// Проверяем что все вершины посещены
			visited := make(map[int]bool)
			for i := 0; i < n; i++ {
				vertex := result.Vertices[i]
				if vertex < 1 || vertex > n {
					t.Errorf("vertex out of range: %d", vertex)
				}
				if visited[vertex] {
					t.Errorf("vertex %d visited twice", vertex)
				}
				visited[vertex] = true
			}
		}
	})

	t.Run("graph with very large weights", func(t *testing.T) {
		ga := New()

		// Граф с очень большими весами
		content := "0 10000 20000\n10000 0 30000\n20000 30000 0\n"
		file, err := os.CreateTemp("", "large_weights_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		result, err := ga.SolveTravelingSalesmanProblem(g)
		if err != nil {
			t.Errorf("unexpected error: %v", err)
		}
		if result == nil {
			t.Error("expected non-nil result")
		} else {
			if result.Distance < 30000 {
				t.Errorf("expected large distance > 30000, got %v", result.Distance)
			}
		}
	})

	t.Run("graph with mixed connectivity", func(t *testing.T) {
		ga := New()

		// Граф со смешанной связностью
		content := "0 1 1 0 0\n1 0 1 0 0\n1 1 0 0 0\n0 0 0 0 1\n0 0 0 1 0\n"
		file, err := os.CreateTemp("", "mixed_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		result, err := ga.SolveTravelingSalesmanProblem(g)
		if err == nil {
			t.Error("expected error for disconnected graph")
		}
		if result != nil {
			t.Error("expected nil result for disconnected graph")
		}
	})

	t.Run("graph where start vertex matters", func(t *testing.T) {
		ga := New()

		// Граф, где результат зависит от стартовой вершины
		content := "0 10 15 20\n10 0 35 25\n15 35 0 30\n20 25 30 0\n"
		file, err := os.CreateTemp("", "start_matters_*.txt")
		if err != nil {
			t.Fatal(err)
		}
		defer os.Remove(file.Name())
		file.Close()

		file2, err := os.Create(file.Name())
		if err != nil {
			t.Fatal(err)
		}
		defer file2.Close()
		_, _ = file2.WriteString(content)

		g := s21_graph.NewGraph()
		if err := g.LoadGraphFromFile(file.Name()); err != nil {
			t.Fatal(err)
		}

		result, err := ga.SolveTravelingSalesmanProblem(g)
		if err != nil {
			t.Errorf("unexpected error: %v", err)
		}
		if result == nil {
			t.Error("expected non-nil result")
		} else {
			n := g.Size()
			if len(result.Vertices) != n+1 {
				t.Errorf("expected %d vertices, got %d", n+1, len(result.Vertices))
			}
			if result.Vertices[0] != result.Vertices[n] {
				t.Error("cycle doesn't end at starting vertex")
			}
		}
	})
}

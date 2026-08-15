package s21_graph_algorithms

import (
	"errors"
	"math"
	"math/rand"
	"s21/s21_graph"
	"s21/s21_queue"
	"s21/s21_stack"
)

// GraphAlgorithms — алгоритмы на графах
type GraphAlgorithms struct{}

func New() *GraphAlgorithms {
	return &GraphAlgorithms{}
}

type TsmResult struct {
	Vertices []int
	Distance float64
}

// DepthFirstSearch — нерекурсивный DFS (вершины с 1)
func (ga *GraphAlgorithms) DepthFirstSearch(g *s21_graph.Graph, start int) []int {
	size := g.Size()
	visited := make([]bool, size+1)
	result := []int{}

	stack := s21_stack.Stack()
	stack.Push(start)

	for !stack.IsEmpty() {
		v, _ := stack.Pop()
		if visited[v] {
			continue
		}
		visited[v] = true
		result = append(result, v)

		neighbors := g.Neighbors(v)
		for i := len(neighbors) - 1; i >= 0; i-- {
			if !visited[neighbors[i]] {
				stack.Push(neighbors[i])
			}
		}
	}
	return result
}

// BreadthFirstSearch — BFS (вершины с 1)
func (ga *GraphAlgorithms) BreadthFirstSearch(g *s21_graph.Graph, start int) []int {
	size := g.Size()
	visited := make([]bool, size+1)
	result := []int{}

	queue := s21_queue.Queue()
	queue.Push(start)
	visited[start] = true

	for !queue.IsEmpty() {
		v, _ := queue.Pop()
		result = append(result, v)

		for _, n := range g.Neighbors(v) {
			if !visited[n] {
				visited[n] = true
				queue.Push(n)
			}
		}
	}
	return result
}

func (ga *GraphAlgorithms) GetShortestPathBetweenVertices(g *s21_graph.Graph, vertex1, vertex2 int) int {
	if g == nil {
		return -1
	}

	n := g.Size()
	if vertex1 < 1 || vertex1 > n || vertex2 < 1 || vertex2 > n {
		return -1
	}
	if vertex1 == vertex2 {
		return 0
	}

	const INF = int(1e9)

	dist := make([]int, n+1)
	used := make([]bool, n+1)

	for i := 1; i <= n; i++ {
		dist[i] = INF
	}
	dist[vertex1] = 0

	for i := 1; i <= n; i++ {
		v := -1
		for j := 1; j <= n; j++ {
			if !used[j] && (v == -1 || dist[j] < dist[v]) {
				v = j
			}
		}

		if v == -1 || dist[v] == INF {
			break
		}
		used[v] = true

		if v == vertex2 {
			break
		}

		for _, to := range g.Neighbors(v) {
			if used[to] {
				continue
			}
			w := g.Weight(v, to)
			if w <= 0 {
				continue
			}
			nd := dist[v] + w
			if nd < dist[to] {
				dist[to] = nd
			}
		}
	}
	if dist[vertex2] == INF {
		return -1
	}
	return dist[vertex2]
}

func (ga *GraphAlgorithms) GetShortestPathsBetweenAllVertices(g *s21_graph.Graph) [][]int {
	if g == nil {
		return nil
	}

	const INF = int(1e9)
	n := g.Size()
	dist := make([][]int, n+1)
	for i := 1; i <= n; i++ {
		dist[i] = make([]int, n+1)
	}

	for i := 1; i <= n; i++ {
		for j := 1; j <= n; j++ {
			if i == j {
				dist[i][j] = 0
				continue
			}
			w := g.Weight(i, j)
			if w > 0 {
				dist[i][j] = w
			} else {
				dist[i][j] = INF
			}
		}
	}
	for k := 1; k <= n; k++ {
		for i := 1; i <= n; i++ {
			if dist[i][k] == INF {
				continue
			}
			for j := 1; j <= n; j++ {
				if dist[k][j] == INF {
					continue
				}
				nd := dist[i][k] + dist[k][j]
				if nd < dist[i][j] {
					dist[i][j] = nd
				}
			}
		}
	}
	for i := 1; i <= n; i++ {
		for j := 1; j <= n; j++ {
			if i != j && dist[i][j] == INF {
				dist[i][j] = -1
			}
		}
	}
	return dist
}

// GetLeastSpanningTree — алгоритм Прима
func (ga *GraphAlgorithms) GetLeastSpanningTree(graph *s21_graph.Graph) [][]int {
	if graph == nil {
		return nil
	}
	n := graph.Size()
	if n == 0 {
		return nil
	}

	const INF = int(1e9)

	inMST := make([]bool, n+1)
	minEdge := make([]int, n+1)
	parent := make([]int, n+1)

	for i := 1; i <= n; i++ {
		minEdge[i] = INF
		parent[i] = -1
	}

	// стартуем с вершины 1
	minEdge[1] = 0

	for i := 1; i <= n; i++ {
		v := -1
		for j := 1; j <= n; j++ {
			if !inMST[j] && (v == -1 || minEdge[j] < minEdge[v]) {
				v = j
			}
		}

		if v == -1 || minEdge[v] == INF {
			break
		}

		inMST[v] = true

		for to := 1; to <= n; to++ {
			weight := graph.Weight(v, to)
			if weight != 0 && !inMST[to] && weight < minEdge[to] {
				minEdge[to] = weight
				parent[to] = v
			}
		}
	}

	// формируем MST матрицу n+1 x n+1 (1-based)
	mst := make([][]int, n+1)
	for i := 1; i <= n; i++ {
		mst[i] = make([]int, n+1)
	}

	for v := 2; v <= n; v++ {
		u := parent[v]
		if u != -1 {
			w := graph.Weight(u, v)
			mst[u][v] = w
			mst[v][u] = w
		}
	}

	return mst
}

func (ga *GraphAlgorithms) SolveTravelingSalesmanProblem(graph *s21_graph.Graph) (*TsmResult, error) {
	if graph == nil {
		return nil, errors.New("graph is nil")
	}

	n := graph.Size()
	if n == 0 {
		return nil, errors.New("graph is empty")
	}

	for i := 1; i <= n; i++ {
		hasConnection := false
		for j := 1; j <= n; j++ {
			if i != j && graph.Weight(i, j) > 0 {
				hasConnection = true
				break
			}
		}
		if !hasConnection && n > 1 {
			return nil, errors.New("graph has isolated vertices, cycle does not exist")
		}
	}

	const INF = int(1e9)
	dist := make([][]int, n+1)
	for i := 1; i <= n; i++ {
		dist[i] = make([]int, n+1)
		for j := 1; j <= n; j++ {
			if i == j {
				dist[i][j] = 0
			} else {
				w := graph.Weight(i, j)
				if w > 0 {
					dist[i][j] = w
				} else {
					dist[i][j] = INF
				}
			}
		}
	}

	const (
		alpha         = 1.0     // важность феромона    вероятность перехода > math.Pow(pheromone[current][next], alpha) * math.Pow(1.0/float64(dist[current][next]), beta)
		beta          = 2.0     // важность эвристики (1 / dist)
		rho           = 0.5     // коэффициент испарения феромона > pheromone[i][j] *= (1.0 - rho)
		q             = 100.0   // масштаб добавки феромона
		antCount      = 20      // количество муравьёв на итерацию
		maxIterations = 100		// количество итераций
	)

	pheromone := make([][]float64, n+1)
	for i := 1; i <= n; i++ {
		pheromone[i] = make([]float64, n+1)
		for j := 1; j <= n; j++ {
			if i != j && dist[i][j] < INF {
				pheromone[i][j] = 1.0
			}
		}
	}

	bestTour := make([]int, n)
	bestLength := math.MaxFloat64

	for iteration := 0; iteration < maxIterations; iteration++ {
		antTours := make([][]int, antCount)
		antLengths := make([]float64, antCount)

		for ant := 0; ant < antCount; ant++ {
			start := rand.Intn(n) + 1
			tour := make([]int, 0, n)
			visited := make([]bool, n+1)
			current := start
			tour = append(tour, current)
			visited[current] = true

			for len(tour) < n {
				probabilities := make([]float64, n+1)
				total := 0.0

				for next := 1; next <= n; next++ {
					if !visited[next] && dist[current][next] < INF {
						prob := math.Pow(pheromone[current][next], alpha) * math.Pow(1.0/float64(dist[current][next]), beta)
						probabilities[next] = prob
						total += prob
					}
				}

				if total == 0 {
					break
				}

				for i := 1; i <= n; i++ {
					if probabilities[i] > 0 {
						probabilities[i] /= total
					}
				}

				r := rand.Float64()
				cumulative := 0.0
				selected := -1

				for next := 1; next <= n; next++ {
					if probabilities[next] > 0 {
						cumulative += probabilities[next]
						if r <= cumulative {
							selected = next
							break
						}
					}
				}

				if selected == -1 {
					break
				}

				current = selected
				tour = append(tour, current)
				visited[current] = true
			}

			if len(tour) < n {
				antLengths[ant] = math.MaxFloat64
				antTours[ant] = tour
				continue
			}

			tourWithReturn := make([]int, len(tour)+1)
			copy(tourWithReturn, tour)
			tourWithReturn[len(tour)] = start

			length := 0.0
			valid := true
			for i := 0; i < len(tourWithReturn)-1; i++ {
				from := tourWithReturn[i]
				to := tourWithReturn[i+1]
				if dist[from][to] >= INF {
					length = math.MaxFloat64
					valid = false
					break
				}
				length += float64(dist[from][to])
			}

			antTours[ant] = tour
			if valid {
				antLengths[ant] = length
			} else {
				antLengths[ant] = math.MaxFloat64
			}

			if valid && length < bestLength {
				bestLength = length
				copy(bestTour, tour)
			}
		}

		for i := 1; i <= n; i++ {
			for j := 1; j <= n; j++ {
				if i != j && dist[i][j] < INF {
					pheromone[i][j] *= (1.0 - rho)
					if pheromone[i][j] < 0.1 {
						pheromone[i][j] = 0.1
					}
				}
			}
		}

		for ant := 0; ant < antCount; ant++ {
			if antLengths[ant] >= math.MaxFloat64-1 {
				continue
			}

			tour := antTours[ant]
			if len(tour) != n {
				continue
			}

			deltaPheromone := q / antLengths[ant]

			for i := 0; i < len(tour); i++ {
				from := tour[i]
				to := tour[(i+1)%len(tour)]
				if from > 0 && to > 0 && from <= n && to <= n && dist[from][to] < INF {
					pheromone[from][to] += deltaPheromone
					pheromone[to][from] += deltaPheromone
				}
			}
		}
	}

	if bestLength >= math.MaxFloat64-1 {
		return nil, errors.New("no Hamiltonian cycle found")
	}

	finalTour := make([]int, len(bestTour))
	copy(finalTour, bestTour)
	finalLength := 0.0

	for i := 0; i < len(finalTour); i++ {
		from := finalTour[i]
		to := finalTour[(i+1)%len(finalTour)]
		if dist[from][to] >= INF {
			return nil, errors.New("found tour contains non-existent edges")
		}
		finalLength += float64(dist[from][to])
	}

	fullCycle := make([]int, len(finalTour)+1)
	copy(fullCycle, finalTour)
	fullCycle[len(finalTour)] = finalTour[0]

	return &TsmResult{
		Vertices: fullCycle,
		Distance: finalLength,
	}, nil
}

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"s21/s21_graph"
	"s21/s21_graph_algorithms"
)

func printMenu() {
	fmt.Println("\n===== Graph Console =====")
	fmt.Println("1. Load graph from file")
	fmt.Println("2. Breadth First Search (BFS)")
	fmt.Println("3. Depth First Search (DFS)")
	fmt.Println("4. Shortest Path (Dijkstra)")
	fmt.Println("5. Shortest Path Between All Certices (Floyd-Warshall)")
	fmt.Println("6. Minimum Spanning Tree (Prim)")
	fmt.Println("7. Traveling Salesman Problem (TSM)")
	fmt.Println("8. Export graph to DOT file")
	fmt.Println("0. Exit")
	fmt.Print("Choose option: ")
}

func readInt(reader *bufio.Reader) int {
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(input)
	value, _ := strconv.Atoi(input)
	return value
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	graph := s21_graph.NewGraph()
	algorithms := s21_graph_algorithms.New()

	graphLoaded := false

	for {
		printMenu()
		choice := readInt(reader)

		switch choice {

		case 1:
			fmt.Print("Enter filename: ")
			filename, _ := reader.ReadString('\n')
			filename = strings.TrimSpace(filename)

			if err := graph.LoadGraphFromFile(filename); err != nil {
				fmt.Println("Error loading graph:", err)
			} else {
				graphLoaded = true
				fmt.Println("Graph loaded successfully")
			}

		case 2:
			if !graphLoaded {
				fmt.Println("Graph not loaded")
				continue
			}
			fmt.Print("Start vertex: ")
			start := readInt(reader)

			result := algorithms.BreadthFirstSearch(graph, start)
			fmt.Println("BFS result:", result)

		case 3:
			if !graphLoaded {
				fmt.Println("Graph not loaded")
				continue
			}
			fmt.Print("Start vertex: ")
			start := readInt(reader)

			result := algorithms.DepthFirstSearch(graph, start)
			fmt.Println("DFS result:", result)

		case 4:
			if !graphLoaded {
				fmt.Println("Graph not loaded")
				continue
			}
			fmt.Print("Start vertex: ")
			start := readInt(reader)
			fmt.Print("End vertex: ")
			end := readInt(reader)

			result := algorithms.GetShortestPathBetweenVertices(graph, start, end)
			fmt.Println("Shortest Path:", result)

		case 5:
			if !graphLoaded {
				fmt.Println("Graph not loaded")
				continue
			}

			result := algorithms.GetShortestPathsBetweenAllVertices(graph)
			n := graph.Size()

			fmt.Println("Shortest paths (Floyd-Warshall):")
			for i := 1; i <= n; i++ {
				fmt.Println(result[i][1:])
			}

		case 6:
			if !graphLoaded {
				fmt.Println("Graph not loaded")
				continue
			}

			mst := algorithms.GetLeastSpanningTree(graph)
			fmt.Println("Minimum Spanning Tree (Adjacency Matrix):")

			for i := 1; i <= graph.Size(); i++ {
				for j := 1; j <= graph.Size(); j++ {
					fmt.Printf("%d ", mst[i][j])
				}
				fmt.Println()
			}

		case 7:
			if !graphLoaded {
				fmt.Println("Graph not loaded")
				continue
			}

			tsm, err := algorithms.SolveTravelingSalesmanProblem(graph)
			if err != nil {
				fmt.Println(err)
			}
			fmt.Println("Shortest Path:", tsm.Vertices)
			fmt.Println("Shortest Distance:", tsm.Distance)

		case 8:
			if !graphLoaded {
				fmt.Println("Graph not loaded")
				continue
			}

			fmt.Print("Enter output DOT filename: ")
			filename, _ := reader.ReadString('\n')
			filename = strings.TrimSpace(filename)

			if err := graph.ExportGraphToDot(filename); err != nil {
				fmt.Println("Export failed:", err)
			} else {
				fmt.Println("Graph exported successfully to", filename)
			}

		case 0:
			fmt.Println("Exit.")
			return

		default:
			fmt.Println("Invalid option")
		}
	}
}

package main

import (
	"fmt"
	"maze/pkg/application"
)

func main() {
	fmt.Println("\n Training RL agent...")

	fmt.Println("Enter maze file:")
	var file string
	fmt.Scan(&file)
	file = "../../maze_back/pkg/datasource/" + file

	maze, err := application.LoadFromFile(file)
	if err != nil {
		fmt.Println("Load error:", err)
		return
	}

	fmt.Println("Enter exit point:")
	var endX, endY int
	fmt.Print("End X: ")
	fmt.Scan(&endX)
	fmt.Print("End Y: ")
	fmt.Scan(&endY)

	agent := application.NewRLAgent()
	application.TrainAgent(agent, maze, endX, endY, 5000)
	application.PrintRLStats(agent)

	fmt.Println("\n6. Enter start point:")
	var sx, sy int

	fmt.Print("Start X: ")
	fmt.Scan(&sx)
	fmt.Print("Start Y: ")
	fmt.Scan(&sy)

	path := application.BuildRLPath(agent, maze, sx, sy, endX, endY)

	fmt.Println("\nRL Path:")
	application.PrintWithPath(maze, path, sx, sy, endX, endY)
}

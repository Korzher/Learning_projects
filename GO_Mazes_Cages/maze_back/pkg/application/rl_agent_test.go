package application

import "testing"

func TestRLFindsExit(t *testing.T) {
	m := NewMaze(3, 3, false)

	// стенка
	m.Cells[1][1].Right = true

	agent := NewRLAgent()
	TrainAgent(agent, m, 2, 2, 3000)

	path := BuildRLPath(agent, m, 0, 0, 2, 2)

	last := path[len(path)-1]

	if last[0] != 2 || last[1] != 2 {
		t.Fatal("agent did not reach exit")
	}
}

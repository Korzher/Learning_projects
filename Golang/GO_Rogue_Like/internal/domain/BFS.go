package domain

func distAndNextPosToTarget(start *Enemy, target *Character, level *Level) []Direction {
	if checkEqualPosition(start.Position, target.Position) {
		return nil
	}
	q := CreateQueue()
	defer q.Free()
	q.Enqueue(start.Position)

	dx := []int{0, 0, -1, 1}
	dy := []int{-1, 1, 0, 0}
	dirs := []Direction{Up, Down, Left, Right}

	visit := make([][]bool, MapHeight)
	dist := make([][]int, MapHeight)
	dirParent := make([][]Direction, MapHeight)
	parent := make([][]Position, MapHeight)

	for i := range visit {
		visit[i] = make([]bool, MapWidth)
		dist[i] = make([]int, MapWidth)
		dirParent[i] = make([]Direction, MapWidth)
		parent[i] = make([]Position, MapWidth)
	}

	visit[start.Position.Y][start.Position.X] = true
	dist[start.Position.Y][start.Position.X] = 0
	parent[start.Position.Y][start.Position.X] = start.Position

	found := false
	targetDistance := 0

	for !q.IsEmpty() {
		current := q.Dequeue()
		currentDist := dist[current.Y][current.X]

		if checkEqualPosition(current, target.Position) {
			found = true
			targetDistance = currentDist
			break
		}

		for i := 0; i < len(dirs); i++ {
			nextPos := Position{
				X: current.X + dx[i],
				Y: current.Y + dy[i],
			}

			if nextPos.X < 0 || nextPos.X >= MapWidth || nextPos.Y < 0 || nextPos.Y >= MapHeight {
				continue
			}

			if !visit[nextPos.Y][nextPos.X] && isPositionAccessible(nextPos, level, true) {
				visit[nextPos.Y][nextPos.X] = true
				dist[nextPos.Y][nextPos.X] = currentDist + 1
				parent[nextPos.Y][nextPos.X] = current
				dirParent[nextPos.Y][nextPos.X] = dirs[i]
				q.Enqueue(nextPos)
			}
		}
	}

	maxVisionDistance := getVisionDistance(start.Hostility)
	if found && targetDistance <= maxVisionDistance {
		var path []Direction
		current := target.Position

		for !checkEqualPosition(parent[current.Y][current.X], start.Position) {
			path = append(path, dirParent[current.Y][current.X])
			current = parent[current.Y][current.X]
		}
		path = append(path, dirParent[current.Y][current.X])
		for i, j := 0, len(path)-1; i < j; i, j = i+1, j-1 {
			path[i], path[j] = path[j], path[i]
		}
		return path
	}
	return nil
}

func isPositionAccessible(pos Position, level *Level, ignoreEnemies bool) bool {
	if pos.X < 0 || pos.X >= MapWidth || pos.Y < 0 || pos.Y >= MapHeight {
		return false
	}
	inWalkableArea := false
	for _, room := range level.Rooms {
		if !outsideRoom(pos, room) {
			inWalkableArea = true
			break
		}
	}

	if !inWalkableArea {
		for _, corridor := range level.Corridors {
			for _, corridorPos := range corridor.Path {
				if pos.X == corridorPos.X && pos.Y == corridorPos.Y {
					inWalkableArea = true
					break
				}
			}
			if inWalkableArea {
				break
			}
		}
	}

	if !inWalkableArea {
		return false
	}

	if !ignoreEnemies {
		for _, enemy := range level.Enemies {
			if checkEqualPosition(pos, enemy.Position) {
				return false
			}
		}
	}
	return true
}

func getVisionDistance(hostility HostilityType) int {
	switch hostility {
	case HostilityTypeLow:
		return 2
	case HostilityTypeAverage:
		return 4
	case HostilityTypeHigh:
		return 6
	default:
		return 1
	}
}

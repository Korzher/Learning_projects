package domain

import (
	"math/rand"
	"time"
)

type Level struct {
	LevelNum       int
	Rooms          [RoomsNum]Room
	Corridors      []Corridor
	Enemies        []*Enemy
	Items          []Item
	Entry          string
	Exit           string
	ExitPos        Position
	StartRoomIndex int
	ExitRoomIndex  int
}

func (l *Level) GenerateRooms(rng *rand.Rand) {
	roomIndex := 0

	for sy := 0; sy < SectorY; sy++ {
		for sx := 0; sx < SectorX; sx++ {
			minX, minY, maxX, maxY := boundsForSector(sx, sy)

			minW, maxW := 6, (maxX-minX)/2
			minH, maxH := 4, (maxY-minY)/2

			width := rng.Intn(maxW-minW+1) + minW
			height := rng.Intn(maxH-minH+1) + minH

			xRange := maxX - minX + 1 - width
			yRange := maxY - minY + 1 - height

			x := minX + rng.Intn(xRange)
			y := minY + rng.Intn(yRange)

			l.Rooms[roomIndex] = Room{
				TopLeft: Position{X: x, Y: y},
				Width:   width,
				Height:  height,
			}

			roomIndex++
		}
	}
}

func indexFromRC(row, col int) int {
	return row*SectorX + col
}

func buildCorridorPath(from, to Position) []Position {
	var path []Position

	x := from.X
	y := from.Y

	dx := 0
	if to.X > x {
		dx = 1
	} else if to.X < x {
		dx = -1
	}

	for x != to.X {
		path = append(path, Position{X: x, Y: y})
		x += dx
	}
	path = append(path, Position{X: x, Y: y})

	dy := 0
	if to.Y > y {
		dy = 1
	} else if to.Y < y {
		dy = -1
	}

	for y != to.Y {
		path = append(path, Position{X: x, Y: y})
		y += dy
	}

	path = append(path, Position{X: x, Y: y})

	return path
}

func (l *Level) BuildTileMap() MapGrid {
	var grid MapGrid

	for y := 0; y < MapHeight; y++ {
		for x := 0; x < MapWidth; x++ {
			grid[y][x] = TileEmpty
		}
	}

	for _, cor := range l.Corridors {
		for _, pos := range cor.Path {
			grid[pos.Y][pos.X] = TileCorridor
		}
	}

	for _, room := range l.Rooms {
		for y := room.TopLeft.Y; y < room.TopLeft.Y+room.Height; y++ {
			for x := room.TopLeft.X; x < room.TopLeft.X+room.Width; x++ {
				grid[y][x] = TileRoom
			}
		}
	}

	if (l.ExitPos == Position{}) {
		exitRoom := l.Rooms[l.ExitRoomIndex]
		l.ExitPos = RandomPositionInRoom(exitRoom, rand.New(rand.NewSource(time.Now().UnixNano())))
	}

	grid[l.ExitPos.Y][l.ExitPos.X] = TileExit

	for y := 0; y < MapHeight; y++ {
		for x := 0; x < MapWidth; x++ {
			if grid[y][x] == TileRoom {
				directions := []Position{
					{X: x, Y: y - 1},
					{X: x, Y: y + 1},
					{X: x - 1, Y: y},
					{X: x + 1, Y: y},
				}

				for _, dir := range directions {
					if dir.X >= 0 && dir.X < MapWidth && dir.Y >= 0 && dir.Y < MapHeight {
						if grid[dir.Y][dir.X] == TileEmpty {
							grid[dir.Y][dir.X] = TileWall
						}
					}
				}
			}
		}
	}

	return grid
}

func (l *Level) GenerateEnemies(rng *rand.Rand) {
	l.Enemies = nil

	n := 3 + l.LevelNum
	if n < 1 {
		n = 1
	}

	availableRooms := make([]int, 0, RoomsNum-1)
	for i := 0; i < RoomsNum; i++ {

		if i != l.StartRoomIndex {
			availableRooms = append(availableRooms, i)
		}
	}

	for i := 0; i < n; i++ {
		roomInd := availableRooms[rng.Intn(len(availableRooms))]
		room := l.Rooms[roomInd]
		pos := RandomPositionInRoom(room, rng)
		enemyType := EnemyType(rng.Intn(5))
		enemy := NewEnemyFromType(enemyType, pos.X, pos.Y, l)

		l.Enemies = append(l.Enemies, &enemy)
	}
}

func (r Room) GetExitPosition(target Room) Position {
	center := r.Center()
	targetCenter := target.Center()

	if targetCenter.X > center.X {
		return Position{
			X: r.TopLeft.X + r.Width - 1,
			Y: center.Y,
		}
	} else if targetCenter.X < center.X {
		return Position{
			X: r.TopLeft.X,
			Y: center.Y,
		}
	} else if targetCenter.Y > center.Y {
		return Position{
			X: center.X,
			Y: r.TopLeft.Y + r.Height - 1,
		}
	} else {
		return Position{
			X: center.X,
			Y: r.TopLeft.Y,
		}
	}
}

func (l *Level) GenerateCorridors() {
	l.Corridors = nil

	for row := 0; row < SectorY; row++ {
		for col := 0; col < SectorX-1; col++ {
			fromIdx := indexFromRC(row, col)
			toIdx := indexFromRC(row, col+1)

			fromExit := l.Rooms[fromIdx].GetExitPosition(l.Rooms[toIdx])
			toExit := l.Rooms[toIdx].GetExitPosition(l.Rooms[fromIdx])

			path := buildCorridorPath(fromExit, toExit)

			l.Corridors = append(l.Corridors, Corridor{
				From: fromIdx,
				To:   toIdx,
				Path: path,
			})
		}
	}

	for row := 0; row < SectorY-1; row++ {
		for col := 0; col < SectorX; col++ {
			fromIdx := indexFromRC(row, col)
			toIdx := indexFromRC(row+1, col)

			fromExit := l.Rooms[fromIdx].GetExitPosition(l.Rooms[toIdx])
			toExit := l.Rooms[toIdx].GetExitPosition(l.Rooms[fromIdx])

			path := buildCorridorPath(fromExit, toExit)

			l.Corridors = append(l.Corridors, Corridor{
				From: fromIdx,
				To:   toIdx,
				Path: path,
			})
		}
	}
}

func (l *Level) IsPlayerOnExit(char *Character) bool {
	return char.Position.X == l.ExitPos.X && char.Position.Y == l.ExitPos.Y
}

func (l *Level) selectStartAndExitRooms(rng *rand.Rand) {
	for {
		l.StartRoomIndex = rng.Intn(RoomsNum)
		l.ExitRoomIndex = rng.Intn(RoomsNum)
		if l.StartRoomIndex != l.ExitRoomIndex {
			break
		}
	}
}

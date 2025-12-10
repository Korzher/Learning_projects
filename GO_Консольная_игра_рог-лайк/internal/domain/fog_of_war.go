package domain

import (
	"math"
)

func NewFogOfWar() *FogOfWar {
	fog := &FogOfWar{
		ViewDistance: 3,
	}

	for y := 0; y < MapHeight; y++ {
		for x := 0; x < MapWidth; x++ {
			fog.Visibility[y][x] = VisibilityUnexplored
		}
	}

	return fog
}

func (f *FogOfWar) UpdateVisibility(playerPos Position, level *Level, grid MapGrid) {
	for y := 0; y < MapHeight; y++ {
		for x := 0; x < MapWidth; x++ {
			if f.Visibility[y][x] == VisibilityVisible {
				f.Visibility[y][x] = VisibilityExplored
			}
		}
	}

	var currentRoom *Room
	for i := range level.Rooms {
		room := &level.Rooms[i]
		if !outsideRoom(playerPos, *room) {
			currentRoom = room
			break
		}
	}

	if currentRoom != nil {
		f.revealRoom(*currentRoom)
	} else {
		f.calculateRayCastingVisibility(playerPos, grid, f.ViewDistance)
	}
}

func (f *FogOfWar) revealRoom(room Room) {
	for y := room.TopLeft.Y - 1; y <= room.TopLeft.Y+room.Height; y++ {
		for x := room.TopLeft.X - 1; x <= room.TopLeft.X+room.Width; x++ {
			f.Visibility[y][x] = VisibilityVisible
		}
	}
}

// Алгоритм расчета RayCasting с применением модернизированного алгоритма Брезенхама
func (f *FogOfWar) calculateRayCastingVisibility(playerPos Position, grid MapGrid, radius int) {
	for angle := 0; angle < 360; angle += 5 {
		rad := float64(angle) * math.Pi / 180.0
		dx := math.Cos(rad)
		dy := math.Sin(rad)

		for r := 0.0; r < float64(radius); r += 0.5 {
			x := int(float64(playerPos.X) + dx*r)
			y := int(float64(playerPos.Y) + dy*r)

			if x < 0 || x >= MapWidth || y < 0 || y >= MapHeight {
				break
			}
			f.Visibility[y][x] = VisibilityVisible
			if grid[y][x] == TileWall {
				break
			}
		}
	}
}

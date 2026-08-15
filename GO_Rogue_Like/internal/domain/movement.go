package domain

import (
	"math/rand"
)

func moveCharacterByDirection(direction Direction, position *Position) {
	switch direction {
	case Up:
		position.Y--
	case Down:
		position.Y++
	case Left:
		position.X--
	case Right:
		position.X++
	// Для монстров
	case DiagForwardLeft:
		position.X--
		position.Y--
	case DiagForwardRight:
		position.X++
		position.Y--
	case DiagBackLeft:
		position.X--
		position.Y++
	case DiagBackRight:
		position.X++
		position.Y++
	case Stop:
	}
}

func moveCharacterByPath(path []Direction, position *Position) {
	for _, direction := range path {
		moveCharacterByDirection(direction, position)
	}
}

func outsideRoom(pos Position, room Room) bool {
	roomLeft := room.TopLeft.X
	roomRight := room.TopLeft.X + room.Width - 1
	roomTop := room.TopLeft.Y
	roomBottom := room.TopLeft.Y + room.Height - 1

	return pos.X < roomLeft ||
		pos.X > roomRight ||
		pos.Y < roomTop ||
		pos.Y > roomBottom
}

func isPlayerNear(pos Position, enemy *Enemy) bool {
	dist := AbsInt(pos.X-enemy.Position.X) + AbsInt(pos.Y-enemy.Position.Y)

	switch enemy.Hostility {
	case HostilityTypeLow:
		return dist <= LowHostilityRadius
	case HostilityTypeAverage:
		return dist <= AverageHostilityRadius
	case HostilityTypeHigh:
		return dist <= HighHostilityRadius
	default:
		return false
	}
}

func MoveMonster(enemy *Enemy, char *Character, level *Level) {
	npcMovementFunctions := map[string]NPCMovementFunc{
		"Zombie":  patternZombie,
		"Vampire": patternVampire,
		"Ghost":   patternGhost,
		"Ogre":    patternOgre,
		"Snake":   patternSnake,
	}

	enemy.IsVisible = true
	var path []Direction
	if isPlayerNear(char.Position, enemy) {
		path = distAndNextPosToTarget(enemy, char, level)
		if len(path) > 0 {
			path = path[:1]
		}
	}

	if len(path) == 0 {
		movementFunc := npcMovementFunctions[enemy.Type]
		if movementFunc != nil {
			path = movementFunc(enemy, level)
		}
	}

	if len(path) > 0 {
		originalCoords := enemy.Position
		tempCoords := originalCoords
		moveCharacterByPath(path, &tempCoords)

		cellOccupied := false
		for i := range level.Enemies {
			if &level.Enemies[i] != &enemy &&
				level.Enemies[i].Health > 0 &&
				checkEqualPosition(tempCoords, level.Enemies[i].Position) {
				cellOccupied = true
				break
			}
		}

		if !cellOccupied && !checkEqualPosition(tempCoords, char.Position) {
			moveCharacterByPath(path, &enemy.Position)
		}

		enemy.Dir = path[len(path)-1]
	}
}

func patternZombie(enemy *Enemy, level *Level) []Direction {
	const maxTriesToMove = 10
	directions := []Direction{Up, Down, Left, Right}

	for try := 0; try < maxTriesToMove; try++ {
		currentDirection := directions[rand.Intn(len(directions))]
		newPos := getPositionInDirection(enemy.Position, currentDirection)

		if isPositionAccessible(newPos, level, false) {
			return []Direction{currentDirection}
		}
	}

	return nil
}

func patternVampire(enemy *Enemy, level *Level) []Direction {
	const maxTriesToMove = 10
	allDirections := []Direction{Up, Down, Left, Right}

	for try := 0; try < maxTriesToMove; try++ {
		currentDirection := allDirections[rand.Intn(len(allDirections))]
		newPos := getPositionInDirection(enemy.Position, currentDirection)

		if isPositionAccessible(newPos, level, false) {
			return []Direction{currentDirection}
		}
	}

	return nil
}

func patternGhost(enemy *Enemy, level *Level) []Direction {
	var currentRoom *Room

	for i := 0; i < len(level.Rooms) && currentRoom == nil; i++ {
		if !outsideRoom(enemy.Position, level.Rooms[i]) {
			currentRoom = &level.Rooms[i]
		}
	}

	if currentRoom == nil {
		return nil
	}

	enemy.IsVisible = rand.Intn(100) >= 20

	for try := 0; try < MaxTriesToMove; try++ {
		randomPos := Position{
			X: currentRoom.TopLeft.X + 1 + rand.Intn(currentRoom.Width-2),
			Y: currentRoom.TopLeft.Y + 1 + rand.Intn(currentRoom.Height-2),
		}

		if isPositionAccessible(randomPos, level, false) {
			path := distAndNextPosToTarget(enemy, &Character{Position: randomPos}, level)
			if path != nil {
				return path
			}
		}
	}

	return nil
}

func patternOgre(enemy *Enemy, level *Level) []Direction {
	for try := 0; try < MaxTriesToMove; try++ {
		currentDirection := Direction(rand.Intn(4))
		canMove := true

		tempPos := enemy.Position
		for step := 0; step < OgreStep; step++ {
			tempPos = getPositionInDirection(tempPos, currentDirection)
			if !isPositionAccessible(tempPos, level, false) {
				canMove = false
				break
			}
		}

		if canMove {
			path := make([]Direction, OgreStep)
			for i := 0; i < OgreStep; i++ {
				path[i] = currentDirection
			}
			return path
		}
	}
	return nil
}

func patternSnake(enemy *Enemy, level *Level) []Direction {
	diagonalDirections := []Direction{DiagForwardLeft, DiagForwardRight, DiagBackLeft, DiagBackRight}

	for try := 0; try < MaxTriesToMove; try++ {
		currentDirection := diagonalDirections[rand.Intn(len(diagonalDirections))]

		if currentDirection == enemy.Dir {
			continue
		}

		newPos := getPositionInDirection(enemy.Position, currentDirection)
		if isPositionAccessible(newPos, level, false) {
			return []Direction{currentDirection}
		}
	}
	if enemy.Dir != Stop {
		newPos := getPositionInDirection(enemy.Position, enemy.Dir)
		if isPositionAccessible(newPos, level, false) {
			return []Direction{enemy.Dir}
		}
	}

	return nil
}

func getPositionInDirection(pos Position, dir Direction) Position {
	switch dir {
	case Up:
		return Position{X: pos.X, Y: pos.Y - 1}
	case Down:
		return Position{X: pos.X, Y: pos.Y + 1}
	case Left:
		return Position{X: pos.X - 1, Y: pos.Y}
	case Right:
		return Position{X: pos.X + 1, Y: pos.Y}
	case DiagForwardLeft:
		return Position{X: pos.X - 1, Y: pos.Y - 1}
	case DiagForwardRight:
		return Position{X: pos.X + 1, Y: pos.Y - 1}
	case DiagBackLeft:
		return Position{X: pos.X - 1, Y: pos.Y + 1}
	case DiagBackRight:
		return Position{X: pos.X + 1, Y: pos.Y + 1}
	default:
		return pos
	}
}

func TryMoveCharacter(char *Character, level *Level, direction Direction, battles []BattleInfo, logger GameEventLogger) bool {
	newPos := char.Position
	moveCharacterByDirection(direction, &newPos)

	if isPositionAccessibleForPlayer(newPos, level, battles) {
		attacked := false
		for i := range battles {
			if battles[i].IsFight && checkEqualPosition(newPos, battles[i].Enemy.Position) {
				Attack(char, &battles[i], PlayerTurn, level, logger)
				attacked = true
				break
			}
		}
		if !attacked {
			char.Position = newPos
			char.StepsTaken++
			PickupItemAtPlayer(level, char, logger)
		}
		return attacked
	}
	return false
}

func isPositionAccessibleForPlayer(pos Position, level *Level, battles []BattleInfo) bool {

	if pos.X < 0 || pos.X >= MapWidth || pos.Y < 0 || pos.Y >= MapHeight {
		return false
	}

	inRoomOrCorridor := false

	for _, room := range level.Rooms {
		if !outsideRoom(pos, room) {
			inRoomOrCorridor = true
			break
		}
	}

	if !inRoomOrCorridor {
		for _, corridor := range level.Corridors {
			for _, corridorPos := range corridor.Path {
				if pos.X == corridorPos.X && pos.Y == corridorPos.Y {
					inRoomOrCorridor = true
					break
				}
			}
			if inRoomOrCorridor {
				break
			}
		}
	}

	if !inRoomOrCorridor {
		return false
	}

	for i := range battles {
		if battles[i].IsFight && checkEqualPosition(pos, battles[i].Enemy.Position) && battles[i].Enemy.Health > 0 {
			return true
		}
	}

	return true
}

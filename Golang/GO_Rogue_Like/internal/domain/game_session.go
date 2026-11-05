package domain

import "math/rand"

type GameSession struct {
	CurrentLevel Level
	Character    *Character
	GameState    GameState
	Score        int
	FogOfWar     *FogOfWar
}

func NewLevel(levelNum int, rng *rand.Rand) Level {
	var l Level
	l.LevelNum = levelNum

	l.GenerateRooms(rng)
	l.selectStartAndExitRooms(rng)
	l.GenerateCorridors()
	exitRoom := l.Rooms[l.ExitRoomIndex]
	l.ExitPos = RandomPositionInRoom(exitRoom, rng)

	return l
}

func NewGameSession(startLevel int, rng *rand.Rand) *GameSession {
	return &GameSession{
		CurrentLevel: NewLevel(startLevel, rng),
		GameState:    GameStatePlaying,
		Score:        0,
		FogOfWar:     NewFogOfWar(),
	}
}

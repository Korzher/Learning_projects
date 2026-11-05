package domain

type Enemy struct {
	Type      string
	Health    int
	MaxHealth int
	Agility   int
	Strength  int
	Hostility HostilityType
	Position  Position
	State     State
	IsVisible bool
	Dir       Direction
}

func NewEnemyFromType(e EnemyType, x, y int, level *Level) Enemy {
	switch e {
	case Zombie:
		return Enemy{
			Type:      "Zombie",
			Health:    HighHealth + (level.LevelNum-1)*8,
			MaxHealth: HighHealth + (level.LevelNum-1)*8,
			Agility:   LowDex,
			Strength:  MediumStr,
			Hostility: HostilityTypeAverage,
			Position:  Position{X: x, Y: y},
			State:     StateAlive,
			IsVisible: true,
			Dir:       Stop,
		}
	case Vampire:
		return Enemy{
			Type:      "Vampire",
			Health:    HighHealth + (level.LevelNum-1)*8,
			MaxHealth: HighHealth + (level.LevelNum-1)*8,
			Agility:   HighDex,
			Strength:  MediumStr,
			Hostility: HostilityTypeHigh,
			Position:  Position{X: x, Y: y},
			State:     StateAlive,
			IsVisible: true,
			Dir:       Stop,
		}
	case Ghost:
		return Enemy{
			Type:      "Ghost",
			Health:    LowHealth + (level.LevelNum-1)*2,
			MaxHealth: LowHealth + (level.LevelNum-1)*2,
			Agility:   HighDex,
			Strength:  LowStr,
			Hostility: HostilityTypeLow,
			Position:  Position{X: x, Y: y},
			State:     StateAlive,
			IsVisible: true,
		}
	case Ogre:
		return Enemy{
			Type:      "Ogre",
			Health:    VeryHighHealth + (level.LevelNum-1)*10,
			MaxHealth: VeryHighHealth + (level.LevelNum-1)*10,
			Agility:   LowDex,
			Strength:  VeryHighStr,
			Hostility: HostilityTypeAverage,
			Position:  Position{X: x, Y: y},
			State:     StateAlive,
			IsVisible: true,
			Dir:       Stop,
		}
	case Snake:
		return Enemy{
			Type:      "Snake",
			Health:    MediumHealth + (level.LevelNum-1)*6,
			MaxHealth: MediumHealth + (level.LevelNum-1)*6,
			Agility:   VeryHighDex,
			Strength:  LowStr,
			Hostility: HostilityTypeHigh,
			Position:  Position{X: x, Y: y},
			State:     StateAlive,
			IsVisible: true,
			Dir:       Stop,
		}
	default:
		return Enemy{}
	}
}

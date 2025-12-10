package domain

type GameState int
type HostilityType int
type State string
type TireType int
type EnemyType int
type ConsumableType int
type StatType int
type Turn int
type BattleEventType int
type VisibilityType int

const (
	VisibilityUnexplored VisibilityType = iota
	VisibilityExplored
	VisibilityVisible
)

type VisibilityGrid [MapHeight][MapWidth]VisibilityType

type FogOfWar struct {
	Visibility   VisibilityGrid
	ViewDistance int
}

type Position struct {
	X int
	Y int
}

type Buff struct {
	StatIncrease int
	EffectEnd    int
}

type Buffs struct {
	MaxHealth []Buff
	Agility   []Buff
	Strength  []Buff
}

type BattleEvent struct {
	Type      BattleEventType
	EnemyType string
	Dealt     int
	Received  int
	Loot      int
	ItemName  string
}

type ItemEventType int

const (
	FoodUsed ItemEventType = iota
	ElixirUsed
	ScrollUsed
	WeaponEquipped
)

type ItemEvent struct {
	Type     ItemEventType
	ItemName string
	Effect   string
}

type GameEventLogger interface {
	LogBattleEvent(event BattleEvent)
	LogItemEvent(event ItemEvent)
}

type Direction int

const (
	BattleStart BattleEventType = iota
	PlayerAttack
	MonsterAttack
	EnemyDefeated
	ItemPickedUp
)

const (
	Up Direction = iota
	Down
	Left
	Right
	DiagForwardLeft
	DiagForwardRight
	DiagBackLeft
	DiagBackRight
	Stop
)

const (
	GameStatePlaying GameState = iota
	GameStateWon
	GameStateLost
)

const (
	TileWall TireType = iota
	TileRoom
	TileCorridor
	TileExit
	TileEmpty
)

type BFSNode struct {
	Pos  Position
	Dist int
	Dir  Direction
	Prev Position
}

const (
	MaxType         = 9
	MaxBackpackSize = 36
)

type MapGrid [MapHeight][MapWidth]TireType

type NPCMovementFunc func(*Enemy, *Level) []Direction

type BattleInfo struct {
	IsFight            bool
	Enemy              *Enemy
	VampireFirstAttack bool
	OgreCooldown       bool
	PlayerAsleep       bool
}

const (
	MapWidth  = 80
	MapHeight = 36
	RoomsNum  = 9
)

const (
	SectorX = 3
	SectorY = 3
)

const (
	LowDex                         = 20
	MediumDex                      = 40
	HighDex                        = 60
	VeryHighDex                    = 70
	LowStr                         = 25
	MediumStr                      = 50
	HighStr                        = 75
	VeryHighStr                    = 125
	LowHealth                      = 50
	MediumHealth                   = 100
	HighHealth                     = 150
	VeryHighHealth                 = 200
	OgreStep         int           = 2
	HostilityTypeLow HostilityType = iota
	HostilityTypeAverage
	HostilityTypeHigh
)

const (
	LowHostilityRadius     int = 3
	AverageHostilityRadius int = 6
	HighHostilityRadius    int = 9
)

const (
	Zombie EnemyType = iota
	Vampire
	Ghost
	Ogre
	Snake
)

const (
	None ConsumableType = iota
	Food
	Elixir
	Weapon
	Scroll
	Treasure
)

const (
	StatNone StatType = iota
	StatHealth
	StatMaxHealth
	StatAgility
	StatStrength
)

const (
	MaxConsumablesPerRoom = 4
	LevelDifficultyStep   = 3
)

const (
	StateAlive State = "alive"
	StateDead  State = "dead"
)

const (
	PlayerTurn       Turn    = 0
	MonsterTurn      Turn    = 1
	StandartStrength int     = 20
	StandartAgility  int     = 50
	StrengthAddition int     = 65
	StrengthWeight   float32 = 0.3
	AgilityWeight    float32 = 0.3
	AgilityLoot      float32 = 0.2
	HPLoot           float32 = 0.5
	StrLoot          float32 = 0.5
	LevelLoot        int     = 5
	InitialDamage    int     = 10
	InitialHitChance int     = 70
	SleepChance      int     = 15
	MaxTriesToMove   int     = 16
)

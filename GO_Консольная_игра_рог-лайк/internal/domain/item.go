package domain

import "math/rand"

type Item struct {
	Name        string
	Kind        ConsumableType
	Stat        StatType
	Amount      int
	WeaponPower int
	Price       int
	Position    Position
}

var foodNames = []string{
	"Ration of the Ironclad",
	"Crimson Berry Cluster",
	"Loaf of the Forgotten Baker",
	"Smoked Wyrm Jerky",
	"Golden Apple of Vitality",
	"Hardtack of the Endless March",
	"Spiced Venison Strips",
	"Honeyed Nectar Bread",
	"Dried Mushrooms of the Deep",
}

var elixirNames = []string{
	"Elixir of the Jade Serpent",
	"Potion of the Phantom's Breath",
	"Vial of Crimson Vitality",
	"Draught of the Frozen Star",
	"Elixir of the Shattered Mind",
	"Potion of the Wandering Soul",
	"Vial of Ember Essence",
	"Elixir of the Obsidian Veil",
	"Potion of the Howling Wind",
}

var scrollNames = []string{
	"Scroll of Shadowstep",
	"Parchment of Eternal Flame",
	"Manuscript of Forgotten Truths",
	"Scroll of Iron Will",
	"Vellum of the Void",
	"Scroll of Whispers",
	"Tome of the Lost King",
	"Scroll of Unseen Paths",
	"Parchment of Thunderous Roar",
}

var weaponNames = []string{
	"Blade of the Forgotten Dawn",
	"Obsidian Reaver",
	"Fang of the Shadow Wolf",
	"Ironclad Cleaver",
	"Crimson Talon",
	"Thunderstrike Maul",
	"Serpent's Kiss Dagger",
	"Voidrend Sword",
	"Ebonheart Spear",
}

func RandomPositionInRoom(room Room, rng *rand.Rand) Position {
	minX := room.TopLeft.X + 1
	minY := room.TopLeft.Y + 1

	maxX := room.TopLeft.X + room.Width - 2
	maxY := room.TopLeft.Y + room.Height - 2

	if maxX < minX {
		maxX = minX
	}
	if maxY < minY {
		maxY = minY
	}

	x := minX + rng.Intn(maxX-minX+1)
	y := minY + rng.Intn(maxY-minY+1)

	return Position{X: x, Y: y}
}

func newRandomFoodItem(pos Position, rng *rand.Rand) Item {
	heal := LowHealth + rng.Intn(MediumHealth-LowHealth+1)

	name := foodNames[rng.Intn(len(foodNames))]

	return Item{
		Name:     name,
		Kind:     Food,
		Stat:     StatHealth,
		Amount:   heal,
		Price:    0,
		Position: pos,
	}
}

func newRandomElixirItem(pos Position, rng *rand.Rand) Item {
	stats := []StatType{StatAgility, StatStrength, StatMaxHealth}
	stat := stats[rng.Intn(len(stats))]

	var min, max int

	switch stat {
	case StatAgility:
		min, max = LowDex, HighDex
	case StatStrength:
		min, max = LowStr, HighStr
	case StatMaxHealth:
		min, max = LowHealth, HighHealth
	default:
		min, max = 0, 0
	}

	if max < min {
		max = min
	}

	amount := min + rng.Intn(max-min+1)

	name := elixirNames[rng.Intn(len(elixirNames))]

	return Item{
		Name:     name,
		Kind:     Elixir,
		Stat:     stat,
		Amount:   amount,
		Position: pos,
	}
}

func newRandomScrollItem(pos Position, rng *rand.Rand) Item {
	stats := []StatType{StatAgility, StatStrength, StatMaxHealth}
	stat := stats[rng.Intn(len(stats))]

	var amount int
	switch stat {
	case StatAgility:
		amount = MediumDex + rng.Intn(HighDex-MediumDex+1)
	case StatStrength:
		amount = MediumStr + rng.Intn(HighStr-MediumStr+1)
	case StatMaxHealth:
		amount = MediumHealth + rng.Intn(HighHealth-MediumHealth+1)
	default:
		amount = 0
	}

	name := scrollNames[rng.Intn(len(scrollNames))]

	return Item{
		Name:     name,
		Kind:     Scroll,
		Stat:     stat,
		Amount:   amount,
		Position: pos,
	}
}
func newRandomWeaponItem(pos Position, rng *rand.Rand) Item {
	name := weaponNames[rng.Intn(len(weaponNames))]

	power := MediumStr + rng.Intn(VeryHighStr-MediumStr+1)

	return Item{
		Name:        name,
		Kind:        Weapon,
		Stat:        StatNone,
		WeaponPower: power,
		Position:    pos,
	}
}

func newRandomItemOfKind(kind ConsumableType, pos Position, rng *rand.Rand) Item {
	switch kind {
	case Food:
		return newRandomFoodItem(pos, rng)
	case Elixir:
		return newRandomElixirItem(pos, rng)
	case Scroll:
		return newRandomScrollItem(pos, rng)
	case Weapon:
		return newRandomWeaponItem(pos, rng)
	default:
		return Item{Position: pos}
	}
}

func (l *Level) GenerateItems(rng *rand.Rand) {
	l.Items = nil

	maxConsumables := MaxConsumablesPerRoom - l.LevelNum/LevelDifficultyStep
	if maxConsumables < 0 {
		maxConsumables = 0
	}

	availableRooms := make([]Room, 0, RoomsNum-1)
	for i := 0; i < RoomsNum; i++ {
		if i != l.StartRoomIndex {
			availableRooms = append(availableRooms, l.Rooms[i])
		}
	}

	for roomIdx := 0; roomIdx < len(availableRooms); roomIdx++ {
		room := availableRooms[roomIdx]

		if maxConsumables == 0 {
			continue
		}
		count := rng.Intn(maxConsumables + 1)

		for i := 0; i < count; i++ {
			pos := RandomPositionInRoom(room, rng)

			kinds := []ConsumableType{Food, Elixir, Scroll, Weapon}
			kind := kinds[rng.Intn(len(kinds))]

			item := newRandomItemOfKind(kind, pos, rng)
			l.Items = append(l.Items, item)
		}
	}
}

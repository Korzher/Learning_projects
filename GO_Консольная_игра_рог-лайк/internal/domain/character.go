package domain

import (
	"fmt"
)

type Character struct {
	Health          int
	Agility         int
	Strength        int
	RegenLimit      int
	ElixirBuffs     Buffs
	Weapon          Item
	Position        Position
	Backpack        *Backpack
	EnemiesDefeated int
	FoodConsumed    int
	ElixirsUsed     int
	ScrollsRead     int
	AttackDealt     int
	AttackReceived  int
	StepsTaken      int
}

func isPassable(t TireType) bool {
	return t == TileRoom || t == TileCorridor || t == TileExit
}

func PickupItemAtPlayer(lvl *Level, ch *Character, logger GameEventLogger) {
	if ch.Backpack == nil {
		return
	}

	pos := ch.Position

	idx := lvl.FindItemAt(pos)
	if idx < 0 {
		return
	}

	item := lvl.Items[idx]

	if !ch.Backpack.AddItem(item) {
		return
	}

	if logger != nil {
		logger.LogBattleEvent(BattleEvent{
			Type:      ItemPickedUp,
			ItemName:  item.Name,
			EnemyType: consumableTypeToString(item.Kind),
		})
	}

	last := len(lvl.Items) - 1
	lvl.Items[idx] = lvl.Items[last]
	lvl.Items = lvl.Items[:last]
}

func (p *Character) UseItem(index int, lvl *Level, logger GameEventLogger) {
	if index < 0 || index >= len(p.Backpack.Items) {
		return
	}

	item := p.Backpack.Items[index]

	switch item.Kind {
	case Food:
		oldHealth := p.Health
		p.ApplyFood(item)
		if logger != nil {
			logger.LogItemEvent(ItemEvent{
				Type:     FoodUsed,
				ItemName: item.Name,
				Effect:   fmt.Sprintf("HP: %d → %d", oldHealth, p.Health),
			})
		}
		p.Backpack.RemoveAt(index)
		p.FoodConsumed++

	case Elixir:
		oldMaxHealth := p.RegenLimit
		oldStrength := p.Strength
		oldAgility := p.Agility

		p.ApplyElixir(item)

		if logger != nil {
			var effect string
			switch item.Stat {
			case StatMaxHealth:
				effect = fmt.Sprintf("Max HP: %d → %d", oldMaxHealth, p.RegenLimit)
			case StatAgility:
				effect = fmt.Sprintf("Agility: %d → %d", oldAgility, p.Agility)
			case StatStrength:
				effect = fmt.Sprintf("Strength: %d → %d", oldStrength, p.Strength)
			}
			logger.LogItemEvent(ItemEvent{
				Type:     ElixirUsed,
				ItemName: item.Name,
				Effect:   effect,
			})
		}
		p.Backpack.RemoveAt(index)
		p.ElixirsUsed++

	case Scroll:
		oldMaxHealth := p.RegenLimit
		oldStrength := p.Strength
		oldAgility := p.Agility

		p.ApplyScroll(item)

		if logger != nil {
			var effect string
			switch item.Stat {
			case StatMaxHealth:
				effect = fmt.Sprintf("Max HP: %d → %d", oldMaxHealth, p.RegenLimit)
			case StatAgility:
				effect = fmt.Sprintf("Agility: %d → %d", oldAgility, p.Agility)
			case StatStrength:
				effect = fmt.Sprintf("Strength: %d → %d", oldStrength, p.Strength)
			}
			logger.LogItemEvent(ItemEvent{
				Type:     ScrollUsed,
				ItemName: item.Name,
				Effect:   effect,
			})
		}
		p.Backpack.RemoveAt(index)
		p.ScrollsRead++

	case Weapon:
		oldWeapon := p.Weapon
		p.ChangeWeapon(item, lvl)
		if logger != nil {
			effect := fmt.Sprintf("Damage: %d → %d", oldWeapon.WeaponPower, item.WeaponPower)
			logger.LogItemEvent(ItemEvent{
				Type:     WeaponEquipped,
				ItemName: item.Name,
				Effect:   effect,
			})
		}
		p.Backpack.RemoveAt(index)
	}
}

func (p *Character) ApplyFood(item Item) {
	heal := item.Amount

	p.Health += heal
	if p.Health > p.RegenLimit {
		p.Health = p.RegenLimit
	}
}

func (p *Character) ApplyScroll(item Item) {
	amount := item.Amount

	switch item.Stat {
	case StatMaxHealth:
		p.RegenLimit += amount
		p.Health += amount
	case StatAgility:
		p.Agility += amount
	case StatStrength:
		p.Strength += amount
	}
}

func (p *Character) ApplyElixir(item Item) {
	amount := item.Amount
	duration := 30

	buff := Buff{
		StatIncrease: amount,
		EffectEnd:    duration,
	}

	switch item.Stat {
	case StatMaxHealth:
		p.RegenLimit += amount
		p.Health += amount
		p.ElixirBuffs.MaxHealth = append(p.ElixirBuffs.MaxHealth, buff)

	case StatAgility:
		p.Agility += amount
		p.ElixirBuffs.Agility = append(p.ElixirBuffs.Agility, buff)

	case StatStrength:
		p.Strength += amount
		p.ElixirBuffs.Strength = append(p.ElixirBuffs.Strength, buff)
	}
}

func (p *Character) UpdateBuffs() {
	p.ElixirBuffs.MaxHealth = p.updateBuffList(
		p.ElixirBuffs.MaxHealth,
		func(statIncrease int) {
			p.RegenLimit -= statIncrease
			if p.Health > p.RegenLimit {
				p.Health = p.RegenLimit
			}
		},
	)

	p.ElixirBuffs.Agility = p.updateBuffList(
		p.ElixirBuffs.Agility,
		func(statIncrease int) {
			p.Agility -= statIncrease
		},
	)

	p.ElixirBuffs.Strength = p.updateBuffList(
		p.ElixirBuffs.Strength,
		func(statIncrease int) {
			p.Strength -= statIncrease
		},
	)
}

func (p *Character) updateBuffList(buffs []Buff, onExpire func(int)) []Buff {
	newBuffs := make([]Buff, 0, len(buffs))

	for _, buff := range buffs {
		buff.EffectEnd--
		if buff.EffectEnd > 0 {
			newBuffs = append(newBuffs, buff)
		} else {
			onExpire(buff.StatIncrease)
		}
	}

	return newBuffs
}

func findFreeCellNear(lvl *Level, from Position) Position {
	grid := lvl.BuildTileMap()

	dirs := []Position{
		{X: 1, Y: 0},
		{X: -1, Y: 0},
		{X: 0, Y: 1},
		{X: 0, Y: -1},
		{X: 1, Y: 1},
		{X: 1, Y: -1},
		{X: -1, Y: 1},
		{X: -1, Y: -1},
	}

	for _, d := range dirs {
		pos := Position{X: from.X + d.X, Y: from.Y + d.Y}

		if pos.X < 0 || pos.X >= MapWidth || pos.Y < 0 || pos.Y >= MapHeight {
			continue
		}

		if !isPassable(grid[pos.Y][pos.X]) {
			continue
		}

		if lvl.FindItemAt(pos) != -1 {
			continue
		}

		if enemyIndexAt(lvl, pos) != -1 {
			continue
		}
		return pos
	}
	return from
}

func enemyIndexAt(lvl *Level, pos Position) int {
	for i, e := range lvl.Enemies {
		if e.Position.X == pos.X && e.Position.Y == pos.Y {
			return i
		}
	}
	return -1
}

func (p *Character) ChangeWeapon(newWeapon Item, lvl *Level) {
	old := p.Weapon

	switch newWeapon.Kind {
	case Weapon:
		p.Weapon = newWeapon
	case None:
		p.Weapon = Item{Kind: None}
	default:
		return
	}

	if old.Kind == Weapon && old.WeaponPower > 0 {
		if newWeapon.Kind == None && p.Backpack != nil && p.Backpack.AddItem(old) {
			return
		}

		dropPos := findFreeCellNear(lvl, p.Position)

		dropped := Item{
			Name:        old.Name,
			Kind:        Weapon,
			Stat:        StatNone,
			WeaponPower: old.WeaponPower,
			Price:       old.Price,
			Position:    dropPos,
		}

		lvl.Items = append(lvl.Items, dropped)
	}
}

func NewCharacter(x, y int) *Character {
	return &Character{
		Health:      500,
		Agility:     50,
		Strength:    50,
		RegenLimit:  500,
		ElixirBuffs: Buffs{},
		Weapon: Item{
			Name: "None",
		},
		Position: Position{X: x, Y: y},
		Backpack: nil,
	}
}

func consumableTypeToString(kind ConsumableType) string {
	switch kind {
	case Food:
		return "Food"
	case Elixir:
		return "Elixir"
	case Scroll:
		return "Scroll"
	case Weapon:
		return "Weapon"
	}
	return ""
}

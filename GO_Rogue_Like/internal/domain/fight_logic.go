package domain

import (
	"math/rand"
)

var monsterDamageFormulas = map[string]func(*BattleInfo) int{
	"Zombie": zombieGhostDamageFormula,
	"Ghost":  zombieGhostDamageFormula,
	"Ogre":   ogreDamageFormula,
	"Snake":  snakeDamageFormula,
}

func Attack(char *Character, BattleInfo *BattleInfo, currTurn Turn, level *Level, logger GameEventLogger) {

	switch currTurn {
	case PlayerTurn:
		isHit := checkHit(char, BattleInfo.Enemy, currTurn)
		dealtDamage := 0
		if isHit {
			dealtDamage = calculateDamage(char, BattleInfo, currTurn)
			if dealtDamage > 0 {
				char.AttackDealt++
			}
			BattleInfo.Enemy.Health -= dealtDamage

			if BattleInfo.Enemy.Health <= 0 {
				loot := calculateLoot(BattleInfo.Enemy, level)
				char.EnemiesDefeated++
				char.Backpack.Treasures.Value += loot
				if logger != nil {
					logger.LogBattleEvent(BattleEvent{
						Type:      EnemyDefeated,
						EnemyType: BattleInfo.Enemy.Type,
						Loot:      loot,
					})
				}
				BattleInfo.IsFight = false
			}
		}

		if logger != nil {
			logger.LogBattleEvent(BattleEvent{
				Type:      PlayerAttack,
				EnemyType: BattleInfo.Enemy.Type,
				Dealt:     dealtDamage,
			})
		}

	case MonsterTurn:
		isHit := checkHit(char, BattleInfo.Enemy, currTurn)
		receivedDamage := 0
		if isHit {
			receivedDamage = calculateDamage(char, BattleInfo, currTurn)
			if receivedDamage > 0 {
				char.AttackReceived++
			}
			char.Health -= receivedDamage
		}
		if logger != nil {
			logger.LogBattleEvent(BattleEvent{
				Type:      MonsterAttack,
				EnemyType: BattleInfo.Enemy.Type,
				Received:  receivedDamage,
			})
		}
	}
}

func checkHit(char *Character, enemy *Enemy, currTurn Turn) bool {
	var wasHit bool
	chance := InitialHitChance
	switch currTurn {
	case PlayerTurn:
		chance += hitChanceFormula(char.Agility, enemy.Agility)
	case MonsterTurn:
		chance += hitChanceFormula(enemy.Agility, char.Agility)
	}
	if rand.Intn(100) < chance || enemy.Type == "Ogre" {
		wasHit = true
	}
	return wasHit
}

func calculateDamage(char *Character, BattleInfo *BattleInfo, currTurn Turn) int {
	damage := InitialDamage
	switch currTurn {
	case PlayerTurn:
		vampireFirstAttack := BattleInfo.Enemy.Type == "Vampire" && BattleInfo.VampireFirstAttack

		if BattleInfo.PlayerAsleep {
			BattleInfo.PlayerAsleep = false
			damage = 0
		} else if vampireFirstAttack {
			BattleInfo.VampireFirstAttack = false
			damage = 0
		} else {
			if char.Weapon.Name == "NoWeapon" {
				baseDamage := 25
				strengthBonus := int(float32(char.Strength) * 0.8)
				damage = baseDamage + strengthBonus
			} else {
				baseDamage := char.Weapon.WeaponPower / 2
				strengthBonus := int(float32(char.Strength) * 0.9)
				damage = baseDamage + strengthBonus
			}

			if damage < 20 {
				damage = 20
			}
		}

	case MonsterTurn:
		if BattleInfo.Enemy.Type == "Vampire" {
			damage = vampireDamageFormula(char, BattleInfo)
		} else {
			damage = monsterDamageFormulas[BattleInfo.Enemy.Type](BattleInfo)
		}
	}

	return damage
}

func calculateLoot(enemy *Enemy, level *Level) int {
	loot := int(float32(enemy.Agility)*AgilityLoot+float32(enemy.MaxHealth)*HPLoot+float32(enemy.Strength)*StrLoot) + rand.Intn(20) + level.LevelNum*LevelLoot
	return loot
}

func hitChanceFormula(attackerAgi int, defenderAgi int) int {
	return int(float32((attackerAgi - defenderAgi - StandartAgility)) * AgilityWeight)
}

func CheckContact(char *Character, enemy *Enemy) bool {
	isContact := checkIfNeighborTile(char.Position, enemy.Position)
	if !isContact {
		isContact = (enemy.Type == "Snake" && checkIfDiagonallyNeighbourTile(char.Position, enemy.Position))
	}
	return isContact
}

func UpdateBattleStatus(char *Character, level *Level, activeBattles []BattleInfo, logger GameEventLogger) []BattleInfo {
	RemoveDeadMonsters(level)
	for i := 0; i < len(level.Enemies); i++ {
		monster := level.Enemies[i]
		if CheckContact(char, monster) && IsUniqueEnemy(monster, activeBattles) {
			activeBattles = StartBattle(monster, activeBattles)
			if logger != nil {
				logger.LogBattleEvent(BattleEvent{
					Type:      BattleStart,
					EnemyType: monster.Type,
				})
			}
		}
	}

	for i := 0; i < len(activeBattles); i++ {
		if activeBattles[i].IsFight {
			monsterDead := activeBattles[i].Enemy.Health <= 0
			lostContact := !CheckContact(char, activeBattles[i].Enemy)

			if monsterDead || lostContact {
				activeBattles = EndBattle(activeBattles, i)
				i--
			}
		}
	}
	return activeBattles
}

func IsUniqueEnemy(enemy *Enemy, activeBattles []BattleInfo) bool {
	for _, battle := range activeBattles {
		if battle.IsFight && checkEqualPosition(battle.Enemy.Position, enemy.Position) {
			return false
		}
	}
	return true
}

func RemoveDeadMonsters(level *Level) {
	aliveEnemies := make([]*Enemy, 0, len(level.Enemies))

	for i := 0; i < len(level.Enemies); i++ {
		if level.Enemies[i].Health > 0 {
			aliveEnemies = append(aliveEnemies, level.Enemies[i])
		}
	}

	level.Enemies = aliveEnemies
}

func StartBattle(enemy *Enemy, activeBattles []BattleInfo) []BattleInfo {
	newBattle := BattleInfo{
		IsFight:            true,
		Enemy:              enemy,
		VampireFirstAttack: true,
		OgreCooldown:       false,
		PlayerAsleep:       false,
	}
	return append(activeBattles, newBattle)
}

func EndBattle(activeBattles []BattleInfo, index int) []BattleInfo {
	return append(activeBattles[:index], activeBattles[index+1:]...)
}

func checkEqualPosition(firstPosition Position, secondPosition Position) bool {
	return (firstPosition.X == secondPosition.X && firstPosition.Y == secondPosition.Y)
}

func vampireDamageFormula(char *Character, battleInfo *BattleInfo) int {
	damage := int(float32(battleInfo.Enemy.Strength) * 0.2)
	hpReduction := char.RegenLimit / 50
	char.RegenLimit -= hpReduction
	if char.Health > char.RegenLimit {
		char.Health = char.RegenLimit
	}
	return damage
}

func zombieGhostDamageFormula(battleInfo *BattleInfo) int {
	return InitialDamage + int(float32(battleInfo.Enemy.Strength-StandartStrength)*StrengthWeight)
}

func ogreDamageFormula(battleInfo *BattleInfo) int {
	damage := 0
	if !battleInfo.OgreCooldown {
		damage = InitialDamage + int(float32(battleInfo.Enemy.Strength-StandartStrength)*StrengthWeight)
		battleInfo.OgreCooldown = true
	} else {
		battleInfo.OgreCooldown = false
	}
	return damage
}

func snakeDamageFormula(battleInfo *BattleInfo) int {
	if rand.Intn(100) < SleepChance {
		battleInfo.PlayerAsleep = true
	}
	return zombieGhostDamageFormula(battleInfo)
}

func checkIfNeighborTile(first, second Position) bool {
	dx := AbsInt(first.X - second.X)
	dy := AbsInt(first.Y - second.Y)
	return (dx == 1 && dy == 0) || (dx == 0 && dy == 1)
}

func checkIfDiagonallyNeighbourTile(first, second Position) bool {
	dx := AbsInt(first.X - second.X)
	dy := AbsInt(first.Y - second.Y)
	return dx == 1 && dy == 1
}

func AbsInt(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

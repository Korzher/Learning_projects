package presentation

import (
	"APG-P01/internal/datalayer"
	"APG-P01/internal/domain"
	"log"
	"math/rand"
)

func GameLoop(ui *TerminalUI, rng *rand.Rand) bool {
	ui.DrawMainMenu()

	var gameSession *domain.GameSession
	var char *domain.Character
	var level *domain.Level
	var currentLevel int
	var startRoom domain.Room

	for {
		action := ui.Input()
		if action == ActionConfirm {
			break
		}
		if action == ActionLoadGame {
			var err error
			gameSession, err = datalayer.LoadLastSession()
			if err != nil {
				gameSession = nil
			} else {
				char = gameSession.Character
				level = &gameSession.CurrentLevel
			}
			break
		}
		if action == ActionUseWeapon {
			stats, err := datalayer.BestAttempts(10)
			if err != nil {
				log.Println("Failed to load stats:", err)
			} else {
				ui.ShowLeaderboard(stats)
			}
			ui.DrawMainMenu()
			continue
		}
		if action == ActionQuit {
			return false
		}
	}

	if gameSession == nil {
		currentLevel = 1
		gameSession = domain.NewGameSession(currentLevel, rng)
		level = &gameSession.CurrentLevel

		level.GenerateEnemies(rng)
		level.GenerateItems(rng)

		startRoom = level.Rooms[level.StartRoomIndex]
		startPosition := domain.RandomPositionInRoom(startRoom, rng)
		char = domain.NewCharacter(startPosition.X, startPosition.Y)
		gameSession.Character = char

		char.Backpack = &domain.Backpack{
			Items:     make([]domain.Item, 0),
			Treasures: &domain.Loot{Value: 0},
		}
	}

	var activeBattles []domain.BattleInfo

	for {
		activeBattles = domain.UpdateBattleStatus(char, level, activeBattles, ui)

		grid := level.BuildTileMap()
		ui.DrawHUD(grid, *level, char, gameSession.FogOfWar)
		action := ui.Input()
		switch action {
		case ActionQuit:
			datalayer.SaveGame(gameSession, false)
			return false
		case ActionMoveUp:
			if domain.TryMoveCharacter(char, level, domain.Up, activeBattles, ui) {
				domain.RemoveDeadMonsters(level)
			}
		case ActionMoveDown:
			if domain.TryMoveCharacter(char, level, domain.Down, activeBattles, ui) {
				domain.RemoveDeadMonsters(level)
			}
		case ActionMoveLeft:
			if domain.TryMoveCharacter(char, level, domain.Left, activeBattles, ui) {
				domain.RemoveDeadMonsters(level)
			}
		case ActionMoveRight:
			if domain.TryMoveCharacter(char, level, domain.Right, activeBattles, ui) {
				domain.RemoveDeadMonsters(level)
			}
		case ActionUseWeapon:
			ui.UseItemOfType(char, level, domain.Weapon, "Weapon", true)
		case ActionUseFood:
			ui.UseItemOfType(char, level, domain.Food, "Food", false)
		case ActionUseElixir:
			ui.UseItemOfType(char, level, domain.Elixir, "Elixir", false)
		case ActionUseScroll:
			ui.UseItemOfType(char, level, domain.Scroll, "Scroll", false)
		}

		for i := range level.Enemies {
			if level.Enemies[i].Health > 0 {
				domain.MoveMonster(level.Enemies[i], char, level)
			}
		}

		for i := range activeBattles {
			if activeBattles[i].IsFight && activeBattles[i].Enemy.Health > 0 {
				domain.Attack(char, &activeBattles[i], domain.MonsterTurn, level, ui)
			}
		}

		char.UpdateBuffs()

		if level.IsPlayerOnExit(char) {
			currentLevel++
			won := false
			if currentLevel > 21 {
				won = true
			}
			if won {
				gameSession.GameState = domain.GameStateWon
				datalayer.SaveToLeaderboard(gameSession, true)
				return ui.DrawGameOverScreen(true, char.Backpack.Treasures.Value)
			}

			gameSession.CurrentLevel = domain.NewLevel(currentLevel, rng)
			level = &gameSession.CurrentLevel
			gameSession.FogOfWar = domain.NewFogOfWar()

			level.GenerateEnemies(rng)
			level.GenerateItems(rng)

			startRoom = level.Rooms[level.StartRoomIndex]
			char.Position = domain.RandomPositionInRoom(startRoom, rng)
			activeBattles = nil
			datalayer.SaveGame(gameSession, won)
		}
		if char.Health <= 0 {
			gameSession.GameState = domain.GameStateLost
			datalayer.SaveToLeaderboard(gameSession, false)
			return ui.DrawGameOverScreen(false, char.Backpack.Treasures.Value)
		}
	}
}

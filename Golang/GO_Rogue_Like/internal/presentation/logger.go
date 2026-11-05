package presentation

import (
	"fmt"

	"APG-P01/internal/domain"

	"github.com/gdamore/tcell/v2"
)

func (ui *TerminalUI) LogBattleEvent(event domain.BattleEvent) {
	switch event.Type {
	case domain.ItemPickedUp:
		ui.UpdateBattleLog(
			fmt.Sprintf("Item picked up: %s", event.ItemName),
			"",
		)
	case domain.BattleStart:
		ui.UpdateBattleLog(
			fmt.Sprintf("Battle started with %s!", event.EnemyType),
			"Get ready",
		)

	case domain.PlayerAttack:
		if event.Dealt > 0 {
			ui.UpdateBattleLog(
				fmt.Sprintf("Dealt %d damage %s", event.Dealt, event.EnemyType),
				"",
			)
		} else {
			ui.UpdateBattleLog(
				fmt.Sprintf("Miss on %s", event.EnemyType),
				"",
			)
		}

	case domain.MonsterAttack:
		if event.Received > 0 {
			ui.UpdateBattleLog(
				fmt.Sprintf("%s attacked!", event.EnemyType),
				fmt.Sprintf("Received %d damage", event.Received),
			)
		} else {
			ui.UpdateBattleLog(
				fmt.Sprintf("%s missed", event.EnemyType),
				"",
			)
		}

	case domain.EnemyDefeated:
		ui.UpdateBattleLog(
			fmt.Sprintf("%s has been slain!", event.EnemyType),
			fmt.Sprintf("Get loot: %d", event.Loot),
		)
	}
}

func (ui *TerminalUI) LogItemEvent(event domain.ItemEvent) {
	switch event.Type {
	case domain.FoodUsed:
		ui.UpdateBattleLog(fmt.Sprintf("Consumed: %s", event.ItemName), event.Effect)
	case domain.ElixirUsed:
		ui.UpdateBattleLog(fmt.Sprintf("Elixir drinked: %s", event.ItemName), event.Effect)
	case domain.ScrollUsed:
		ui.UpdateBattleLog(fmt.Sprintf("Scroll used: %s", event.ItemName), event.Effect)
	case domain.WeaponEquipped:
		ui.UpdateBattleLog(fmt.Sprintf("Equiped: %s", event.ItemName), event.Effect)
	}
}

func (ui *TerminalUI) DrawBattleLog() {
	ui.DrawText(2, 40, "Battle log", tcell.StyleDefault.Foreground((tcell.ColorWhite)))
	if ui.battleLog[0] != "" {
		ui.DrawText(2, 41, ui.battleLog[0], tcell.StyleDefault.Foreground(tcell.ColorWhite))
	}
	if ui.battleLog[1] != "" {
		ui.DrawText(2, 42, ui.battleLog[1], tcell.StyleDefault.Foreground(tcell.ColorWhite))
	}
}

func (ui *TerminalUI) LogBattleStart(enemy string) {
	ui.UpdateBattleLog(fmt.Sprintf("Battle started with %s!", enemy), "Get ready")
}

func (ui *TerminalUI) LogBattleDamage(dealt int, received int, enemy string) {
	line1 := ""
	line2 := ""

	if dealt > 0 && received > 0 {
		line1 = fmt.Sprintf("You dealt %d damage to %s", dealt, enemy)
		line2 = fmt.Sprintf("Received %d damage", received)
	} else if dealt > 0 {
		line1 = fmt.Sprintf("You dealt %d damage to %s", dealt, enemy)
	} else if received > 0 {
		line1 = fmt.Sprintf("Received %d damage from %s", received, enemy)
	} else {
		line1 = "Miss"
	}

	ui.UpdateBattleLog(line1, line2)
}

func (ui *TerminalUI) LogItemUsed(itemName string, effect string) {
	ui.UpdateBattleLog(fmt.Sprintf("Used: %s", itemName), effect)
}

func (ui *TerminalUI) LogItemEquipped(itemName string, effect string) {
	ui.UpdateBattleLog(fmt.Sprintf("Equiped: %s", itemName), effect)
}

func (ui *TerminalUI) LogElixirEnd(statName string, oldValue int, newValue int) {
	ui.UpdateBattleLog("Elixir effect is gone",
		fmt.Sprintf("%s: %d → %d", statName, oldValue, newValue))
}

func (ui *TerminalUI) LogBattleEnd(enemyType string, victory bool) {
	if victory {
		ui.UpdateBattleLog(fmt.Sprintf("%s slain!", enemyType), "You won")
	}
}

func (ui *TerminalUI) LogEnemyDeath(enemyType string, loot int) {
	ui.UpdateBattleLog(fmt.Sprintf("%s has been slain!", enemyType),
		fmt.Sprintf("Loot received: %d", loot))
}

package presentation

import (
	"APG-P01/internal/domain"
	"fmt"

	"github.com/gdamore/tcell/v2"
)

func (ui *TerminalUI) DrawControl(char *domain.Character, level domain.Level) {
	ui.DrawText(GameWidth+1, 2, " Achieve exit to", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 3, "proceed in dungeons", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 5, "Controls", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 6, "W - to move Up", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 7, "A - to move Left", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 8, "S - to move Down", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 9, "D - to move Right", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 10, "E - to use Scroll", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 11, "H - to use Weapon", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 12, "J - to use Food", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 13, "K - to use Elixir", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 14, "Q - to save and quit", tcell.StyleDefault)
	ui.DrawText(GameWidth+1, 16, "Current Run Stats", tcell.StyleDefault)
	loot := fmt.Sprintf("Loot collected: %d", char.Backpack.Treasures.Value)
	ui.DrawText(GameWidth+1, 17, loot, tcell.StyleDefault)
	levels := fmt.Sprintf("Levels Comleted: %d", level.LevelNum-1)
	ui.DrawText(GameWidth+1, 18, levels, tcell.StyleDefault)
	enemies := fmt.Sprintf("Enemies Defeated: %d", char.EnemiesDefeated)
	ui.DrawText(GameWidth+1, 19, enemies, tcell.StyleDefault)
	food := fmt.Sprintf("Food Consumed: %d", char.FoodConsumed)
	ui.DrawText(GameWidth+1, 20, food, tcell.StyleDefault)
	elixirs := fmt.Sprintf("Elixirs Used: %d", char.ElixirsUsed)
	ui.DrawText(GameWidth+1, 21, elixirs, tcell.StyleDefault)
	scrolls := fmt.Sprintf("Scrolls Read: %d", char.ScrollsRead)
	ui.DrawText(GameWidth+1, 22, scrolls, tcell.StyleDefault)
	dealt := fmt.Sprintf("Attacks Dealt: %d", char.AttackDealt)
	ui.DrawText(GameWidth+1, 23, dealt, tcell.StyleDefault)
	received := fmt.Sprintf("Attacks Received: %d", char.AttackReceived)
	ui.DrawText(GameWidth+1, 24, received, tcell.StyleDefault)
	steps := fmt.Sprintf("Steps Taken: %d", char.StepsTaken)
	ui.DrawText(GameWidth+1, 25, steps, tcell.StyleDefault)
}

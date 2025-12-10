package presentation

import (
	"APG-P01/internal/datalayer"
	"fmt"

	"github.com/gdamore/tcell/v2"
)

func (ui *TerminalUI) ShowLeaderboard(stats []datalayer.LevelStats) error {
	ui.screen.Clear()

	colorStyle := tcell.ColorWhite
	defaultStyle := tcell.StyleDefault.
		Foreground(tcell.ColorWhite).
		Background(tcell.ColorBlack)

	ui.drawTextCentered(0, "Leaaderboard", colorStyle)
	ui.drawTextCentered(2, "Press Enter to get back to menu", colorStyle)

	if len(stats) == 0 {
		ui.drawTextCentered(5, "There is no registered tries", colorStyle)
		ui.screen.Show()
		for {
			action := ui.Input()
			if action == ActionConfirm {
				break
			}
		}
		return nil
	}

	y := 4

	ui.DrawText(2, y, "№ Won  Loot  Level Enemies Food Elixirs Scrolls AttacksDealt AttacksReceived   Steps   Date", defaultStyle)
	ui.DrawText(2, y+1, "-----------------------------------------------------------------------------------------------", defaultStyle)

	for i, stat := range stats {
		if i >= 10 {
			break
		}

		dateStr := stat.FinishedAt.Format("02.01")

		result := "-"
		if stat.IsWin {
			result = "+"
		}

		row := fmt.Sprintf("%-2d %3s %7d %5d %7d %4d %7d %7d %12d %15d %6d %8s",
			i+1, result, stat.Treasures, stat.LevelReached,
			stat.EnemiesDefeated, stat.FoodConsumed, stat.ElixirsUsed, stat.ScrollsRead, stat.AttackDealt, stat.AttackReceived, stat.StepsTaken, dateStr)

		ui.DrawText(2, y+2+i, row, defaultStyle)
	}

	ui.screen.Show()

	for {
		action := ui.Input()
		if action == ActionConfirm {
			break
		}
	}

	return nil
}

package presentation

import (
	"APG-P01/internal/domain"
)

func (ui *TerminalUI) DrawHUD(grid domain.MapGrid, level domain.Level, character *domain.Character, fog *domain.FogOfWar) {
	enemies := level.Enemies
	items := level.Items
	ui.screen.Clear()
	ui.drawFrame(0, 0, ScreenWidth, ScreenHeight)
	fog.UpdateVisibility(character.Position, &level, grid)
	ui.DrawLevel(grid, enemies, items, character, fog)
	ui.DrawStats(character, level)
	ui.DrawBattleLog()
	ui.DrawControl(character, level)
	ui.screen.Show()
}

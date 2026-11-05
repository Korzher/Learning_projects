package presentation

import (
	"APG-P01/internal/domain"
	"fmt"

	"github.com/gdamore/tcell/v2"
)

func (ui *TerminalUI) DrawStats(character *domain.Character, level domain.Level) {
	backpackInfo := ""
	if character.Backpack != nil {
		backpackInfo = fmt.Sprintf("Items: %d/%d", len(character.Backpack.Items), domain.MaxBackpackSize)
	}

	statusBar := fmt.Sprintf("Level:%v Treasures:%v HP:%v/%v Agility:%v Strength:%v %s", level.LevelNum, character.Backpack.Treasures.Value, character.Health, character.RegenLimit, character.Agility, character.Strength, backpackInfo)
	ui.DrawText(2, GameHeight+1, statusBar, tcell.StyleDefault)
}

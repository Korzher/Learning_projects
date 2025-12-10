package presentation

import (
	"APG-P01/internal/domain"
	"fmt"

	"github.com/gdamore/tcell/v2"
)

func (ui *TerminalUI) DrawGameOverScreen(isWin bool, score int) bool {
	ui.screen.Clear()
	ui.drawFrame(0, 0, domain.MapWidth, domain.MapHeight)
	message := "You Lost!"
	color := tcell.ColorRed
	if isWin {
		message = "You won!"
		color = tcell.ColorGreen
	}

	ui.drawTextCentered(ScreenHeight/2-2, message, color)
	ui.drawTextCentered(ScreenHeight/2, fmt.Sprintf("Loot collected: %d", score), tcell.ColorWhite)
	ui.drawTextCentered(ScreenHeight/2+2, "Press Enter to enter Main Menu", tcell.ColorGray)
	ui.drawTextCentered(ScreenHeight/2+3, "Press Q to exit", tcell.ColorGray)

	ui.screen.Show()
	for {
		action := ui.Input()
		switch action {
		case ActionQuit:
			return false
		case ActionConfirm:
			return true
		default:
			continue
		}
	}

}

func (ui *TerminalUI) drawTextCentered(y int, text string, color tcell.Color) {
	x := (ScreenWidth - len(text)) / 2
	for i, ch := range text {
		ui.screen.SetContent(x+i, y, ch, nil, tcell.StyleDefault.Foreground(color))
	}
}

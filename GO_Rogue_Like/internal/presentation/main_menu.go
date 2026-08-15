package presentation

import (
	"github.com/gdamore/tcell/v2"
)


func (ui *TerminalUI) DrawMainMenu() {
	ui.screen.Clear()

	ui.drawFrame(0, 0, ScreenWidth, ScreenHeight)

	centerX := GameWidth / 2
	centerY := GameHeight / 2
	titleX := centerX - 2
	titleY := centerY - 3
	startX := centerX - 12
	startY := centerY
	loadX := centerX - 13
	loadY := centerY + 2
	statsX := centerX - 11
	statsY := centerY + 4
	quitX := centerX - 7
	quitY := centerY + 6

	style := tcell.StyleDefault.
		Foreground(tcell.ColorWhite).
		Background(tcell.ColorBlack)

	ui.DrawText(titleX, titleY, "ROGUE", style)
	ui.DrawText(startX, startY, "Press Enter to start a game", style)
	ui.DrawText(loadX, loadY, "Press L to load your last game", style)
	ui.DrawText(statsX, statsY, "Press H to see Highscores", style)
	ui.DrawText(quitX, quitY, "Press Q to quit", style)

	ui.screen.Show()
}


func (ui *TerminalUI) DrawText(x, y int, text string, style tcell.Style) {
	for i, ch := range text {
		ui.screen.SetContent(x+i, y, ch, nil, style)
	}
}

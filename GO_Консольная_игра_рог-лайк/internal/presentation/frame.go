package presentation

import (
	"github.com/gdamore/tcell/v2"
)


func (ui *TerminalUI) drawFrame(x, y, width, height int) {
	style := tcell.StyleDefault.
		Foreground(tcell.ColorWhite).
		Background(tcell.ColorBlack)

	ui.screen.SetContent(x, y, '┌', nil, style)
	ui.screen.SetContent(x+width-1, y, '┐', nil, style)
	ui.screen.SetContent(x, y+height-1, '└', nil, style)
	ui.screen.SetContent(x+width-1, y+height-1, '┘', nil, style)

	for i := 1; i < width-1; i++ {
		ui.screen.SetContent(x+i, y, '─', nil, style)
		ui.screen.SetContent(x+i, y+height-1, '─', nil, style)
	}

	for i := 1; i < height-1; i++ {
		ui.screen.SetContent(x, y+i, '│', nil, style)
		ui.screen.SetContent(x+width-1, y+i, '│', nil, style)
	}
}

package presentation

import (
	"fmt"

	"github.com/gdamore/tcell/v2"
)


func NewTerminalUI() (*TerminalUI, error) {
	screen, err := tcell.NewScreen()
	if err != nil {
		return nil, err
	}

	if err := screen.Init(); err != nil {
		return nil, err
	}

	width, height := screen.Size()

	if width < ScreenWidth || height < ScreenHeight {
		screen.Fini()
		return nil, fmt.Errorf("окно терминала слишком маленькое для отображения игры: %dx%d. пожайлуйста, растяните терминал хотя бы до 80x40", width, height)
	}

	return &TerminalUI{
		screen:    screen,
		width:     width,
		height:    height,
		battleLog: [2]string{"", ""},
		logTimer:  [2]int{0, 0},
	}, nil
}


func (ui *TerminalUI) Close() {
	if ui.screen != nil {
		ui.screen.Fini()
	}
}

func (ui *TerminalUI) UpdateBattleLog(line1, line2 string) {
	ui.battleLog[0] = line1
	ui.battleLog[1] = line2
	ui.logTimer[0] = 1
	ui.logTimer[1] = 1
}

func (ui *TerminalUI) UpdateBattleLogLine(lineNum int, message string) {
	if lineNum >= 0 && lineNum <= 2 {
		ui.battleLog[lineNum] = message
		ui.logTimer[lineNum] = 1
	}
}

func (ui *TerminalUI) UpdateLogTimers() {
	for i := 0; i < 2; i++ {
		if ui.logTimer[i] > 0 {
			ui.logTimer[i]--
			if ui.logTimer[i] == 0 {
				ui.battleLog[i] = ""
			}
		}
	}
}

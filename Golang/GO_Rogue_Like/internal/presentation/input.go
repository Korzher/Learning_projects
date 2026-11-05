package presentation

import (
	"github.com/gdamore/tcell/v2"
)

func (ui *TerminalUI) Input() Action {
	for {
		event := ui.screen.PollEvent()
		switch event := event.(type) {
		case *tcell.EventKey:
			switch event.Key() {
			case tcell.KeyEnter:
				return ActionConfirm
			case tcell.KeyEscape:
				return ActionQuit
			}

			switch event.Rune() {
			case ' ':
				return ActionNone
			case 'w', 'W':
				return ActionMoveUp
			case 's', 'S':
				return ActionMoveDown
			case 'a', 'A':
				return ActionMoveLeft
			case 'd', 'D':
				return ActionMoveRight
			case 'h', 'H':
				return ActionUseWeapon
			case 'j', 'J':
				return ActionUseFood
			case 'k', 'K':
				return ActionUseElixir
			case 'e', 'E':
				return ActionUseScroll
			case 'l', 'L':
				return ActionLoadGame
			case 'q', 'Q':
				return ActionQuit
			}
		}
	}
}

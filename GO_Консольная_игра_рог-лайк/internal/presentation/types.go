package presentation

import (
	"github.com/gdamore/tcell/v2"
)

type TerminalUI struct {
	screen    tcell.Screen
	width     int
	height    int
	battleLog [2]string
	logTimer  [2]int
}

type Action int 

const (
	ActionNone      Action = iota //Space - Пропуск тика
	ActionMoveUp                  // "W"
	ActionMoveDown                // "S"
	ActionMoveLeft                // "A"
	ActionMoveRight               // "D"
	ActionLoadGame                // "L"
	ActionUseWeapon               // "H"
	ActionUseFood                 // "J"
	ActionUseElixir               // "K"
	ActionUseScroll               // "E"
	ActionQuit                    // "Q"
	ActionConfirm                 // "Enter"
	ScreenWidth     = 80
	ScreenHeight    = 40
	GameWidth       = 80
	GameHeight      = 36
	HUDHeight       = 4
)

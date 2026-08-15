package presentation

import (
	"APG-P01/internal/domain"
	"fmt"

	"github.com/gdamore/tcell/v2"
)

func (ui *TerminalUI) DrawInventory(invType string, items []domain.Item) int {
	overlayStyle := tcell.StyleDefault.
		Background(tcell.NewRGBColor(50, 50, 50))

	title := fmt.Sprintf("Select %s (1-9):", invType)
	if invType == "Weapon" {
		title = "Select Weapon (0-9, 0=unequip):"
	}

	windowX := 20
	windowY := 10
	windowWidth := 40
	windowHeight := 15

	for y := windowY; y < windowY+windowHeight; y++ {
		for x := windowX; x < windowX+windowWidth; x++ {
			ui.screen.SetContent(x, y, ' ', nil, overlayStyle)
		}
	}

	ui.drawFrame(windowX, windowY, windowWidth, windowHeight)

	titleX := windowX + (windowWidth-len(title))/2
	ui.DrawText(titleX, windowY+1, title, tcell.StyleDefault.Foreground(tcell.ColorWhite))

	for i, item := range items {
		if i >= 9 {
			break
		}
		line := fmt.Sprintf("%d. %s", i+1, item.Name)
		ui.DrawText(windowX+2, windowY+3+i, line, tcell.StyleDefault.Foreground(tcell.ColorWhite))
	}

	for i := len(items); i < 9; i++ {
		line := fmt.Sprintf("%d. [Empty]", i+1)
		ui.DrawText(windowX+2, windowY+3+i, line, tcell.StyleDefault.Foreground(tcell.ColorGray))
	}

	if invType == "Weapon" {
		line := "0.Unequip current weapon"
		ui.DrawText(windowX+2, windowY+3+9, line, tcell.StyleDefault.Foreground(tcell.ColorGray))
	}
	ui.screen.Show()
	return ui.waitForInventorySelection(len(items), invType == "Weapon")
}

func (ui *TerminalUI) waitForInventorySelection(itemCount int, allowUnequip bool) int {
	for {
		event := ui.screen.PollEvent()
		switch event := event.(type) {
		case *tcell.EventKey:
			if event.Key() == tcell.KeyEscape {
				return -1
			}

			if event.Rune() >= '1' && event.Rune() <= '9' {
				index := int(event.Rune() - '1')
				if index < itemCount {
					return index
				}
			}

			if allowUnequip && event.Rune() == '0' {
				return -2
			}
			return -1
		}
	}
}

func (ui *TerminalUI) FilterItemsByType(items []domain.Item, kind domain.ConsumableType) []domain.Item {
	var filtered []domain.Item
	for _, item := range items {
		if item.Kind == kind {
			filtered = append(filtered, item)
		}
	}
	return filtered
}

func (ui *TerminalUI) FindItemIndex(items []domain.Item, target domain.Item) int {
	for i, item := range items {
		if item.Name == target.Name && item.Kind == target.Kind {
			return i
		}
	}
	return -1
}

func (ui *TerminalUI) UseItemOfType(
	char *domain.Character,
	level *domain.Level,
	kind domain.ConsumableType,
	typeName string,
	allowUnequip bool,
) bool {
	if char.Backpack == nil {
		return false
	}

	items := ui.FilterItemsByType(char.Backpack.Items, kind)
	selected := ui.DrawInventory(typeName, items)

	if selected == -2 && allowUnequip {
		char.ChangeWeapon(domain.Item{Kind: domain.None}, level)
		return true
	}

	if selected >= 0 && selected < len(items) {
		target := items[selected]
		index := ui.FindItemIndex(char.Backpack.Items, target)
		if index != -1 {
			char.UseItem(index, level, ui)
			return true
		}
	}

	return false
}

package presentation

import (
	"APG-P01/internal/domain"

	"github.com/gdamore/tcell/v2"
)

func (ui *TerminalUI) DrawLevel(grid domain.MapGrid, enemies []*domain.Enemy, items []domain.Item, character *domain.Character, fog *domain.FogOfWar) {

	for y := 0; y < domain.MapHeight; y++ {
		for x := 0; x < domain.MapWidth; x++ {
			visibility := fog.Visibility[y][x]
			if visibility == domain.VisibilityUnexplored {
				ui.screen.SetContent(x, y, ' ', nil, tcell.StyleDefault.Background(tcell.ColorBlack))
				continue
			}
			var symbol rune
			var style tcell.Style
			var fgColor tcell.Color
			var bgColor tcell.Color = tcell.ColorBlack

			switch visibility {
			case domain.VisibilityExplored:
				switch grid[y][x] {
				case domain.TileWall:
					fgColor = tcell.ColorDarkGray
				case domain.TileRoom:
					fgColor = tcell.ColorDarkSlateGray
				case domain.TileCorridor:
					fgColor = tcell.ColorDarkSlateGray
				case domain.TileExit:
					fgColor = tcell.ColorDarkGreen
				default:
					fgColor = tcell.ColorDarkGray
				}
			case domain.VisibilityVisible:
				switch grid[y][x] {
				case domain.TileWall:
					fgColor = tcell.ColorLightGray
				case domain.TileRoom:
					fgColor = tcell.ColorLightGray
				case domain.TileCorridor:
					fgColor = tcell.ColorLightGray
				case domain.TileExit:
					fgColor = tcell.ColorGreen
				default:
					fgColor = tcell.ColorWhite
				}
			}

			switch grid[y][x] {
			case domain.TileWall:
				symbol = '#'
			case domain.TileRoom:
				symbol = '.'
			case domain.TileCorridor:
				symbol = '='
			case domain.TileExit:
				symbol = '%'
			default:
				symbol = ' '
			}

			style = tcell.StyleDefault.
				Foreground(fgColor).
				Background(bgColor)

			ui.screen.SetContent(x, y, symbol, nil, style)
		}
	}

	for _, item := range items {
		pos := item.Position
		if fog.Visibility[pos.Y][pos.X] == domain.VisibilityVisible {
			var symbol rune
			var style tcell.Style

			switch item.Kind {
			case domain.Food:
				symbol = ':'
				style = tcell.StyleDefault.
					Foreground(tcell.ColorBrown).
					Background(tcell.ColorBlack)
			case domain.Elixir:
				symbol = '!'
				style = tcell.StyleDefault.
					Foreground(tcell.ColorPink).
					Background(tcell.ColorBlack)
			case domain.Weapon:
				symbol = ')'
				style = tcell.StyleDefault.
					Foreground(tcell.ColorOrange).
					Background(tcell.ColorBlack)
			case domain.Scroll:
				symbol = '?'
				style = tcell.StyleDefault.
					Foreground(tcell.ColorGray).
					Background(tcell.ColorBlack)
			default:
				continue
			}

			ui.screen.SetContent(item.Position.X, item.Position.Y, symbol, nil, style)
		}
	}

	for _, enemy := range enemies {
		if enemy.State != domain.StateAlive || !enemy.IsVisible {
			continue
		}

		pos := enemy.Position
		if fog.Visibility[pos.Y][pos.X] == domain.VisibilityVisible {
			var symbol rune
			var style tcell.Style

			switch enemy.Type {
			case "Zombie":
				symbol = 'z'
				style = tcell.StyleDefault.
					Foreground(tcell.ColorGreen).
					Background(tcell.ColorBlack)
			case "Vampire":
				symbol = 'v'
				style = tcell.StyleDefault.
					Foreground(tcell.ColorRed).
					Background(tcell.ColorBlack)
			case "Ghost":
				symbol = 'g'
				style = tcell.StyleDefault.
					Foreground(tcell.ColorWhite).
					Background(tcell.ColorBlack)
			case "Ogre":
				symbol = 'O'
				style = tcell.StyleDefault.
					Foreground(tcell.ColorYellow).
					Background(tcell.ColorBlack)
			case "Snake":
				symbol = 's'
				style = tcell.StyleDefault.
					Foreground(tcell.ColorWhite).
					Background(tcell.ColorBlack)
			default:
				symbol = 'E'
				style = tcell.StyleDefault.
					Foreground(tcell.ColorWhite).
					Background(tcell.ColorBlack)
			}

			ui.screen.SetContent(enemy.Position.X, enemy.Position.Y, symbol, nil, style)
		}
	}

	if character != nil {
		playerSymbol := '@'
		playerStyle := tcell.StyleDefault.
			Foreground(tcell.ColorWhite).
			Background(tcell.ColorBlack)

		ui.screen.SetContent(
			character.Position.X,
			character.Position.Y,
			playerSymbol, nil, playerStyle)
	}

	ui.drawFrame(0, 0, domain.MapWidth, domain.MapHeight)

	ui.screen.Show()
}

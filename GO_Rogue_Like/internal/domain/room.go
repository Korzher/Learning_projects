package domain

type Room struct {
	TopLeft Position
	Width   int
	Height  int
}

func boundsForSector(sx, sy int) (minX, minY, maxX, maxY int) {
	sectorWidth := MapWidth / SectorX
	sectorHeight := MapHeight / SectorY

	minX = sx*sectorWidth + 2
	minY = sy*sectorHeight + 2

	if sx == SectorX-1 {
		maxX = MapWidth - 2
	} else {
		maxX = minX + sectorWidth - 2
	}

	if sy == SectorY-1 {
		maxY = MapHeight - 2
	} else {
		maxY = minY + sectorHeight - 2
	}

	return
}

func (r Room) Center() Position {
	p := Position{}
	p.X = r.TopLeft.X + r.Width/2
	p.Y = r.TopLeft.Y + r.Height/2
	return p
}

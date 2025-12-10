package domain

type Backpack struct {
	Items     []Item
	Weight    int
	Treasures *Loot
}

type Loot struct {
	Value int
}

func (b *Backpack) AddItem(item Item) bool {
	current := 0
	for _, i := range b.Items {
		if i.Kind == item.Kind {
			current++
		}
	}

	if current >= MaxType {
		return false
	}

	b.Items = append(b.Items, item)
	return true
}

func (b *Backpack) RemoveAt(index int) {
	if index < 0 || index >= len(b.Items) {
		return
	}

	last := len(b.Items) - 1
	b.Items[index] = b.Items[last]
	b.Items = b.Items[:last]
}

func (l *Level) FindItemAt(pos Position) int {
	for i, it := range l.Items {
		if it.Position.X == pos.X && it.Position.Y == pos.Y {
			return i
		}
	}
	return -1
}

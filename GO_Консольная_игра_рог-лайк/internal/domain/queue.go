package domain

type Queue struct {
	items []Position
}

func CreateQueue() *Queue {
	return &Queue{items: make([]Position, 0)}
}

func (q *Queue) Enqueue(pos Position) {
	q.items = append(q.items, pos)
}

func (q *Queue) Dequeue() Position {
	if len(q.items) == 0 {
		return Position{}
	}
	item := q.items[0]
	q.items = q.items[1:]
	return item
}

func (q *Queue) IsEmpty() bool {
	return len(q.items) == 0
}

func (q *Queue) Free() {
	q.items = nil
}

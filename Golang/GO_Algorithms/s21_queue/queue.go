package s21_queue

import "errors"

// Queue — самописная очередь
type s21_Queue struct {
	data []int
}

// Queue — создание пустой очереди
func Queue() *s21_Queue {
	return &s21_Queue{data: []int{}}
}

func (q *s21_Queue) Push(value int) {
	q.data = append(q.data, value)
}

func (q *s21_Queue) Pop() (int, error) {
	if len(q.data) == 0 {
		return 0, errors.New("queue is empty")
	}
	v := q.data[0]
	q.data = q.data[1:]
	return v, nil
}

func (q *s21_Queue) Front() (int, error) {
	if len(q.data) == 0 {
		return 0, errors.New("queue is empty")
	}
	return q.data[0], nil
}

func (q *s21_Queue) Back() (int, error) {
	if len(q.data) == 0 {
		return 0, errors.New("queue is empty")
	}
	return q.data[len(q.data)-1], nil
}

func (q *s21_Queue) IsEmpty() bool {
	return len(q.data) == 0
}

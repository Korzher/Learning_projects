package s21_queue

type Queuer interface {
	Queue() *s21_Queue
	Push(int)
	Pop() (int, error)
	Front() (int, error)
	Back() (int, error)
	IsEmpty() bool
}

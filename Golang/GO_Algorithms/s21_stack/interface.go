package s21_stack

type Stacker interface {
	Stack() *s21_Stack
	Push(int)
	Pop() (int, error)
	Top() (int, error)
	IsEmpty() bool
}

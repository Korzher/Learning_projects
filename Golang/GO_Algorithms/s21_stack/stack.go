package s21_stack

import "errors"

// Stack — самописный стек
type s21_Stack struct {
	data []int
}

// Stack — создание пустого стека
func Stack() *s21_Stack {
	return &s21_Stack{data: []int{}}
}

func (s *s21_Stack) Push(value int) {
	s.data = append(s.data, value)
}

func (s *s21_Stack) Pop() (int, error) {
	if len(s.data) == 0 {
		return 0, errors.New("stack is empty")
	}
	v := s.data[len(s.data)-1]
	s.data = s.data[:len(s.data)-1]
	return v, nil
}

func (s *s21_Stack) Top() (int, error) {
	if len(s.data) == 0 {
		return 0, errors.New("stack is empty")
	}
	return s.data[len(s.data)-1], nil
}

func (s *s21_Stack) IsEmpty() bool {
	return len(s.data) == 0
}

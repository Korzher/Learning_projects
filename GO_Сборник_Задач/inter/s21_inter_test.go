package main

import (
	"reflect"
	"testing"
)

func TestIntersect(t *testing.T) {
	tests := []struct {
		name        string
		firstInput  []int
		secondInput []int
		expected    []int
	}{
		{"Обычное поведение", []int{1, 2, 3, 4, 5, 4, 5}, []int{4, 5, 6, 7, 8}, []int{4, 5}},
		{"Нет пересечений", []int{1, 2, 3, 4}, []int{5, 6, 7, 8}, []int{}},
		{"Одно пересечение", []int{1, 2, 3, 4}, []int{6, 8, 4}, []int{4}},
		{"Повторяющиеся числа", []int{7, 3, 4, 5, 2, 3}, []int{7, 3, 3, 8}, []int{7, 3, 3}},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			result := compareLists(test.firstInput, test.secondInput)
			if !reflect.DeepEqual(result, test.expected) {
				t.Errorf("compareLists(%v, %v) does not match expected %v, got %v",
					test.firstInput, test.secondInput, test.expected, result)
			}
		})
	}
}

package main

import (
	"reflect"
	"testing"
)

func TestSortByFrequency(t *testing.T) {
	tests := []struct {
		name     string
		input    string
		k        int
		expected []string
	}{
		{"Обычное поведение", "aa bb cc aa cc cc cc aa ab ac bb", 3, []string{"cc", "aa", "bb"}},
		{"Пустая строка", "", 3, []string{}},
		{"Количество элементов меньше К", "aa bb aa cc aa", 5, []string{"aa", "bb", "cc"}},
		{"К равно нулю", "aa bb cc", 0, []string{}},
		{"К равно единице", "aa bb cc aa", 1, []string{"aa"}},
		{"Слова с одинаковой частотой", "aa bb cc dd", 2, []string{"aa", "bb"}},
		{"Большие и маленькие буквы", "aa AA aa AA", 2, []string{"AA", "aa"}},
		{"Много пробелов", "aa  bb   aa    bb   cc", 3, []string{"aa", "bb", "cc"}},
		{"Слова с числами", "a1 b2 a1 a1 b2 c3", 2, []string{"a1", "b2"}},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			result := sortByFrequency(test.input, test.k)
			if !reflect.DeepEqual(result, test.expected) {
				t.Errorf("sortByFrequency(%v, %v) does not match expected %v, got %v",
					test.input, test.k, test.expected, result)
			}
		})
	}
}

package main

import (
	"math"
	"testing"
)

func TestCalculate(t *testing.T) {
	tests := []struct {
		name     string
		left     float64
		operator string
		right    float64
		expected float64
	}{
		{"Сложение", 5, "+", 3, 8},
		{"Вычитание", 8, "-", 3, 5},
		{"Умножение", 4, "*", 3, 12},
		{"Деление", 6, "/", 3, 2},
		{"Неправильно введен оператор", 5, "^", 4, 0},
		{"Деление на ноль", 6, "/", 0, 0},
		{"Десятичные", 4.5, "+", 5.5, 10.0},
		{"Десятичные с точностью 3 знака", 4.324, "+", 5.137, 9.461},
		{"Отрицательные числа", -3, "+", -2, -5},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			result := calculate(test.left, test.operator, test.right)
			if math.Abs(result-test.expected) > 1e-12 {
				t.Errorf("calculate(%.3f, %s, %.3f) = %.3f, expected %.3f",
					test.left, test.operator, test.right, result, test.expected)
			}
		})
	}
}

package main

import (
	"fmt"
	"strconv"
)

func main() {
	var operator string
	var leftOperand, rightOperand float64

	leftOperand = getOperand("left")
	operator = getOperator()
	rightOperand = getOperand("right")
	calculate(leftOperand, operator, rightOperand)
}

func getOperand(side string) float64 {
	var input string
	var value float64
	for {
		fmt.Printf("Input %s operand\n", side)
		fmt.Scan(&input)
		var err error
		value, err = strconv.ParseFloat(input, 64)
		if err == nil {
			break
		}
		fmt.Println("Invalid input")
	}
	return value
}

func getOperator() string {
	var operator string
	for {
		fmt.Println("Input operator")
		fmt.Scan(&operator)
		if operator == "+" || operator == "-" || operator == "*" || operator == "/" {
			break
		}
		fmt.Println("Invalid operator")
	}
	return operator
}

func calculate(leftOperand float64, operator string, rightOperand float64) float64 {
	var result float64
	switch operator {
	case "+":
		result = leftOperand + rightOperand
	case "-":
		result = leftOperand - rightOperand
	case "*":
		result = leftOperand * rightOperand
	case "/":
		if rightOperand == 0 {
			fmt.Println("Division by zero")
			return 0
		}
		result = leftOperand / rightOperand
	}
	fmt.Printf("%.3f\n", result)
	return result
}

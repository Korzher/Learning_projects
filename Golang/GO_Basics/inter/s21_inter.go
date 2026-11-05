package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	firstInput, err := readNumbers()
	if err != nil {
		fmt.Println("Invalid Input")
		return
	}
	secondInput, err := readNumbers()
	if err != nil {
		fmt.Println("Invalid Input")
		return
	}
	result := compareLists(firstInput, secondInput)
	if len(result) == 0 {
		fmt.Println("Empty intersection")
	} else {
		fmt.Println(result)
	}
}

func readNumbers() ([]int, error) {
	var result []int
	fmt.Println("Enter list of numbers:")
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	input := scanner.Text()
	for _, word := range strings.Fields(input) {
		num, err := strconv.Atoi(word)
		if err != nil {
			return nil, err
		}
		result = append(result, num)
	}
	return result, nil
}

func compareLists(firstInput []int, secondInput []int) []int {
	count := make(map[int]int)

	for _, num := range secondInput {
		count[num]++
	}

	result := make([]int, 0)

	for _, num := range firstInput {
		if count[num] > 0 {
			result = append(result, num)
			count[num]--
		}
	}

	return result
}

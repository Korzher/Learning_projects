package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	input, k := readInput()
	result := sortByFrequency(input, k)
	fmt.Println(result)
}

func readInput() (string, int) {
	var k int
	scanner := bufio.NewScanner(os.Stdin)

	fmt.Println("Input words to sort")
	scanner.Scan()
	input := scanner.Text()
	fmt.Println("Input K")
	scanner.Scan()
	for {
		var err error
		k, err = strconv.Atoi(scanner.Text())
		if err != nil {
			fmt.Println("Invalid k, try again with a number")
			scanner.Scan()
			continue
		}
		break
	}
	return input, k
}

func sortByFrequency(input string, k int) []string {
	wordCount := make(map[string]int)
	for _, word := range strings.Fields(input) {
		wordCount[word]++
	}
	result := make([]string, 0, k)
	for i := 0; i < k && len(wordCount) > 0; i++ {
		maxWord := ""
		maxCount := -1

		for word, count := range wordCount {
			if count > maxCount || (count == maxCount && word < maxWord) {
				maxCount = count
				maxWord = word
			}
		}

		if maxWord != "" {
			result = append(result, maxWord)
			delete(wordCount, maxWord)
		}
	}
	return result
}

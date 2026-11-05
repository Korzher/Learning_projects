package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"sort"
	"strings"
)

type visit struct {
	name           string
	specialization string
	date           string
}

type PatientNotFoundError struct{}

func (e PatientNotFoundError) Error() string {
	return "patient not found"
}

func main() {
	visits := make([]visit, 0)
	for {
		input := scanCommand()
		switch input {
		case "Save":
			saveCommand(&visits)
		case "GetHistory":
			err := getHistoryCommand(visits)
			if err != nil {
				fmt.Println(err)
			}
		case "GetLastVisit":
			err := getLastVisitCommand(visits)
			if err != nil {
				fmt.Println(err)
			}
		case "Exit":
			return
		default:
			fmt.Println("Неверная команда")
		}
	}
}

func scanCommand() string {
	fmt.Println("Введите команду:")
	fmt.Println("Save - Сохранить информацию о посетителе")
	fmt.Println("GetHistory - Получить историю посещений по ФИО")
	fmt.Println("GetLastVisit - Получить последнюю информацию о посещении")
	fmt.Println("Exit - Выход")
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	return scanner.Text()
}

func saveCommand(visits *[]visit) {
	var date string
	fmt.Println("Введите ФИО через пробел:")
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	name := strings.TrimSpace(scanner.Text())
	fmt.Println("Введите специализацию врача:")
	scanner.Scan()
	specialization := strings.ToLower(strings.TrimSpace(scanner.Text()))
	fmt.Println("Введите дату визита в формате YYYY-MM-DD:")
	for {
		scanner.Scan()
		date = scanner.Text()
		if !isValidDate(date) {
			fmt.Println("Введите кооректную дату в формате YYYY-MM-DD")
			continue
		}
		break
	}
	*visits = append(*visits, visit{name, specialization, date})
	fmt.Println("Информация о посетителе сохранена")
}

func isValidDate(date string) bool {
	pattern := `^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$`
	matched, _ := regexp.MatchString(pattern, date)
	return matched
}

func getHistoryCommand(visits []visit) error {
	count := 0
	fmt.Println("Введите ФИО:")
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	name := strings.TrimSpace(scanner.Text())
	for _, v := range visits {
		if v.name == name {
			fmt.Printf("%s %s\n", v.specialization, v.date)
			count++
		}
	}
	if count == 0 {
		return PatientNotFoundError{}
	}
	return nil
}

func getLastVisitCommand(visits []visit) error {
	fmt.Println("Введите ФИО:")
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	name := strings.TrimSpace(scanner.Text())
	fmt.Println("Введите специализацию врача:")
	scanner.Scan()
	specialization := strings.ToLower(strings.TrimSpace(scanner.Text()))

	var userVisits []visit
	for _, v := range visits {
		if v.name == name && v.specialization == specialization {
			userVisits = append(userVisits, v)
		}
	}

	if len(userVisits) == 0 {
		return PatientNotFoundError{}
	}

	sort.Slice(userVisits, func(i, j int) bool {
		return userVisits[i].date > userVisits[j].date
	})

	lastVisit := userVisits[0]
	fmt.Printf("%s\n", lastVisit.date)

	return nil
}

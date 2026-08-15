package main

import (
	"bufio"
	"fmt"
	"os"
	"time"

	"maze/cave"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	fmt.Print("Введите имя файла: ")
	filename, _ := reader.ReadString('\n')
	filename = filename[:len(filename)-1]
	c, err := cave.LoadFromFile(filename)
	if err != nil {
		fmt.Println("Ошибка:", err)
		return
	}

	var birth, death int
	fmt.Print("Введите birthLimit (0-7): ")
	fmt.Scan(&birth)
	fmt.Print("Введите deathLimit (0-7): ")
	fmt.Scan(&death)

	for {
		fmt.Println("Текущее состояние:")
		cave.DrawConsole(c)

		fmt.Println("1 - следующий шаг")
		fmt.Println("2 - авто режим")
		fmt.Println("0 - выход")

		var cmd int
		fmt.Scan(&cmd)

		if cmd == 1 {
			c.Step(birth, death)
		} else if cmd == 2 {
			var ms int
			fmt.Print("Введите задержку в мс: ")
			fmt.Scan(&ms)

			for {
				changed := c.Step(birth, death)
				cave.DrawConsole(c)
				if !changed {
					fmt.Println("Стабилизация достигнута")
					break
				}
				time.Sleep(time.Millisecond * time.Duration(ms))
			}
		} else {
			break
		}
	}
}

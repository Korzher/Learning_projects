package main

import (
	"flag"
	"fmt"
	"os"
)

func main() {
	K, N := parseFlags()
	channelInput := generator(K, N)
	channelResult := square(channelInput)
	printOut(channelResult)
}

func parseFlags() (int, int) {
	var K, N int

	flag.IntVar(&K, "K", -1, "Первое число (обязательно)")
	flag.IntVar(&N, "N", -1, "Второе число (обязательно)")

	flag.Parse()

	if K < 0 || N < 0 {
		fmt.Println("Ошибка: необходимо указать оба числа, они должны быть целыми, положительными и указаны в порядке возрастания")
		fmt.Println("Использование: go run task2.go -K=<число> -N=<число>")
		os.Exit(1)
	}
	return K, N
}

func generator(K int, N int) <-chan int {
	channelInput := make(chan int)
	go insert(channelInput, K, N)
	return channelInput

}

func insert(channelInput chan int, K int, N int) {
	defer close(channelInput)
	for i := K; i <= N; i++ {
		channelInput <- i
	}
}

func square(channelInput <-chan int) <-chan int {
	channelResult := make(chan int)
	go squareFunc(channelResult, channelInput)
	return channelResult
}

func squareFunc(channelResult chan<- int, channelInput <-chan int) {
	defer close(channelResult)
	for num := range channelInput {
		result := num * num
		channelResult <- result
	}
}

func printOut(channelResult <-chan int) {
	for squaredValue := range channelResult {
		fmt.Printf("%v\n", squaredValue)
	}
}

/*
Задание 2. Генератор квадратов числа
Программа считывает из аргументов запуска команды K и N.
Параметры K и N задаются через аргументы при вызове программы.
Программа запускает 2 функции: генератор, и функцию возведения в квадрат.
Параметры K и N имеют тип int.
Функция генератор запускает горутину и возвращает канал 1. Внутри горутины генерируются числа от K до N (включительно) и отправляются в канал 1.
Функция возведения в квадрат запускает горутину и возвращает канал 2. Внутри горутины вычитываются числа из канала 1, каждое возводится в квадрат, результат отправляется в канал 2.
Основная программа (main) вычитывает числа из канала 2 и печатает его в консоль.
Функция возведения в квадрат должна принимать канал 1 на чтение, полученный из функции генератор.
Возведение в квадрат и генератор должны быть запущены конкурентно.
Возведение числа в квадрат должно происходить последовательно. После чтения числа из канала 1 его необходимо сразу возводить в квадрат и отправлять дальше, и после этого обрабатывать другое число.
Подсказка: каналы необходимо создавать в функциях, возвращать канал с ограничением на операцию чтения/записи. Каналы необходимо закрывать после завершения работы функции. Функции генератор и возведения в квадрат должны работать конкурентно.

*/

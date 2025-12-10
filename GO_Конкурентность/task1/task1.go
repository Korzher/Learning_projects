package main

import (
	"flag"
	"fmt"
	"math/rand"
	"os"
	"sort"
	"sync"
	"time"
)

type SleepTimer struct {
	Id            int
	SleepDuration time.Duration
}

func init() {
	rand.Seed(time.Now().UnixNano())
}

func main() {
	N, M := parseFlags()
	result := createRoutines(N, M)
	sortResults(result)
	outputResults(result)
}

func parseFlags() (int, int) {
	var N, M int

	flag.IntVar(&N, "N", 0, "Первое число (обязательно)")
	flag.IntVar(&M, "M", 0, "Второе число (обязательно)")

	flag.Parse()

	if N <= 0 || M <= 0 {
		fmt.Println("Ошибка: необходимо указать два положительных целых числа")
		fmt.Println("Использование: go run task1.go -N=<число> -M=<число>")
		os.Exit(1)
	}
	return N, M
}

func createRoutines(N int, M int) []SleepTimer {
	var WaitGroup sync.WaitGroup
	result := []SleepTimer{}
	var mu sync.Mutex
	for i := 1; i <= N; i++ {
		WaitGroup.Add(1)
		go routine(i, &WaitGroup, &mu, M, &result)
	}
	WaitGroup.Wait()
	return result
}

func routine(id int, WaitGroup *sync.WaitGroup, mu *sync.Mutex, M int, result *[]SleepTimer) {
	defer WaitGroup.Done()
	sleepTime := randomSleep(M)
	mu.Lock()
	defer mu.Unlock()
	*result = append(*result, SleepTimer{id, sleepTime})
}

func randomSleep(M int) time.Duration {
	sleepTime := rand.Intn(M)
	return time.Duration(sleepTime) * time.Millisecond
}

func sortResults(result []SleepTimer) {
	sort.Slice(result, func(i int, j int) bool {
		return result[i].SleepDuration > result[j].SleepDuration
	})
}

func outputResults(result []SleepTimer) {
	for _, value := range result {
		fmt.Println(value.Id, value.SleepDuration)
	}
}

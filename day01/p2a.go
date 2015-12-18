package main

import (
	"fmt"
	"os"
)

func countFloors(input string) int {
	floor := 0
	for i, char := range(input) {
		if char == '(' {
			floor++
		} else {
			floor--
		}
		if floor == -1 {
			return i+1
		}
	}
	return -1
}

func main() {
	fd, err := os.Open(os.Args[1])
    if err != nil {
        panic(fmt.Sprintf("open %s: %v", os.Args[1], err))
    }

    var line string
    fmt.Fscanf(fd, "%s\n", &line)

	fmt.Println(countFloors(line))
}

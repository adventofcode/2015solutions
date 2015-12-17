package main

import (
	"fmt"
	"os"
)

func countFloors(input string) (floor int) {
	floor = 0
	for _, char := range(input) {
		if char == '(' {
			floor++
		} else {
			floor--
		}
	}
	return
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
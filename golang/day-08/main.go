package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	// Read input from stdin
	scanner := bufio.NewScanner(os.Stdin)
	var input [][]byte
	for scanner.Scan() {
		line := scanner.Text()
		input = append(input, []byte(line))
	}

	fmt.Printf("Part 1: %d\n", partOne(input))
	fmt.Printf("Part 2: %d\n", partTwo(input))
}

func partOne(input [][]byte) int {
	mapData := make(map[byte][][2]int)
	set := make(map[[2]int]struct{})

	n := len(input)
	m := 0
	if n > 0 {
		m = len(input[0])
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			if input[i][j] != '.' {
				mapData[input[i][j]] = append(mapData[input[i][j]], [2]int{i, j})
			}
		}
	}

	for _, v := range mapData {
		for i := 0; i < len(v); i++ {
			for j := i + 1; j < len(v); j++ {
				d0 := v[j][0] - v[i][0]
				d1 := v[j][1] - v[i][1]

				p1 := [2]int{v[j][0] + d0, v[j][1] + d1}
				p2 := [2]int{v[i][0] - d0, v[i][1] - d1}

				if p1[0] >= 0 && p1[0] < n && p1[1] >= 0 && p1[1] < m {
					set[p1] = struct{}{}
				}

				if p2[0] >= 0 && p2[0] < n && p2[1] >= 0 && p2[1] < m {
					set[p2] = struct{}{}
				}
			}
		}
	}

	return len(set)
}

func partTwo(input [][]byte) int {
	mapData := make(map[byte][][2]int)
	set := make(map[[2]int]struct{})

	n := len(input)
	m := 0
	if n > 0 {
		m = len(input[0])
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			if input[i][j] != '.' {
				mapData[input[i][j]] = append(mapData[input[i][j]], [2]int{i, j})
			}
		}
	}

	inRange := func(p [2]int) bool {
		return p[0] >= 0 && p[0] < n && p[1] >= 0 && p[1] < m
	}

	for _, v := range mapData {
		for i := 0; i < len(v); i++ {
			for j := i + 1; j < len(v); j++ {
				d0 := v[j][0] - v[i][0]
				d1 := v[j][1] - v[i][1]

				p1 := v[j]
				p2 := v[i]

				for inRange(p1) {
					set[p1] = struct{}{}
					p1 = [2]int{p1[0] + d0, p1[1] + d1}
				}

				for inRange(p2) {
					set[p2] = struct{}{}
					p2 = [2]int{p2[0] - d0, p2[1] - d1}
				}
			}
		}
	}

	return len(set)
}

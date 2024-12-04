package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var data []string
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		data = append(data, scanner.Text())
	}

	fmt.Printf("Part 1: %d\n", partOne(data))
	fmt.Printf("Part 2: %d\n", partTwo(data))
}

func partOne(data []string) int64 {
	var ans int64
	toCheck := "XMAS"
	check := func(i, j int, di, dj int64) bool {
		x, y := int64(i), int64(j)
		for k := 0; k < len(toCheck); k++ {
			if x >= 0 && x < int64(len(data)) && y >= 0 && y < int64(len(data[0])) {
				if data[x][y] != toCheck[k] {
					return false
				}
				x += di
				y += dj
			} else {
				return false
			}
		}
		return true
	}

	for i := 0; i < len(data); i++ {
		for j := 0; j < len(data[i]); j++ {
			if data[i][j] == 'X' {
				for di := -1; di <= 1; di++ {
					for dj := -1; dj <= 1; dj++ {
						if check(i, j, int64(di), int64(dj)) {
							ans++
						}
					}
				}
			}
		}
	}
	return ans
}

func partTwo(data []string) int64 {
	var ans int64
	check := func(i, j int) bool {
		if data[i][j] != 'A' {
			return false
		}
		if i == 0 || i == len(data)-1 || j == 0 || j == len(data[i])-1 {
			return false
		}

		for d := -1; d <= 1; d++ {
			x, y := i+d, j+d
			if x >= 0 && x < len(data) && y >= 0 && y < len(data[x]) {
				continue
			}
			return false
		}

		for d := -1; d <= 1; d++ {
			x, y := i+d, j-d
			if x >= 0 && x < len(data) && y >= 0 && y < len(data[x]) {
				continue
			}
			return false
		}

		found1 := (data[i-1][j-1] == 'M' && data[i+1][j+1] == 'S') ||
			(data[i-1][j-1] == 'S' && data[i+1][j+1] == 'M')

		found2 := (data[i-1][j+1] == 'M' && data[i+1][j-1] == 'S') ||
			(data[i-1][j+1] == 'S' && data[i+1][j-1] == 'M')

		return found1 && found2
	}

	for i := 0; i < len(data); i++ {
		for j := 0; j < len(data[i]); j++ {
			if data[i][j] == 'A' {
				if check(i, j) {
					ans++
				}
			}
		}
	}
	return ans
}

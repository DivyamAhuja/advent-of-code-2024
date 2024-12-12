package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

type Grid [][]int

func dfsPartOne(input Grid, visited map[[2]int]bool, i, j int) uint64 {
	if visited[[2]int{i, j}] {
		return 0
	}
	visited[[2]int{i, j}] = true

	if input[i][j] == 9 {
		return 1
	}

	ways := uint64(0)
	if i > 0 && input[i][j]+1 == input[i-1][j] {
		ways += dfsPartOne(input, visited, i-1, j)
	}

	if i < len(input)-1 && input[i][j]+1 == input[i+1][j] {
		ways += dfsPartOne(input, visited, i+1, j)
	}

	if j > 0 && input[i][j]+1 == input[i][j-1] {
		ways += dfsPartOne(input, visited, i, j-1)
	}

	if j < len(input[i])-1 && input[i][j]+1 == input[i][j+1] {
		ways += dfsPartOne(input, visited, i, j+1)
	}

	return ways
}

func partOne(input Grid) uint64 {
	ans := uint64(0)
	for i := range input {
		for j := range input[i] {
			if input[i][j] == 0 {
				visited := make(map[[2]int]bool)
				ans += dfsPartOne(input, visited, i, j)
			}
		}
	}
	return ans
}

func dfsPartTwo(input Grid, i, j int) uint64 {
	if input[i][j] == 9 {
		return 1
	}

	ways := uint64(0)
	if i > 0 && input[i][j]+1 == input[i-1][j] {
		ways += dfsPartTwo(input, i-1, j)
	}

	if i < len(input)-1 && input[i][j]+1 == input[i+1][j] {
		ways += dfsPartTwo(input, i+1, j)
	}

	if j > 0 && input[i][j]+1 == input[i][j-1] {
		ways += dfsPartTwo(input, i, j-1)
	}

	if j < len(input[i])-1 && input[i][j]+1 == input[i][j+1] {
		ways += dfsPartTwo(input, i, j+1)
	}

	return ways
}

func partTwo(input Grid) uint64 {
	ans := uint64(0)
	for i := range input {
		for j := range input[i] {
			if input[i][j] == 0 {
				ans += dfsPartTwo(input, i, j)
			}
		}
	}
	return ans
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var input Grid

	for scanner.Scan() {
		line := scanner.Text()
		row := []int{}
		for _, c := range line {
			num, err := strconv.Atoi(string(c))
			if err == nil {
				row = append(row, num)
			}
		}
		input = append(input, row)
	}

	fmt.Printf("Part 1: %d\n", partOne(input))
	fmt.Printf("Part 2: %d\n", partTwo(input))
}

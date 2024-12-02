package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

func main() {
	var left, right []int

	reader := bufio.NewScanner(os.Stdin)
	for reader.Scan() {
		line := reader.Text()
		parts := strings.Fields(line)

		if len(parts) != 2 {
			break
		}

		in1, err1 := strconv.Atoi(parts[0])
		in2, err2 := strconv.Atoi(parts[1])
		if err1 != nil || err2 != nil {
			break
		}
		left = append(left, in1)
		right = append(right, in2)

		if err := reader.Err(); err != nil {
			fmt.Fprintln(os.Stderr, "Error reading input:", err)
			return
		}
	}

	fmt.Printf("Part 1: %d\n", part_one(left, right))
	fmt.Printf("Part 2: %d\n", part_two(left, right))
}

func part_one(left, right []int) uint64 {
	sort.Ints(left)
	sort.Ints(right)

	var ans uint64 = 0

	for i := range left {
		diff := left[i] - right[i]
		if diff < 0 {
			diff = -diff
		}
		ans += uint64(diff)
	}
	return ans
}

func part_two(left, right []int) uint64 {
	freq := make(map[int]int)

	for _, v := range right {
		freq[v]++
	}

	var ans uint64 = 0

	for _, v := range left {
		ans += uint64(v * freq[v])
	}
	return ans
}

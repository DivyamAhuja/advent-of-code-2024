package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {

	var data [][]int64

	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line := scanner.Text()
		levels := strings.Fields(line)

		var report []int64

		for _, level := range levels {
			lvl, err := strconv.Atoi(level)
			if err != nil {
				break
			}
			report = append(report, int64(lvl))
		}

		data = append(data, report)
	}

	fmt.Printf("Part 1: %d\n", part_one(data))
	fmt.Printf("Part 2: %d\n", part_two(data))
}

func report_is_valid(report []int64) bool {
	n := len(report)
	increasing := true
	if 1 < n {
		increasing = report[0] < report[1]
	}
	for i := 1; i < n; i++ {
		diff := report[i] - report[i-1]
		if increasing && 1 <= diff && diff <= 3 {
			continue
		}
		if !increasing && -3 <= diff && diff <= -1 {
			continue
		}
		return false
	}
	return true
}

func part_one(data [][]int64) int64 {
	ans := int64(0)
	for _, report := range data {
		if report_is_valid(report) {
			ans += 1
		}
	}
	return ans
}

func part_two(data [][]int64) int64 {
	ans := int64(0)
	for _, report := range data {
		if report_is_valid(report) {
			ans += 1
		} else {
			for index := range len(report) {
				v := make([]int64, len(report)-1)
				copy(v, report[:index])
				copy(v[index:], report[index+1:])

				if report_is_valid(v) {
					ans += 1
					break
				}
			}

		}
	}
	return ans
}

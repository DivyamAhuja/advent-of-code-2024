package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func main() {

	var data string

	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line := scanner.Text()
		data += line + " "
	}

	fmt.Printf("Part 1: %d\n", part_one(data))
	fmt.Printf("Part 2: %d\n", part_two(data))
}

func part_one(data string) uint64 {
	var ans uint64
	re := regexp.MustCompile(`mul\(\d+,\d+\)`)
	matches := re.FindAllString(data, -1)

	for _, match := range matches {
		nums := strings.Split(match[4:len(match)-1], ",")
		num1, _ := strconv.ParseUint(nums[0], 10, 64)
		num2, _ := strconv.ParseUint(nums[1], 10, 64)
		ans += num1 * num2
	}
	return ans
}

func part_two(data string) uint64 {
	var ans uint64
	re := regexp.MustCompile(`mul\(\d+,\d+\)|do\(\)|don't\(\)`)
	matches := re.FindAllString(data, -1)
	enabled := true
	for _, match := range matches {
		if match == "do()" {
			enabled = true
			continue
		}
		if match == "don't()" {
			enabled = false
			continue
		}
		if !enabled {
			continue
		}

		nums := strings.Split(match[4:len(match)-1], ",")
		num1, _ := strconv.ParseUint(nums[0], 10, 64)
		num2, _ := strconv.ParseUint(nums[1], 10, 64)
		ans += num1 * num2
	}
	return ans
}

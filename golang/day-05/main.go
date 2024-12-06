package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Rules map[int]map[int]bool

func parse(data []string) (Rules, [][]int) {
	rules := make(Rules)
	updates := [][]int{}
	i := 0

	// Parse rules
	for i < len(data) && data[i] != "" {
		parts := strings.Split(data[i], "|")
		num1, _ := strconv.Atoi(parts[0])
		num2, _ := strconv.Atoi(parts[1])
		if _, exists := rules[num2]; !exists {
			rules[num2] = make(map[int]bool)
		}
		rules[num2][num1] = true
		i++
	}
	i++

	// Parse updates
	for i < len(data) {
		parts := strings.Split(data[i], ",")
		update := make([]int, len(parts))
		for j, p := range parts {
			update[j], _ = strconv.Atoi(p)
		}
		updates = append(updates, update)
		i++
	}

	return rules, updates
}

func part1(data []string) uint64 {
	rules, updates := parse(data)
	var ans uint64

	for _, update := range updates {
		valid := true
	outer:
		for i := 0; i < len(update); i++ {
			for j := i + 1; j < len(update); j++ {
				if rules[update[i]][update[j]] {
					valid = false
					break outer
				}
			}
		}
		if valid {
			ans += uint64(update[len(update)/2])
		}
	}

	return ans
}

func part2(data []string) uint64 {
	rules, updates := parse(data)
	var ans uint64

	for _, update := range updates {
		valid := true
	outer:
		for i := 0; i < len(update); i++ {
			for j := i + 1; j < len(update); j++ {
				if rules[update[i]][update[j]] {
					valid = false
					break outer
				}
			}
		}

		if !valid {
			visited := make(map[int]bool)
			inUpdate := make(map[int]bool)
			for _, u := range update {
				inUpdate[u] = true
			}

			order := []int{}

			var dfs func(int)
			dfs = func(x int) {
				if visited[x] {
					return
				}
				visited[x] = true

				for p := range rules[x] {
					if inUpdate[p] {
						dfs(p)
					}
				}
				order = append(order, x)
			}

			for _, u := range update {
				if !visited[u] {
					dfs(u)
				}
			}

			ans += uint64(order[len(order)/2])
		}
	}

	return ans
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	data := []string{}

	for scanner.Scan() {
		data = append(data, scanner.Text())
	}

	fmt.Printf("Part 1: %d\n", part1(data))
	fmt.Printf("Part 2: %d\n", part2(data))
}

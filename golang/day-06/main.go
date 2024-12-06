package main

import (
	"bufio"
	"fmt"
	"os"
)

type Position struct {
	x, y int
}

type Direction struct {
	dx, dy int
}

type ParsedData struct {
	start Position
	dir   Direction
	area  [][]int
}

var path []Position

func parse(data []string) ParsedData {
	n := len(data)
	m := len(data[0])
	area := make([][]int, n)
	for i := range area {
		area[i] = make([]int, m)
	}

	var start Position
	var dir Direction

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			switch data[i][j] {
			case '#':
				area[i][j] = 2
			case '^':
				start = Position{i, j}
				dir = Direction{-1, 0}
			case '>':
				start = Position{i, j}
				dir = Direction{0, 1}
			case 'v':
				start = Position{i, j}
				dir = Direction{1, 0}
			case '<':
				start = Position{i, j}
				dir = Direction{0, -1}
			}
		}
	}

	return ParsedData{start, dir, area}
}

func turnRight(dx, dy int) (int, int) {
	if dx != 0 {
		return 0, -dx
	}
	return dy, 0
}

func part1(data []string) int {
	parsed := parse(data)
	pos := parsed.start
	dir := parsed.dir
	area := parsed.area

	n, m := len(area), len(area[0])
	for {
		nx, ny := pos.x+dir.dx, pos.y+dir.dy

		area[pos.x][pos.y] = 1
		if nx < 0 || nx >= n || ny < 0 || ny >= m {
			break
		}

		if area[nx][ny] > 1 {
			dir.dx, dir.dy = turnRight(dir.dx, dir.dy)
		} else {
			pos.x, pos.y = nx, ny
		}
	}

	ans := 0
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			if area[i][j] == 1 {
				ans++
				path = append(path, Position{i, j})
			}
		}
	}

	return ans
}

func part2(data []string) int {
	parsed := parse(data)
	start := parsed.start
	dir := parsed.dir
	area := parsed.area

	n, m := len(area), len(area[0])
	ans := 0

	for _, p := range path {
		if p == start {
			continue
		}

		area[p.x][p.y] = 2
		visited := make(map[string]struct{})
		pos := start
		dir := dir
		loop := false

		for {
			nx, ny := pos.x+dir.dx, pos.y+dir.dy

			area[pos.x][pos.y] = 1
			if nx < 0 || nx >= n || ny < 0 || ny >= m {
				break
			}

			edge := fmt.Sprintf("%d,%d,%d,%d", pos.x, dir.dx, pos.y, dir.dy)
			if _, exists := visited[edge]; exists {
				loop = true
				break
			}
			visited[edge] = struct{}{}

			if area[nx][ny] > 1 {
				dir.dx, dir.dy = turnRight(dir.dx, dir.dy)
			} else {
				pos.x, pos.y = nx, ny
			}
		}

		if loop {
			ans++
		}

		area[p.x][p.y] = 0
	}

	return ans
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var data []string

	for scanner.Scan() {
		data = append(data, scanner.Text())
	}

	fmt.Printf("Part 1: %d\n", part1(data))
	fmt.Printf("Part 2: %d\n", part2(data))
}

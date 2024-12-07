package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var input []string

	for scanner.Scan() {
		line := scanner.Text()
		input = append(input, line)
	}

	fmt.Printf("Part 1: %d\n", partOne(input))
	fmt.Printf("Part 2: %d\n", partTwo(input))
}

type Equation struct {
	Result   int64
	Operands []int64
}

func parse(input []string) []Equation {
	var equations []Equation
	for _, eq := range input {
		parts := strings.Split(eq, ":")
		if len(parts) != 2 {
			continue
		}
		result, err := strconv.ParseInt(strings.TrimSpace(parts[0]), 10, 64)
		if err != nil {
			panic(err)
		}
		operandStrings := strings.Fields(parts[1])
		var operands []int64
		for _, op := range operandStrings {
			operand, err := strconv.ParseInt(op, 10, 64)
			if err != nil {
				panic(err)
			}
			operands = append(operands, operand)
		}
		equations = append(equations, Equation{Result: result, Operands: operands})
	}
	return equations
}

func possible(result int64, operands []int64, curr int64, index int) bool {
	if index == len(operands) {
		return curr == result
	}
	can := false
	can = can || possible(result, operands, curr+operands[index], index+1)
	can = can || possible(result, operands, curr*operands[index], index+1)
	return can
}

func possiblePartTwo(result int64, operands []int64, curr int64, index int) bool {
	if index == len(operands) {
		return curr == result
	}
	can := false
	can = can || possiblePartTwo(result, operands, curr+operands[index], index+1)
	can = can || possiblePartTwo(result, operands, curr*operands[index], index+1)
	concatenated, err := strconv.ParseInt(fmt.Sprintf("%d%d", curr, operands[index]), 10, 64)
	if err == nil {
		can = can || possiblePartTwo(result, operands, concatenated, index+1)
	}
	return can
}

func partOne(input []string) int64 {
	var ans int64
	equations := parse(input)

	for _, eq := range equations {
		if len(eq.Operands) == 0 {
			continue
		}
		if possible(eq.Result, eq.Operands, eq.Operands[0], 1) {
			ans += eq.Result
		}
	}
	return ans
}

func partTwo(input []string) int64 {
	var ans int64
	equations := parse(input)

	for _, eq := range equations {
		if len(eq.Operands) == 0 {
			continue
		}
		if possiblePartTwo(eq.Result, eq.Operands, eq.Operands[0], 1) {
			ans += eq.Result
		}
	}
	return ans
}

package main

import (
	"bufio"
	"fmt"
	"os"
)

type Block struct {
	len int
	id  *int64
}

func NewBlock(len int, id *int64) Block {
	return Block{len: len, id: id}
}

func (b Block) Empty() bool {
	return b.id == nil
}

func partOne(input string) int64 {
	var checksum int64
	disk := make([]Block, 0)

	for i, c := range input {
		len := int(c - '0')
		if i%2 == 0 {
			id := int64(i / 2)
			for j := 0; j < len; j++ {
				disk = append(disk, NewBlock(1, &id))
			}
		} else {
			for j := 0; j < len; j++ {
				disk = append(disk, NewBlock(1, nil))
			}
		}
	}

	first, last := 0, len(disk)-1

	for {
		for first < len(disk) && !disk[first].Empty() {
			first++
		}
		for last > 0 && disk[last].Empty() {
			last--
		}
		if last < first {
			break
		}
		disk[first], disk[last] = disk[last], disk[first]
	}

	for i, block := range disk {
		if block.id != nil {
			checksum += int64(i) * *block.id
		}
	}

	return checksum
}

func partTwo(input string) int64 {
	var checksum int64
	disk := make([]Block, 0)

	for i, c := range input {
		len := int(c - '0')
		if len == 0 {
			continue
		}
		if i%2 == 0 {
			id := int64(i / 2)
			disk = append(disk, NewBlock(len, &id))
		} else {
			disk = append(disk, NewBlock(len, nil))
		}
	}

	last := len(disk) - 1

	for last > 0 {
		first := 0
		for last > 0 && disk[last].Empty() {
			last--
		}
		for first <= last {
			if disk[first].Empty() && disk[last].len <= disk[first].len {
				break
			}
			first++
		}
		if last < first {
			last--
			continue
		}

		remainingLen := disk[first].len - disk[last].len
		disk[first] = disk[last]
		disk[last] = NewBlock(disk[first].len, nil)
		if remainingLen > 0 {
			newBlock := NewBlock(remainingLen, nil)
			disk = append(disk[:first+1], append([]Block{newBlock}, disk[first+1:]...)...)
			last++
		}
	}

	index := 0
	for _, block := range disk {
		for j := 0; j < block.len; j++ {
			if block.id != nil {
				checksum += int64(index) * *block.id
			}
			index++
		}
	}

	return checksum
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var input string
	if scanner.Scan() {
		input = scanner.Text()
	}

	fmt.Printf("Part 1: %d\n", partOne(input))
	fmt.Printf("Part 2: %d\n", partTwo(input))
}

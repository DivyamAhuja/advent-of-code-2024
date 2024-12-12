use std::collections::VecDeque;

#[derive(Debug, Clone)]
struct Block {
    len: usize,
    id: Option<i64>,
}

impl Block {
    fn new(len: usize, id: Option<i64>) -> Self {
        Block { len, id }
    }

    fn empty(&self) -> bool {
        self.id.is_none()
    }
}

fn part_one(input: &str) -> i64 {
    let mut checksum = 0;
    let mut disk: Vec<Block> = Vec::new();

    for (i, c) in input.chars().enumerate() {
        let len = (c.to_digit(10).unwrap_or(0)) as usize;
        if i % 2 == 0 {
            let id = (i / 2) as i64;
            for _ in 0..len {
                disk.push(Block::new(1, Some(id)));
            }
        } else {
            for _ in 0..len {
                disk.push(Block::new(1, None));
            }
        }
    }

    let mut first = 0;
    let mut last = disk.len().saturating_sub(1);

    while first < last {
        while first < disk.len() && !disk[first].empty() {
            first += 1;
        }
        while last > 0 && disk[last].empty() {
            last = last.saturating_sub(1);
        }

        if last <= first {
            break;
        }

        disk.swap(first, last);
    }

    for (i, block) in disk.iter().enumerate() {
        if let Some(id) = block.id {
            checksum += id * i as i64;
        }
    }

    checksum
}

fn part_two(input: &str) -> i64 {
    let mut checksum = 0;
    let mut disk: VecDeque<Block> = VecDeque::new();

    for (i, c) in input.chars().enumerate() {
        let len = (c.to_digit(10).unwrap_or(0)) as usize;
        if len == 0 {
            continue;
        }
        if i % 2 == 0 {
            let id = (i / 2) as i64;
            disk.push_back(Block::new(len, Some(id)));
        } else {
            disk.push_back(Block::new(len, None));
        }
    }
    let mut last = disk.len() - 1;
    while 0 < last {
        while 0 < last && disk[last].empty() {
            last -= 1;
        }
        let mut first = 0;
        while first <= last {
            if disk[first].empty() && disk[last].len <= disk[first].len {
                break;
            }
            first += 1;
        }

        if last < first {
            last -= 1;
            continue;
        }

        let last_block = disk[last].clone();
        let remaining_len = disk[first].len.saturating_sub(last_block.len);
        disk[first] = last_block;
        disk[last] = Block::new(disk[first].len, None);

        if remaining_len > 0 {
            disk.insert(first + 1, Block::new(remaining_len, None));
        }
    }

    let mut index = 0;
    for block in &disk {
        for _ in 0..block.len {
            if let Some(id) = block.id {
                checksum += id * index as i64;
            }
            index += 1;
        }
    }

    checksum
}

fn main() {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let input = input.trim();

    println!("Part 1: {}", part_one(input));
    println!("Part 2: {}", part_two(input));
}

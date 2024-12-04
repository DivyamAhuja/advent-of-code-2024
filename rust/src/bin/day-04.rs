use std::io;

fn main() {
    let data = io::stdin()
        .lines()
        .filter_map(Result::ok)
        .collect::<Vec<_>>();

    println!("Part 1: {}", part_one(&data));
    println!("Part 2: {}", part_two(&data));
}

fn part_one(data: &Vec<String>) -> i64 {
    let mut ans = 0;
    let to_check = "XMAS";
    let check = |i: usize, j: usize, di: i64, dj: i64| {
        let to_check = to_check.as_bytes();
        let mut x = i as i64;
        let mut y = j as i64;
        for i in 0..to_check.len() {
            if 0 <= x && x < data.len() as i64 && 0 <= y && y < data[0].len() as i64 {
                if data[x as usize].as_bytes()[y as usize] != to_check[i] {
                    return false;
                }
                x += di;
                y += dj;
            } else {
                return  false;
            }
        }
        return true;
    };

    for i in 0..data.len() {
        for j in 0..data[i].len() {
            if data[i].as_bytes()[j] == b'X' {
                for di in -1..=1 {
                    for dj in -1..=1 {
                        if check(i, j, di, dj) {
                            ans += 1;
                        }
                    }
                }
            }
        }
    }

    return ans;
}

fn part_two(data: &Vec<String>) -> i64 {
    let mut ans = 0;
    let check = |i: usize, j: usize| {
        if data[i].as_bytes()[j] != b'A' {
            return false;
        }
        if i == 0 || i == data.len() - 1 || j == 0 || j == data[i].len() - 1 {
            return false;
        }

        for d in -1..=1 {
            let x = i as i64 + d;
            let y = j as i64 + d;
            if 0 <= x && x < data.len() as i64 && 0 <= y && y < data[x as usize].len() as i64 {
                continue;
            }
            return  false;
        }

        for d in -1..=1 {
            let x = i as i64 + d;
            let y = j as i64 - d;
            if 0 <= x && x < data.len() as i64 && 0 <= y && y < data[x as usize].len() as i64 {
                continue;
            }
            return  false;
        }

        let (mut found1, mut found2) = (false, false);
        found1 |= data[i - 1].as_bytes()[j - 1] == b'M' && data[i + 1].as_bytes()[j + 1] == b'S';
        found1 |= data[i - 1].as_bytes()[j - 1] == b'S' && data[i + 1].as_bytes()[j + 1] == b'M';

        found2 |= data[i - 1].as_bytes()[j + 1] == b'M' && data[i + 1].as_bytes()[j - 1] == b'S';
        found2 |= data[i - 1].as_bytes()[j + 1] == b'S' && data[i + 1].as_bytes()[j - 1] == b'M';
        
        return found1 && found2;
    };

    for i in 0..data.len() {
        for j in 0..data[i].len() {
            if data[i].as_bytes()[j] == b'A' {
                if check(i, j) {
                    ans += 1;
                }
            }
        }
    }
    return ans;
}
use std::io;
use regex::Regex;

fn main() {
    let data = io::stdin()
        .lines()
        .filter_map(Result::ok)
        .map(|x| x + " ")
        .collect::<String>();

        println!("Part 1: {}", part_one(&data));
        println!("Part 2: {}", part_two(&data));
        return;
}

fn part_one(data: &String) -> u64 {
    let re = Regex::new(r"mul\(\d+,\d+\)").unwrap();
    
    let mut ans = 0;
    for mat in re.find_iter(data) {
        let s = mat.as_str();
        let b = s.as_bytes();
        let mut i = 4;
        let mut num1: u64 = 0;
        let mut num2: u64 = 0;
        
        while b[i] as char != ',' {
            num1 = 10 * num1 + ((b[i] - ('0' as u8)) as u64);
            i += 1;
        }
        i += 1;
        while b[i] as char != ')' {
            num2 = 10 * num2 + ((b[i] - ('0' as u8)) as u64);
            i += 1;
        }

        ans += num1 * num2
    }

    ans
}

fn part_two(data: &String) -> u64 {
    let re = Regex::new(r"mul\(\d+,\d+\)|do\(\)|don't\(\)").unwrap();
    
    let mut ans = 0;
    let mut enabled = true;

    for mat in re.find_iter(data) {
        let s = mat.as_str();

        if s == "do()" {
            enabled = true;
            continue;
        }

        if s == "don't()" {
            enabled = false;
            continue;
        }

        if !enabled {
            continue;
        }

        let b = s.as_bytes();
        let mut i = 4;
        let mut num1: u64 = 0;
        let mut num2: u64 = 0;
        
        while b[i] as char != ',' {
            num1 = 10 * num1 + ((b[i] - ('0' as u8)) as u64);
            i += 1;
        }
        i += 1;
        while b[i] as char != ')' {
            num2 = 10 * num2 + ((b[i] - ('0' as u8)) as u64);
            i += 1;
        }

        ans += num1 * num2
    }

    ans
}
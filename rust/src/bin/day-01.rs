use std::{collections::HashMap, io};

fn main() {
    let (mut left, mut right) = io::stdin()
        .lines()
        .filter_map(Result::ok)
        .map(|x| 
            x.split_whitespace().map(|x| x.parse::<u64>().unwrap()).collect::<Vec<_>>()
        ).map(|x| (x[0], x[1]))
        .unzip::<_, _, Vec<_>, Vec<_>>();
    
    println!("Part 1: {}", part_one(&mut left, &mut right));
    println!("Part 2: {}", part_two(&mut left, &mut right));
}

fn part_one(left: &mut Vec<u64>, right: &mut Vec<u64>) -> u64 {
    left.sort();
    right.sort();

    let ans = left.into_iter().zip(right.into_iter())
        .fold(0, |acc, x| acc + x.0.abs_diff(*x.1));

    return ans;
}

fn part_two(left: &mut Vec<u64>, right: &mut Vec<u64>) -> u64 {
    let mut freq: HashMap<u64, u64> = HashMap::new();

    let mut ans = 0;

    for x in right.iter() {
        if let Some(count) = freq.get(x) {
            freq.insert(*x, count + 1);
        } else {
            freq.insert(*x, 1);
        }
    }

    for x in left.iter() {
        if let Some(count) = freq.get(x) {
            ans += x * count;
        }
    }

    return ans;
}
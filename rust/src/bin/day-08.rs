use std::{collections::{HashMap, HashSet}, ops::Index};


fn main() {
    let input = std::io::stdin()
        .lines()
        .filter_map(Result::ok)
        .map(|x| x.as_bytes().to_vec())
        .collect::<Vec<_>>();

    println!("Part 1: {}", part_one(&input));
    println!("Part 2: {}", part_two(&input));
}

#[allow(unused_variables)]
fn part_one(input: &Vec<Vec<u8>>) -> i64 {
    let mut map = HashMap::<u8, Vec<(i64, i64)>>::new();
    let mut set = HashSet::<(i64, i64)>::new();

    let n = input.len() as i64;
    let m = if n > 0 { input.index(0).len() as i64 } else { 0 };

    for i in 0..input.len() {
        for j in 0..input.index(i).len() {
            if input[i][j] != b'.' {
                map.entry(input[i][j]).or_default().push((i as i64, j as i64));
            }
        }
    }

    for (_, v) in map {
        for i in 0..v.len() {
            for j in i+1..v.len() {
                let d0 = v[j].0 - v[i].0;
                let d1 = v[j].1 - v[i].1;
                let p1 = (v[j].0 + d0, v[j].1 + d1);
                let p2 = (v[i].0 - d0, v[i].1 - d1);

                if 0 <= p1.0 && p1.0 < n && 0 <= p1.1 && p1.1 < m {
                    set.insert(p1);
                }

                if 0 <= p2.0 && p2.0 < n && 0 <= p2.1 && p2.1 < m {
                    set.insert(p2);
                }

            }
        }
    }

    return set.len() as i64;
}

#[allow(unused_variables)]
fn part_two(input: &Vec<Vec<u8>>) -> i64 {
    let mut map = HashMap::<u8, Vec<(i64, i64)>>::new();
    let mut set = HashSet::<(i64, i64)>::new();

    let n = input.len() as i64;
    let m = if n > 0 { input.index(0).len() as i64 } else { 0 };

    for i in 0..input.len() {
        for j in 0..input.index(i).len() {
            if input[i][j] != b'.' {
                map.entry(input[i][j]).or_default().push((i as i64, j as i64));
            }
        }
    }

    let in_range = |p: &(i64, i64)| -> bool {
        return 0 <= p.0 && p.0 < n && 0 <= p.1 && p.1 < m;
    };

    for (_, v) in map {
        for i in 0..v.len() {
            for j in i+1..v.len() {
                let d0 = v[j].0 - v[i].0;
                let d1 = v[j].1 - v[i].1;
                let mut p1 = v[j];
                let mut p2 = v[i];

                while in_range(&p1) {
                    set.insert(p1);
                    p1 = (p1.0 + d0, p1.1 + d1);
                }

                while in_range(&p2) {
                    set.insert(p2);
                    p2 = (p2.0 - d0, p2.1 - d1);
                }

            }
        }
    }

    return set.len() as i64;
}
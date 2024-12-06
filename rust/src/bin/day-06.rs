use std::{collections::HashSet, i64};

fn main() {
    let input = std::io::stdin()
        .lines()
        .filter_map(Result::ok)
        .map(|x| x.as_bytes().to_vec())
        .collect::<Vec<_>>();
    
    let map = Map::new(input);
    println!("Part 1: {}", part_one(&map));
    println!("Part 2: {}", part_two(&map));
}

struct Map {
    area: Vec<Vec<u8>>,
    start: (i64, i64),
    dir: (i64, i64)
}

impl Map {
    fn new(input: Vec<Vec<u8>>) -> Self {
        let n = input.len();
        let m = if n > 0 { input[0].len() } else { 0 };
        let mut start = (0, 0);
        let mut dir = (0, 0);
        for i in 0..n as i64 {
            for j in 0..m as i64 {
                match input[i as usize][j as usize] {
                    b'^' => {
                        start = (i, j);
                        dir = (-1, 0);
                    },
                    b'v' => {
                        start = (i, j);
                        dir = (1, 0);
                    },
                    b'>' => {
                        start = (i, j);
                        dir = (0, 1);
                    },
                    b'<' => {
                        start = (i, j);
                        dir = (0, -1);
                    },
                    _ => ()
                };     
            }
        }
        Self {area: input, start, dir}
    }

    fn visit(&self) -> HashSet<(i64, i64)> {
        let mut path: HashSet<(i64, i64)> = HashSet::new();
        let (mut i, mut j) = self.start;
        let (mut di, mut dj) = self.dir;
        
        let n = self.area.len() as i64;
        let m = if n > 0 { self.area[0].len() as i64 } else { 0 };

        loop {
            let ni = i + di;
            let nj = j + dj;

            path.insert((i, j));
            if !(0 <= ni && ni < n && 0 <= nj && nj < m) {
                break;
            }

            if self.area[ni as usize][nj as usize] == b'#' {
                if di != 0 {
                    (di, dj) = (0, -di);
                } 
                else if dj != 0 {
                    (di, dj) = (dj, 0);
                }
            } else {
                (i, j) = (ni, nj);
            }
        }

        return path;
    }

    fn loops(&self, obstruction: (i64, i64)) -> bool {
        let mut edges: HashSet<(i64, i64, i64, i64)> = HashSet::new();
        let (mut i, mut j) = self.start;
        let (mut di, mut dj) = self.dir;
        
        if (i, j) == obstruction {
            return false;
        }

        let n = self.area.len() as i64;
        let m = if n > 0 { self.area[0].len() as i64 } else { 0 };

        loop {
            let ni = i + di;
            let nj = j + dj;

            if !(0 <= ni && ni < n && 0 <= nj && nj < m) {
                return false;
            }

            let edge = (i, j, di, dj);
            if !edges.insert(edge) {
                return true;
            }

            if (ni, nj) == obstruction || self.area[ni as usize][nj as usize] == b'#' {
                if di != 0 {
                    (di, dj) = (0, -di);
                } 
                else if dj != 0 {
                    (di, dj) = (dj, 0);
                }
            } else {

                (i, j) = (ni, nj);
            }
        }

    }
}

fn part_one(map: &Map) -> u64 {
    return map.visit().len() as u64;
}

fn part_two(map: &Map) -> u64 {
    return map.visit()
        .into_iter()
        .filter(|obs| map.loops(*obs))
        .count() as u64;
}
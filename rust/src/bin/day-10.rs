use std::{collections::HashSet, ops::Index, usize};


fn main() {
    let input = std::io::stdin()
        .lines()
        .filter_map(Result::ok)
        .map(
            |x| x.chars()
                .map(|x| x.to_digit(10).unwrap())
                .collect::<Vec<_>>()
        )
        .collect::<Vec<_>>();

    println!("Part 1: {}", part_one(&input));
    println!("Part 2: {}", part_two(&input));
}

fn part_one(input: &Vec<Vec<u32>>) -> u64 {
    
    fn dfs(
        input: &Vec<Vec<u32>>,
        visited: &mut HashSet<(usize, usize)>,
        i: usize, j: usize
    ) -> u64 { 
        if visited.contains(&(i, j)) {
            return 0;
        }
        visited.insert((i, j));

        if input[i][j] == 9 {
            return 1;
        }

        let mut ways = 0;
        if 0 < i && input[i][j] + 1 == input[i - 1][j] {
            ways += dfs(input, visited, i - 1, j)
        }

        if i < input.len() - 1 && input[i][j] + 1 == input[i + 1][j] {
            ways += dfs(input, visited, i + 1, j)
        }

        if 0 < j && input[i][j] + 1 == input[i][j - 1] {
            ways += dfs(input, visited, i, j - 1)
        }

        if j < input.index(i).len() - 1 && input[i][j] + 1 == input[i][j + 1] {
            ways += dfs(input, visited, i, j + 1)
        }
        return ways;
    }
    let mut ans = 0;
    for i in 0..input.len() {
        for j in 0..input.index(i).len() {
            if input[i][j] == 0 {
                let mut visited = HashSet::<(usize, usize)>::new();
                ans += dfs(input, &mut visited, i, j);
            }
        }
    }
    ans
}

fn part_two(input: &Vec<Vec<u32>>) -> u64{
    
    fn dfs(
        input: &Vec<Vec<u32>>,
        i: usize, j: usize
    ) -> u64 { 
        if input[i][j] == 9 {
            return 1;
        }
        
        let mut ways = 0;
        if 0 < i && input[i][j] + 1 == input[i - 1][j] {
            ways += dfs(input, i - 1, j)
        }

        if i < input.len() - 1 && input[i][j] + 1 == input[i + 1][j] {
            ways += dfs(input, i + 1, j)
        }

        if 0 < j && input[i][j] + 1 == input[i][j - 1] {
            ways += dfs(input, i, j - 1)
        }

        if j < input.index(i).len() - 1 && input[i][j] + 1 == input[i][j + 1] {
            ways += dfs(input, i, j + 1)
        }
        return ways;
    }
    let mut ans = 0;
    for i in 0..input.len() {
        for j in 0..input.index(i).len() {
            if input[i][j] == 0 {
                ans += dfs(input, i, j);
            }
        }
    }
    ans
}
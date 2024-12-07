
fn main() {
    let input = std::io::stdin()
        .lines()
        .filter_map(Result::ok)
        .collect::<Vec<_>>();

    println!("Part 1: {}", part_one(&input));
    println!("Part 1: {}", part_two(&input));
}

fn parse(input: &Vec<String>) -> Vec<(i64, Vec<i64>)> {
    let mut equations: Vec<(i64, Vec<i64>)> = Vec::new();
    for eq in input {
        let mut it= eq.split(':');
        let result = it.next().unwrap()
            .parse::<i64>().unwrap();
        let operands = it.next().unwrap()
            .split_whitespace()
            .map(|x| x.parse::<i64>().unwrap())
            .collect::<Vec<_>>();
        equations.push((result, operands));
    }
    return equations;
}

fn part_one(input: &Vec<String>) -> i64 {
    let mut ans = 0;
    let equations = parse(input);

    fn possible(result: &i64, operands: &Vec<i64>, curr: i64, index: usize) -> bool {
        if index == operands.len() {
            return *result == curr;
        }
        let mut can = false;
        can |=  possible(result, operands, curr + operands[index], index + 1);
        can |=  possible(result, operands, curr * operands[index], index + 1);
        return can;
    }

    for (result, operands) in equations {
        if operands.is_empty() {
            continue;
        }
        if possible(&result, &operands, operands[0], 1) {
            ans += result;
        }

    }
    return ans;
}

fn part_two(input: &Vec<String>) -> i64 {
    let mut ans = 0;
    let equations = parse(input);

    fn possible(result: &i64, operands: &Vec<i64>, curr: i64, index: usize) -> bool {
        if index == operands.len() {
            return *result == curr;
        }
        let mut can = false;
        can |=  possible(result, operands, curr + operands[index], index + 1);
        can |=  possible(result, operands, curr * operands[index], index + 1);
        can |=  possible(result, operands, (curr.to_string() + &operands[index].to_string()).parse::<i64>().unwrap(), index + 1);
        return can;
    }

    for (result, operands) in equations {
        if operands.is_empty() {
            continue;
        }
        if possible(&result, &operands, operands[0], 1) {
            ans += result;
        }

    }
    return ans;
}
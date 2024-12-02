use std::io;

fn main() {
    let data = io::stdin()
        .lines()
        .filter_map(Result::ok)
        .map(|x| {
            x.split_whitespace()
                .map(|x| x.parse::<i64>().unwrap())
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    println!("Part 1: {}", part_one(&data));
    println!("Part 2: {}", part_two(&data));
}

fn report_is_valid(report: &Vec<i64>) -> bool {
    let n = report.len();
    let increasing = if 1 < n { report[0] < report[1] } else { true };
    let mut i = 1;
    while i < n {
        let diff = report[i] - report[i - 1];
        if increasing && 1 <= diff && diff <= 3 {
            i += 1;
            continue;
        }
        if !increasing && -3 <= diff && diff <= -1 {
            i += 1;
            continue;
        }

        return false;
    }
    return true;
}

fn part_one(data: &Vec<Vec<i64>>) -> i64 {
    let mut ans = 0;
    for report in data.into_iter() {
        if report_is_valid(report) {
            ans += 1;
        }
    }
    return  ans;
}

fn part_two(data: &Vec<Vec<i64>>) -> i64 {
    let mut ans = 0;
    for report in data.into_iter() {
        if report_is_valid(report) {
            ans += 1;
        } else {
            for index in 0..report.len() {
                let mut v = report.clone();
                v.remove(index);
                if report_is_valid(&v) {
                    ans += 1;
                    break;
                }
            }
        }
    }
    return  ans;
}
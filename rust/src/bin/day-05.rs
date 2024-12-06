use std::{collections::{HashMap, HashSet}, io, ops::Div};

fn main() {
    let input = io::stdin()
        .lines()
        .filter_map(Result::ok)
        .collect::<Vec<_>>()
        .split(|s| s.trim().is_empty())
        .map(|x| x.to_vec() )
        .collect::<Vec<_>>();
    
    let mut graph: HashMap<i64, HashSet<i64>> = HashMap::new();
    
    input.get(0)
        .unwrap()
        .into_iter()
        .map(|x| x.split(|c| c == '|').collect::<Vec<_>>())
        .map(|x| (x[0].parse::<i64>().unwrap(), x[1].parse::<i64>().unwrap()))
        .for_each(|(x, y)| {
            graph.entry(y).or_default().insert(x);
        });
    
    let is_valid_order = |update: &Vec<i64>| {
        for i in 0..update.len() {
            for j in i+1..update.len() {
                if let Some(should_come_before) = graph.get(&update[i]) {
                    if should_come_before.contains(&update[j]) {
                        return false;
                    }
                }
            }
        }
        return true;
    };

    // Part 1
    let mut ans = 0;
    input.get(1)
        .unwrap()
        .into_iter()
        .map(|x| x.split(',').map(|x| x.parse::<i64>().unwrap()).collect::<Vec<_>>())
        .for_each(|update| {
            if is_valid_order(&update) {
                ans += update.get(update.len().div(2)).unwrap();
            }
        });

    println!("Part 1: {ans}");
    
    let get_order = |update: &Vec<i64>| {
        
        let mut order = Vec::<i64>::new();
        let in_update = update.iter().collect::<HashSet<_>>();
        let mut visited = HashSet::<i64>::new();

        fn dfs(
            x: &i64, 
            visited: &mut HashSet<i64>, 
            in_update: &HashSet<&i64>, 
            graph: &HashMap<i64, HashSet<i64>>,
            order: &mut Vec<i64>
        ) {
            if visited.contains(&x) {
                return;
            }
            visited.insert(*x);

            if let Some(should_come_before) = graph.get(&x) {
                for prev in should_come_before.iter() {
                    if in_update.contains(prev) {
                        dfs(prev, visited, in_update, graph, order);
                    }
                }
            }
            order.push(*x);
        }

        for x in update.iter() {
            if !visited.contains(x) {
                dfs(x, &mut visited, &in_update, &graph, &mut order);
            }
        }
        return order;
    };

    // Part 2
    let mut ans = 0;
    input.get(1)
        .unwrap()
        .into_iter()
        .map(|x| x.split(',').map(|x| x.parse::<i64>().unwrap()).collect::<Vec<_>>())
        .for_each(|update| {
            if !is_valid_order(&update) {
                let order = get_order(&update);
                ans += order.get(order.len().div(2)).unwrap();
            }
        });

    println!("Part 2: {ans}");
}
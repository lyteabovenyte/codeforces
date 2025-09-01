use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let a: Vec<i64> = lines.next().unwrap().unwrap().trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
        let b = a.clone();
        let result = solve(a);
        println!("solve: {}", result);
        let result2 = solve2(b);
        println!("solve1: {}", result2);
    }
}

fn solve(a: Vec<i64>) -> i64 {
    let mut a = a;
    a.sort_unstable();

    let result = a.iter().scan(0, |acc, &x| {
        *acc += x;
        Some(*acc)
    }).collect::<Vec<i64>>();

    let total_waiting_time: i64 = result.iter().take(result.len() - 1).sum();
    total_waiting_time
}

fn solve2(a: Vec<i64>) -> i64 {
    let mut a = a;
    a.sort_unstable();

    let mut total = 0;
    for (index, service_time) in a.iter().enumerate() {
        let num_remaining_queries = (a.len() - (index + 1)) as i64;
        total += *service_time * num_remaining_queries;
    }
    total
}
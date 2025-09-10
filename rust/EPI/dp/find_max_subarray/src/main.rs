use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: Vec<i64> = lines.next().unwrap().unwrap().trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
        let result = solve(a);
        println!("{}", result);
    }
}

fn solve(a: Vec<i64>) -> i64 {
    let mut min_sum = 0;
    let mut max_sum = 0;

    let acc = a.iter().scan(0, |sum, &x| {*sum += x; Some(*sum)}).collect::<Vec<i64>>();
    println!("acc = {:?}", acc);

    for running_sum in acc {
        min_sum = min_sum.min(running_sum);
        max_sum = max_sum.max(running_sum - min_sum);
    }

    max_sum
}
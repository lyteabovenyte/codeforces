/*
    Author: lyteabovenyte
*/

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: Vec<i64> = lines.next().unwrap().unwrap().trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
        let result = solve(a, n);
        println!("{}", result);
    }
}

fn solve(a: Vec<i64>, n: i64) -> i64 {
    let max = a.iter().max().unwrap();
    let indices: Vec<usize> = a.iter()
        .enumerate()
        .filter_map(|(i, x)| if x == max { Some(i) } else { None })
        .collect();

    let increment = if n % 2 != 0 {
        // len is odd
        if indices.iter().any(|&i| i % 2 == 0) {
            (n + 1) / 2
        } else {
            n / 2
        }
    } else {
        // len is even
        if indices.iter().any(|&i| i % 2 == 0) {
            n / 2
        } else {
            (n + 1) / 2
        }
    };

    return *max + increment;
}
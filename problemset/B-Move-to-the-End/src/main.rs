/*
    Author: lyteabovenyte
*/

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: Vec<i64> = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        let result = solve(a, n);
        println!(
            "{}",
            result
                .iter()
                .map(|x| x.to_string())
                .collect::<Vec<String>>()
                .join(" ")
        );
    }
}

fn solve(a: Vec<i64>, n: usize) -> Vec<i64> {
    let mut pmax = vec![0; n + 1];
    let mut psum = vec![0i64; n + 1];

    for j in 0..n {
        pmax[j + 1] = pmax[j].max(a[j]);
        psum[j + 1] = psum[j] + a[j] as i64;
    }

    let mut result = Vec::with_capacity(n);
    for k in 1..=n {
        let val = pmax[n - k + 1] as i64 + (psum[n] - psum[n - k + 1]);
        result.push(val);
    }
    result
}

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
        let a = lines.next().unwrap().unwrap().trim().to_string();
        let result = solve(n, &a);
        println!("{}", if result { "YES" } else { "NO" });
    }
}

fn solve(n: usize, s: &str) -> bool {
    for i in 0..=4 {
        let prefix = &s[0..i];
        let suffix = &s[n - 4 + i..n];
        if format!("{}{}", prefix, suffix) == "2020" {
            return true;
        }
    }
    return false;
}
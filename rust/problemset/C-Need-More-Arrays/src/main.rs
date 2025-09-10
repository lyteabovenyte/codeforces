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
        let result = solve(a);
        println!("{}", result);
    }
}

fn solve(a: Vec<i64>) -> i64 {
    
    let mut ptr = a[0];

    let mut res = 1;
    for k in 1..a.len() {
        if a[k] - ptr > 1 {
            res += 1;
            ptr = a[k];
        } else {
            continue;
        }
    }
    res
}
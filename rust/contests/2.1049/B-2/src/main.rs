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
        let result = solve3(n);
        println!("{}", result);
    }
}

fn solve(n: i64) -> i64 {
    2 * n
}

fn solve2(n: i64) -> i64 {
    8 * n
}

// x * 10^d -x = 0
fn solve3(n: i64) -> i64 {
    let it = n.to_string();
    let mut sz = it.len();
    if it.chars().next().unwrap() == '9' {sz+=1;}
    10_i64.pow(sz as u32) - 1 - n
}
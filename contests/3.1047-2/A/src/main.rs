/*
    Author: lyteabovenyte
*/

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let mut iter = line.split_whitespace();
        let k: i64 = iter.next().unwrap().parse().unwrap();
        let x: i64 = iter.next().unwrap().parse().unwrap();
        let result = solve(k, x);
        println!("{}", result);
    }
}

fn solve(k: i64, x: i64) -> i64 {
    let mut x = x;
    for i in 0..k {
        x <<= 1;
    }
    x
}
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
        let result = solve(n ,a);
        println!("{}", result.iter().map(|&x| x.to_string()).collect::<Vec<String>>().join(" "));
    }
}

fn solve(n: i64, a: Vec<i64>) -> Vec<i64> {
    let mut result = vec![0; n as usize];
    for i in 0..n as usize {
        result[i] = n + 1 - a[i];
    } 
    result
}
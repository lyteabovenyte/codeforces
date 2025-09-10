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
        let a = lines.next().unwrap().unwrap().trim().as_bytes().to_vec();
        let res = solve(n, a);
        println!("{}", res);
    }
}

fn solve(n: i64, a: Vec<u8>) -> i64 {
    let mut fact = a.clone();
    fact.sort_unstable();

    let mut c = 0;
    for i in 0..a.len() {
        if a[i] != fact[i] {
            c += 1;
        }
    }
    c/2
}
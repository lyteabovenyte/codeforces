/*
    Author: lyteabovenyte
*/

use std::io::{self, BufRead};
use std::collections::HashSet;

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: Vec<i64> = lines.next().unwrap().unwrap().split_whitespace().map(|s| s.parse().unwrap()).collect();

        let result = solve(n, a);
        println!("{result}");
    }
}

fn solve(_n: i64, a: Vec<i64>) -> usize {
    // To sort a, declare it as mutable and call sort():
    let mut a = a;
    a.sort();
    
    let mut used = HashSet::new();
    
    for &value in &a {
        if !used.contains(&value) {
            used.insert(value);
        } else if !used.contains(&(value + 1)) {
            used.insert(value + 1);
        }
    }

    used.len()
}
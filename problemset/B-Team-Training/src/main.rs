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
        let mut parts = line.trim().split_whitespace();
        let _n: usize = parts.next().unwrap().parse().unwrap();
        let k: i64 = parts.next().unwrap().parse().unwrap();
        let a_line = lines.next().unwrap().unwrap();
        let a: Vec<i64> = a_line.trim().split_whitespace().map(|s| s.parse().unwrap()).collect();

        let result = solve2(a, k);
        println!("{result:?}");
    }
}

fn solve2(a: Vec<i64>, k: i64) -> i64 {
    let mut result = 0;

    let mut aa = a.clone();
    aa.sort();
    let mut temp = Vec::new();
    for i in (0..aa.len()).rev() {
        temp.push(aa[i]);
        if temp.len() as i64 * temp.iter().min().unwrap() >= k {
            result += 1;
            temp.clear();
        } else {
            continue;
        }
    }

    result
}
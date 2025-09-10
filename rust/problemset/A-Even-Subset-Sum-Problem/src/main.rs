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
        let b = solve(a, n);
        if b.len() == 0 {
            println!("-1");
        } else {
            println!("{}", b.len());
            for i in b {
                print!("{} ", i + 1);
            }
            println!();
        }

    }
}

fn solve(a: Vec<i64>, n: i64) -> Vec<i64> {

    if a.iter().any(|&x| x % 2 == 0) {
        let index = a.iter().position(|&x| x % 2 == 0).unwrap();
        return vec![index as i64];
    }

    // all the elements are odd
    if a.len() < 2 {
        return vec![];
    } else {
        // just find two consecutive odd elements and return them
        for i in 0..(a.len() - 1) {
            if a[i] % 2 == 1 && a[i + 1] % 2 == 1 {
                return vec![i as i64, (i + 1) as i64];
            }
        }
        return vec![];
    }
}
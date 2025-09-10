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
        let result = solve(a, n);
        println!("{}", result);
    }
}

fn solve(a: Vec<i64>, n: i64) -> i64 {
    let mut z = 1;
    let mut init = 0; // init cost
    for i in 0..n {
        init = init + a[i as usize] * z;
        z *= -1;
    }

    // both + or both -
    let mx_pair = if n % 2 == 0 {n - 2} else {n - 1};

    let mut mx_iter = 0;
    for i in 0..n-1 {
        for j in i+1..n {
            mx_iter = mx_iter.max((2*a[i as usize] - i) - (2 * a[j as usize] - j));
        }
    }

    let mx = if mx_pair > mx_iter {mx_pair} else {mx_iter};

    mx + init
}
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
        let a: Vec<i64> = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        let result = solve2(n, a);
        println!("{}", result);
    }
}

fn solve(n: i64, a: Vec<i64>) -> i64 {
    let mut mx = i64::MIN;
    let mut result = 0;
    let mut prev = a[0];

    for i in 0..n as usize {
        if a[i] * prev > 0 {
            mx = mx.max(a[i]);
        } else {
            result += mx;
            mx = a[i];
            prev = a[i];
        }
    }
    result + mx
}

fn solve2(n: i64, a: Vec<i64>) -> i64 {
    let mut sum: i64 = 0;
    let mut i = 0;
    
    while i < n as usize {
        let mut cur = a[i];
        let mut j = i;
        
        // Find the maximum value in consecutive numbers with the same sign
        while j < n as usize && (a[i] > 0) == (a[j] > 0) {
            cur = cur.max(a[j]);
            j += 1;
        }
        
        sum += cur;
        i = j - 1;
        i += 1; // Move to next segment
    }
    
    sum
}

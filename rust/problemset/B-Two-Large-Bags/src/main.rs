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
        println!("{}", if result { "Yes" } else { "No" });

    }
}

fn solve(mut a: Vec<i64>) -> bool {
    a.sort();
    let mut mx = 0;
    
    for i in (0..a.len()).step_by(2) {
        if i + 1 >= a.len() {
            break;
        }
        
        let current_max = mx.max(a[i]);
        let next_max = mx.max(a[i + 1]);
        
        if current_max != next_max {
            return false;
        }
        
        mx = current_max + 1;
    }
    
    true
}
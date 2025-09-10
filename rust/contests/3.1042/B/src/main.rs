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
        let result = solve(n);
        for i in 0..result.len() {
            print!("{} ", result[i]);
        }
        println!();
    }
}

fn solve(n: i64) -> Vec<i64> {
    if n == 2 {
        let result = vec![-1, 2];
        return result;
    }

    if n % 2 == 0 {
        // push to the result -1, -3, -1, -3, -1 so that the length of the result is n, but the last -3 is replaced with -1
        let mut result = vec![-1, 3];
        for _ in 0..(n - 2) / 2 {
            result.push(-1);
            result.push(3);
        }
        result[n as usize - 1] = 2;
        result
    } else {
        // push to the result -1, -3, -1, -3, -1 so that the length of the result is n
        let mut result = vec![-1, 3];
        for _ in 0..(n - 2) / 2 {
            result.push(-1);
            result.push(3);
        }
        // For odd n, we need to add one more -1 to reach length n
        if result.len() < n as usize {
            result.push(-1);
        }
        result
    }
}
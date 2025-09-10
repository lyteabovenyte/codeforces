use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<i64> = line.trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
        let n = parts[0];
        let k = parts[1];
        let nums: Vec<i64> = lines.next().unwrap().unwrap().trim().split_whitespace().map(|s| s.parse().unwrap()).collect();

        let result = solve(nums, k);
        for i in 0..result.len() {
            print!("{}", result[i]);
            if i < result.len() - 1 {
                print!(" ");
            }
        }
        println!();
    }
}

fn gcd(a: i64, b: i64) -> i64 {
    if b == 0 { a.abs() } else { gcd(b, a % b) }
}

fn gcd_of_vector(nums: &Vec<i64>) -> i64 {
    nums.iter().copied().reduce(|a, b| gcd(a, b)).unwrap_or(0)
}

fn solve(nums: Vec<i64>, k: i64) -> Vec<i64> {
    let mut result = nums;
    while gcd_of_vector(&result) == 1 {
        if k % 2 == 1 {
            // k is odd: adding k flips parity
            // Make all numbers even by adding k to odd numbers
            for i in 0..result.len() {
                if result[i] % 2 == 1 {
                    result[i] += k;
                }
            }
        } else {
            for i in 0..result.len() {
                result[i] += (result[i] % (k + 1)) * k;
            }
        }
        // If after this step, the gcd is still 1, the loop will repeat
    }
    result
}
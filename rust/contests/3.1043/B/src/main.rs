use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let result = solve(n);
        println!("{}", result.len());
        if !result.is_empty() {
            for i in result {
                print!("{} ", i);
            }
            println!();
        }
    }
}

// we want to find the integers that by adding multiple 0s to the end of it and adding them together, we can get to n.
fn solve(n: i64) -> Vec<i64> {
    let mut result = Vec::new();
    
    // For each possible k (number of zeros to add)
    // We want x + x*10^k = n, which means x*(1 + 10^k) = n
    // So x = n / (1 + 10^k)
    for k in 1..=18 {  // Start from k=1 since we need to actually add zeros
        let power = 10_i64.pow(k as u32);
        let divisor = 1 + power;
        
        // Check if n is divisible by (1 + 10^k)
        if n % divisor == 0 {
            let x = n / divisor;
            // Make sure x is positive and not already in our result
            if x > 0 && !result.contains(&x) {
                result.push(x);
            }
        }
    }
    
    // Sort the result in ascending order
    result.sort();
    result
}
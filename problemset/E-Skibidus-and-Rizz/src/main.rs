/*
    Author: lyteabovenyte
*/

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let a: Vec<i64> = lines.next().unwrap().unwrap().trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
        let can_we_a = a.clone();
        if can_we(can_we_a) {
            construct(a);
        } else {
            println!("-1");
        }
    }
}

fn can_we(a: Vec<i64>) -> bool{
    let mut n = a[0];
    let mut m = a[1];
    let mut k = a[2];

    let min = if n < m { n } else { m };

    let this = ((n + m) - (k + 1));
    if this < 0 {
        return true;
    }
    
    let truth = (this / 2) + 1;
    truth <= min
}

fn construct(a: Vec<i64>) {
    let n = a[0] as usize;
    let m = a[1] as usize;
    let k = a[2] as usize;

    // Try to construct the string by checking all possible substrings
    let result = construct_string(n, m, k);
    println!("{}", result);
}

fn construct_string(n: usize, m: usize, k: usize) -> String {
    // We need to construct a string where the maximum balance-value among all substrings is exactly k
    // Balance-value = |number_of_zeros - number_of_ones| in a substring
    
    // Strategy: Create a pattern that can achieve exactly k difference
    // The key is to create blocks that allow reaching the maximum difference
    
    if n == 0 {
        // All ones: balance-value = m, so we need m = k
        if m == k {
            return "1".repeat(m);
        } else {
            return String::new(); // This should be handled by can_we
        }
    }
    
    if m == 0 {
        // All zeros: balance-value = n, so we need n = k
        if n == k {
            return "0".repeat(n);
        } else {
            return String::new(); // This should be handled by can_we
        }
    }
    
    // For mixed strings, we need to create a pattern that can reach exactly k
    // One approach: create alternating blocks that can achieve the maximum difference
    
    let mut result = String::new();
    let mut zeros_left = n;
    let mut ones_left = m;
    
    // Try to create a pattern that reaches exactly k difference
    // We'll use a greedy approach that tries to reach the maximum
    
    let mut balance = 0i32;
    let mut reached_max = false;
    
    while zeros_left > 0 || ones_left > 0 {
        let should_add_zero = if zeros_left == 0 {
            false
        } else if ones_left == 0 {
            true
        } else {
            if !reached_max {
                // Try to reach exactly k difference
                // We want to create a substring with balance-value = k
                
                // If we have more zeros, try to create a substring with k more zeros
                if zeros_left >= ones_left + k {
                    // We can create a substring with k more zeros
                    if balance - 1 >= -(k as i32) {
                        true
                    } else {
                        false
                    }
                } else if ones_left >= zeros_left + k {
                    // We can create a substring with k more ones
                    if balance + 1 <= k as i32 {
                        false
                    } else {
                        true
                    }
                } else {
                    // Try to balance while reaching k
                    if balance > 0 {
                        true
                    } else {
                        false
                    }
                }
            } else {
                // We've reached the max, now balance
                if balance > 0 {
                    true
                } else {
                    false
                }
            }
        };
        
        if should_add_zero {
            result.push('0');
            zeros_left -= 1;
            balance -= 1;
        } else {
            result.push('1');
            ones_left -= 1;
            balance += 1;
        }
        
        // Check if we've reached the maximum difference
        if balance.abs() == k as i32 {
            reached_max = true;
        }
    }
    
    result
}
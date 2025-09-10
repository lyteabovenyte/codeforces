/*
    Author: lyteabovenyte
*/

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let _n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: Vec<i64> = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        let result = solve(a);
        println!("{}", result);
    }
}

fn solve(a: Vec<i64>) -> String {
    if a.is_empty() {
        return String::new();
    }
    
    let mut left = 0;
    let mut right = a.len() - 1;
    let mut result = String::new();
    
    // Track the last value added to determine strategy
    let mut last_value = a[0];
    result.push('L');
    left += 1;
    
    // Strategy: -1 for "prefer smaller", +1 for "prefer larger"
    let mut strategy = -1;
    
    while left <= right {
        let left_val = a[left];
        let right_val = a[right];
        
        // Determine which side to choose based on strategy
        let (chosen_val, chosen_side, new_left, new_right) = if strategy == -1 {
            // Prefer smaller values
            if left_val < last_value && right_val < last_value {
                // Both are smaller, pick the smaller one
                if left_val <= right_val {
                    (left_val, 'L', left + 1, right)
                } else {
                    (right_val, 'R', left, right.saturating_sub(1))
                }
            } else if left_val < last_value {
                // Only left is smaller
                (left_val, 'L', left + 1, right)
            } else if right_val < last_value {
                // Only right is smaller
                (right_val, 'R', left, right.saturating_sub(1))
            } else {
                // Both are larger, pick the smaller one
                if left_val <= right_val {
                    (left_val, 'L', left + 1, right)
                } else {
                    (right_val, 'R', left, right.saturating_sub(1))
                }
            }
        } else {
            // Prefer larger values
            if left_val > last_value && right_val > last_value {
                // Both are larger, pick the larger one
                if left_val >= right_val {
                    (left_val, 'L', left + 1, right)
                } else {
                    (right_val, 'R', left, right.saturating_sub(1))
                }
            } else if left_val > last_value {
                // Only left is larger
                (left_val, 'L', left + 1, right)
            } else if right_val > last_value {
                // Only right is larger
                (right_val, 'R', left, right.saturating_sub(1))
            } else {
                // Both are smaller, pick the larger one
                if left_val >= right_val {
                    (left_val, 'L', left + 1, right)
                } else {
                    (right_val, 'R', left, right.saturating_sub(1))
                }
            }
        };
        
        // Update state
        last_value = chosen_val;
        result.push(chosen_side);
        left = new_left;
        right = new_right;
        
        // Switch strategy for next iteration
        strategy = -strategy;
    }
    
    result
}

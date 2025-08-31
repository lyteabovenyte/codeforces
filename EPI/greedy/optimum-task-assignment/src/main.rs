use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        // number of workers
        let n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        // each elements shows how many hours each task to be completed
        let a: Vec<i64> = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();

        let result = solve(n, a);
        println!("{}", result);
    }
}

fn solve(n: i64, a: Vec<i64>) -> i64 {
    let n = n as usize;
    
    // Binary search on the answer
    let mut left = *a.iter().max().unwrap(); // minimum possible answer
    let mut right = a.iter().sum::<i64>();   // maximum possible answer
    
    while left < right {
        let mid = left + (right - left) / 2;
        
        if can_assign_tasks(&a, n, mid) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    left
}

/// Checks if all tasks can be assigned to workers without exceeding the time limit.
/// Uses a greedy approach: always try to pack as many tasks as possible into the current worker.
/// 
/// Returns true if we need ≤ num_workers, false otherwise.
fn can_assign_tasks(tasks: &[i64], num_workers: usize, time_limit: i64) -> bool {
    let mut workers_needed = 0;  // Count of workers we've used so far
    let mut current_sum = 0;     // Total hours for the current worker
    
    // Process each task in order
    for &task in tasks {
        // If any single task exceeds the time limit, it's impossible
        if task > time_limit {
            return false; // Single task exceeds limit
        }
        
        // Try to add this task to the current worker
        if current_sum + task > time_limit {
            // Adding this task would exceed the limit, so finish current worker
            workers_needed += 1;
            current_sum = task;  // Start new worker with this task
        } else {
            // We can add this task to the current worker
            current_sum += task;
        }
    }
    
    // we have current_sum, which means we need at least one more worker to handle it
    if current_sum > 0 {
        workers_needed += 1;
    }
    
    // Check if we need more workers than available
    workers_needed <= num_workers
}

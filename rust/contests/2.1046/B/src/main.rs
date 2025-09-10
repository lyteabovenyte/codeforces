use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n_k_line = lines.next().unwrap().unwrap();
        let n_k: Vec<i64> = n_k_line.trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
        let (n, k) = (n_k[0], n_k[1]);
        let binary_line = lines.next().unwrap().unwrap();
        let a: Vec<i64> = binary_line.trim().chars().map(|c| c.to_digit(10).unwrap() as i64).collect();
        
        match solve_and_check(a, n, k) {
            Some(result) => {
                println!("YES");
                for ele in result {
                    print!("{} ", ele);
                }
                println!();
            }
            None => {
                println!("NO");
            }
        }
    }
}

fn solve_and_check(a: Vec<i64>, n: i64, k: i64) -> Option<Vec<i64>> {
    let n = n as usize;
    let k = k as usize;
    
    // If k > n, we just need to place the largest element at any zero position
    if k > n {
        if !a.iter().any(|&x| x == 0) {
            return None;
        }
        
        let mut result = vec![0; n];
        let mut current = n as i64;
        
        // Place numbers at zero positions first
        for i in 0..n {
            if a[i] == 0 {
                result[i] = current;
                current -= 1;
            }
        }
        
        // Fill remaining positions
        for i in 0..n {
            if result[i] == 0 {
                result[i] = current;
                current -= 1;
            }
        }
        
        return Some(result);
    }
    
    // For k <= n, check each window efficiently using sliding window
    // We need to ensure each window has at least one zero
    let mut zero_count = 0;
    
    // Count zeros in the first window
    for i in 0..k {
        if a[i] == 0 {
            zero_count += 1;
        }
    }
    
    // If first window has no zeros, it's impossible
    if zero_count == 0 {
        return None;
    }
    
    // Check remaining windows
    for i in k..n {
        // Remove the element that's leaving the window
        if a[i - k] == 0 {
            zero_count -= 1;
        }
        // Add the new element entering the window
        if a[i] == 0 {
            zero_count += 1;
        }
        
        // If current window has no zeros, it's impossible
        if zero_count == 0 {
            return None;
        }
    }
    
    // If we reach here, all windows have at least one zero
    // Now build the result using greedy approach
    let mut result = vec![0; n];
    let mut current_num = n as i64;
    
    // First pass: assign the largest numbers to zero positions
    for i in 0..n {
        if a[i] == 0 {
            result[i] = current_num;
            current_num -= 1;
        }
    }
    
    // Second pass: fill the remaining positions (ones) with smaller numbers
    for i in 0..n {
        if a[i] == 1 {
            result[i] = current_num;
            current_num -= 1;
        }
    }
    
    Some(result)
}
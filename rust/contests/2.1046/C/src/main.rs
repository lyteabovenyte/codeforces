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

        let result = solve(a, n);
        println!("{}", result);
    }
}


fn solve(a: Vec<i64>, n: i64) -> i64 {
    let n = n as usize;
    let mut dp = vec![0; n + 1]; // dp[i] = longest neat subsequence using first i elements
    
    // For each value, maintain a count and a queue of positions
    let mut counts = vec![0; n + 1];
    let mut positions = vec![Vec::new(); n + 1];
    
    for i in 0..n {
        // Don't include current element
        dp[i + 1] = dp[i];
        
        let current_val = a[i] as usize;
        if current_val <= n && current_val > 0 {
            counts[current_val] += 1;
            positions[current_val].push(i);
            
            // If we have enough elements to form a block
            if counts[current_val] >= current_val {
                // Use the oldest position as block start
                let start_pos = positions[current_val][counts[current_val] - current_val];
                dp[i + 1] = dp[i + 1].max(dp[start_pos] + current_val as i64);
            }
        }
    }
    
    dp[n]
}

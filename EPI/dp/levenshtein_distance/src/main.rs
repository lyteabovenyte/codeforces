use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let a: Vec<String> = lines.next().unwrap().unwrap().trim().to_string().split_whitespace().map(|s| s.to_string()).collect();
        let result = solve(a);
        println!("{}", result);
    }
}

fn solve(a: Vec<String>) -> i64 {
    let x = &a[0];
    let y = &a[1];
    
    let m = x.len();
    let n = y.len();
    
    // Create DP table with dimensions (m+1) x (n+1)
    let mut dp = vec![vec![0; n + 1]; m + 1];
    
    // Base cases
    for i in 0..=m {
        dp[i][0] = i as i64;  // empty string to string of length i
    }
    for j in 0..=n {
        dp[0][j] = j as i64;  // string of length j to empty string
    }
    
    // Fill the DP table
    for i in 1..=m {
        for j in 1..=n {
            let cost = if x.chars().nth(i-1) == y.chars().nth(j-1) { 0 } else { 1 };
            
            dp[i][j] = (dp[i-1][j] + 1)                    // deletion
                .min(dp[i][j-1] + 1)                       // insertion
                .min(dp[i-1][j-1] + cost);                 // substitution
        }
    }
    
    dp[m][n]  // return the final answer
}
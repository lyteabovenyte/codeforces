use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let a: Vec<String> = lines.next().unwrap().unwrap().trim().to_string().split_whitespace().map(|s| s.to_string()).collect();
        let words = a.clone();
        let lev_dist = solve(words);
        println!("Levenshtein distance: {lev_dist}");
        let first = a[0].clone();
        let second = a[1].clone();
        let lcs = compute_longest_common_subsequence(&first, &second);
        println!("Longest common subsequence: {lcs}");
        println!()
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


fn compute_longest_common_subsequence(a: &str, b: &str) -> i64 {
    // getting two strings, we want to compute the longest common subsequence between them
    // e.g between "orchestra" and "carthorse" the longest common subsequence is "rhs"
    // a subsequence is a sequence of characters that appear in the same order in both strings, but not necessarily consecutively
    // we want to compute the length of the longest common subsequence
    // we can use dynamic programming to compute this
    // we will use a 2D array to store the longest common subsequence of the substrings of a and b
    // dp[i][j] will be the longest common subsequence of the substrings a[0..i] and b[0..j]
    // we will initialize the array with 0s
    // we will then fill the array using the following recurrence relation:
    // if a[i] == b[j], then dp[i][j] = dp[i-1][j-1] + 1
    // else dp[i][j] = max(dp[i-1][j], dp[i][j-1])

    let mut dp = vec![vec![0; b.len() + 1]; a.len() + 1];

    for i in 1..=a.len() {
        for j in 1..=b.len(){
            if a.chars().nth(i - 1) == b.chars().nth(j - 1) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = dp[i - 1][j].max(dp[i][j - 1]);
            }
        }
    }

    dp[a.len()][b.len()]
}
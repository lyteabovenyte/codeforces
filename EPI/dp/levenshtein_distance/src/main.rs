use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let a: Vec<String> = lines.next().unwrap().unwrap().trim().to_string().split_whitespace().map(|s| s.to_string()).collect();
        let words = a.clone();
        let lev_dist = levenshtein_distance(words);
        println!("Levenshtein distance: {lev_dist}");
        let first = a[0].clone();
        let second = a[1].clone();
        let lcs = compute_longest_common_subsequence(&first, &second);
        println!("Longest common subsequence: {lcs}");

        let min_edit = minimum_deletions_for_palindrome(&a[0]);
        println!("Minimum number of edits to make the string \"{}\" a palindrome: {min_edit}", a[0]);

        let closest_regex = closest_string_to_regex("Saturday", "Sunday");
        println!("Closest string to regex: {closest_regex}");

        println!("Is \"gattaca\" an interleaving of \"gtaa\" and \"atc\"? {}", is_interleaving("gattaca", "gtaa", "atc")); // true
        println!("Is \"gatacta\" an interleaving of \"gtaa\" and \"atc\"? {}", is_interleaving("gatacta", "gtaa", "atc")); // false
        println!("Is \"gattaca\" an interleaving of \"gtaa\" and \"atc\"? {}", is_interleaving("alaei", "aa", "lei"));

        println!();
    }
}

fn levenshtein_distance(a: Vec<String>) -> i64 {
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


/// given a string, we want to compute the minimum number of deletions to make it a palindrome
/// a palindrome is a string that reads the same forwards and backwards
/// we can use dynamic programming to compute this
fn minimum_deletions_for_palindrome(a: &str) -> i64 {
    let n = a.len();
    
    // Create a 2D DP table where dp[i][j] represents the minimum deletions
    // needed to make the substring a[i..j] a palindrome
    let mut dp = vec![vec![0; n]; n];
    
    // Base case: single characters are already palindromes
    for i in 0..n {
        dp[i][i] = 0;
    }
    
    // Fill the DP table for substrings of length 2 and above
    // len, i and j are ensuring that we are processing the dp table in the correct order
    // so when we need dp[i][j], we have already computed dp[i+1][j-1] and dp[i+1][j] and dp[i][j-1]

    // Dependency Analysis:
    // For dp[i][j] to be computed correctly, we need:
    // dp[i+1][j-1]: This is for a substring of length len-2 (inner substring)
    // dp[i+1][j]: This is for a substring of length len-1 (left substring)
    // dp[i][j-1]: This is for a substring of length len-1 (right substring)
    
    for len in 2..=n { // 2..=n means we process substrings of length 2, 3, 4, ..., n
        for i in 0..=n-len { // For each length, try all possible starting positions
            let j = i + len - 1; // Calculate the ending index for the current starting position
            
            if a.chars().nth(i) == a.chars().nth(j) {
                // If characters match, no deletion needed for these positions
                dp[i][j] = dp[i+1][j-1]; // get the inner substring and check for min deletions
            } else {
                // If characters don't match, we need to delete one of them
                // Take minimum of deleting left character or right character
                dp[i][j] = 1 + dp[i+1][j].min(dp[i][j-1]);
            }
        }
    }
    
    dp[0][n-1]
}

// Given a string `A` and a regular expression `r`, what is the string in the language of the `r` that is closets the the string `A`
// the distance between `A` and `r` is the levenshtein distance between them
// we can use dynamic programming to compute this
// note that we want the closest string in the language of the regex to the string `A` and return it.
fn closest_string_to_regex(a: &str, r: &str) -> i64 {

    let mut dp = vec![vec![0; r.len() + 1]; a.len() + 1];

    for i in 1..=a.len() {
        for j in 1..=r.len() {
            if a.chars().nth(i - 1) == r.chars().nth(j - 1) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = 0;
            }
        }
    }

    dp[a.len()][r.len()]
}


// define a string `t` to be an interleaving of string `s1` and `s2` if there is a way to interleave the characters
// of `s1` and `s2`, keeping the left-to-right order of each, to obtain `t`.
// for example, if `s1` = "gtaa" and `s2` = "atc", then "gattaca" and "gtataac" can be formed as interleavings of `s1` and `s2`.
// but "gatacta" cannot.
// Determine if a string `t` is an interleaving of strings `s1` and `s2`.
fn is_interleaving(t: &str, s1: &str, s2: &str) -> bool {
    let len1 = s1.len();
    let len2 = s2.len();
    let len_t = t.len();
    
    // If the total length doesn't match, it's impossible
    if len1 + len2 != len_t {
        return false;
    }
    
    // Create DP table: dp[i][j] = true if t[0..i+j] can be formed by interleaving
    // s1[0..i] and s2[0..j]
    let mut dp = vec![vec![false; len2 + 1]; len1 + 1];
    
    // Base case: empty strings can form empty string
    dp[0][0] = true;
    
    // Fill first row: using only s1
    for i in 1..=len1 {
        if s1.chars().nth(i - 1) == t.chars().nth(i - 1) {
            dp[i][0] = dp[i - 1][0];
        }
    }
    
    // Fill first column: using only s2
    for j in 1..=len2 {
        if s2.chars().nth(j - 1) == t.chars().nth(j - 1) {
            dp[0][j] = dp[0][j - 1];
        }
    }
    
    // Fill the rest of the DP table
    for i in 1..=len1 {
        for j in 1..=len2 {
            let t_char = t.chars().nth(i + j - 1);
            let s1_char = s1.chars().nth(i - 1);
            let s2_char = s2.chars().nth(j - 1);
            
            // Check if current character in t matches s1[i-1]
            if t_char == s1_char {
                dp[i][j] = dp[i][j] || dp[i - 1][j];
            }
            
            // Check if current character in t matches s2[j-1]
            if t_char == s2_char {
                dp[i][j] = dp[i][j] || dp[i][j - 1];
            }
        }
    }
    
    dp[len1][len2]
}


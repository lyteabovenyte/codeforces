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
        
        // first we should check
        if check(a.clone(), k) {
            let solution = solve(a, k, n);
            if !solution.is_empty() {
                println!("YES");
                println!("{}", solution.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(" "));
            } else {
                println!("NO");
            }
        } else {
            println!("NO");
        }
    }
}

fn solve(a: Vec<i64>, k: i64, n: i64) -> Vec<i64> {
    let n = n as usize;
    let k = k as usize;
    
    // If k > n, we just need to place the largest element at any zero position
    if k > n {
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
        
        return result;
    }
    
    // For each position, we need to check if it can be the maximum in any window
    let mut can_be_max = vec![true; n];
    
    // For each window of length k, mark positions that cannot be the maximum
    for start in 0..=n - k {
        let window = start..start + k;
        let mut has_zero = false;
        
        // Check if this window has any zero positions
        for pos in window.clone() {
            if a[pos] == 0 {
                has_zero = true;
                break;
            }
        }
        
        // If no zero positions in this window, it's impossible
        if !has_zero {
            return vec![];
        }
        
        // Mark positions with 1s as cannot be maximum in this window
        for pos in window {
            if a[pos] == 1 {
                can_be_max[pos] = false;
            }
        }
    }
    
    // Now we know which positions can be maximum
    // We need to assign numbers so that in each window, the maximum is at a zero position
    let mut result = vec![0; n];
    let mut used = vec![false; n + 1];
    
    // Start with the largest number and place it at a valid position
    let mut current_num = n as i64;
    
    // First, place numbers at positions that can be maximum
    for i in 0..n {
        if can_be_max[i] && result[i] == 0 {
            result[i] = current_num;
            used[current_num as usize] = true;
            current_num -= 1;
        }
    }
    
    // Fill remaining positions
    for i in 0..n {
        if result[i] == 0 {
            while used[current_num as usize] {
                current_num -= 1;
            }
            result[i] = current_num;
            used[current_num as usize] = true;
            current_num -= 1;
        }
    }
    
    // Verify the solution
    if is_valid_solution(&result, &a, k) {
        result
    } else {
        vec![]
    }
}

fn is_valid_solution(perm: &Vec<i64>, a: &Vec<i64>, k: usize) -> bool {
    let n = perm.len();
    if k > n {
        return true;
    }
    
    for i in 0..=n - k {
        let subseq = &perm[i..i + k];
        let max_val = subseq.iter().max().unwrap();
        let max_pos = i + subseq.iter().position(|&x| x == *max_val).unwrap();
        
        // The maximum element should be at a position where a[i] == 0
        if a[max_pos] != 0 {
            return false;
        }
    }
    true
}

fn check(a: Vec<i64>, k: i64) -> bool {
    let n = a.len();
    if k > n as i64 {
        if !a.iter().any(|&x| x == 0) {
            return false;
        }
        return true;
    }

    // todo: check for k == 0
    
    let k = k as usize;
    for i in 0..=n - k {
        let subseq = &a[i..i + k];
        if !subseq.iter().any(|&x| x == 0) {
            return false;
        }
    }
    true
}
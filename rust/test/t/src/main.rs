use std::io::{self, BufRead};

fn collatz_step(x: i64) -> i64 {
    if x % 2 == 0 {
        x / 2
    } else {
        3 * x + 1
    }
}

fn find_initial_value(k: i32, final_value: i32) -> i32 {
    let mut all_results = Vec::new();
    
    for start in 1..=1000 {
        let mut current = start as i64;
        let mut valid = true;
        
        for _ in 0..k {
            current = collatz_step(current);
            if current > 1_000_000 {
                valid = false;
                break;
            }
        }
        
        if valid && current == final_value as i64 {
            all_results.push(start);
        }
    }
    
    if all_results.is_empty() {
        return 0;
    }
    
    if all_results.len() == 1 {
        return all_results[0];
    }
    
    let odd_results: Vec<i32> = all_results.iter().filter(|&&x| x % 2 == 1).cloned().collect();
    
    if !odd_results.is_empty() {
        return *odd_results.iter().max().unwrap();
    }
    
    *all_results.iter().max().unwrap()
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    if let Some(Ok(first_line)) = lines.next() {
        if let Ok(t) = first_line.trim().parse::<i32>() {
            for _ in 0..t {
                if let Some(Ok(line)) = lines.next() {
                    let parts: Vec<&str> = line.trim().split_whitespace().collect();
                    if parts.len() >= 2 {
                        if let (Ok(k), Ok(x)) = (parts[0].parse::<i32>(), parts[1].parse::<i32>()) {
                            println!("{}", find_initial_value(k, x));
                        }
                    }
                }
            }
        }
    }
}

use std::io::{self, BufRead};

fn solve_lever(a: &mut Vec<i32>, b: &Vec<i32>) -> i32 {
    let mut iterations = 0;
    
    loop {
        iterations += 1;
        
        // Step 1: Decrease a_i if a_i > b_i
        let mut decreased = false;
        for i in 0..a.len() {
            if a[i] > b[i] {
                a[i] -= 1;
                decreased = true;
                break; // Only decrease one element per iteration
            }
        }
        
        // If no decrease was possible, terminate
        if !decreased {
            break;
        }
        
        // Step 2: Increase a_i if a_i < b_i
        for i in 0..a.len() {
            if a[i] < b[i] {
                a[i] += 1;
                break; // Only increase one element per iteration
            }
        }
    }
    
    iterations
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
    
    for _ in 0..t {
        let _n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
        
        // Read array a
        let a_line = lines.next().unwrap().unwrap();
        let mut a: Vec<i32> = a_line
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        
        // Read array b
        let b_line = lines.next().unwrap().unwrap();
        let b: Vec<i32> = b_line
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        
        println!("{}", solve_lever(&mut a, &b));
    }
}

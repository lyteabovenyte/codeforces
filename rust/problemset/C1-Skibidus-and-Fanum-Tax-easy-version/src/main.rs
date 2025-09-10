use std::io::{self, BufRead};

fn solve() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: usize = lines.next().unwrap().unwrap().parse().unwrap();
    
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<usize> = line.split_whitespace().map(|x| x.parse().unwrap()).collect();
        let _n = parts[0];
        let _m = parts[1]; 
        
        let line = lines.next().unwrap().unwrap();
        let a: Vec<i64> = line.split_whitespace().map(|x| x.parse().unwrap()).collect();
        
        let line = lines.next().unwrap().unwrap();
        let b: Vec<i64> = line.split_whitespace().map(|x| x.parse().unwrap()).collect();
        let b_val = b[0];
        
        let mut possible = true;
        let mut last = i64::MIN;
        
        for &a_val in &a {
            let val1 = a_val;
            let val2 = b_val - a_val;
            
            // Choose the smallest value that is >= last
            let mut chosen = i64::MAX;
            
            if val1 >= last {
                chosen = chosen.min(val1);
            }
            if val2 >= last {
                chosen = chosen.min(val2);
            }
            
            if chosen == i64::MAX {
                possible = false;
                break;
            }
            
            last = chosen;
        }
        
        if possible {
            println!("YES");
        } else {
            println!("NO");
        }
    }
}

fn main() {
    solve();
}

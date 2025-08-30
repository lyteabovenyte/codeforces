use std::io::{self, BufRead};

fn main() {
    // Precompute costs for each power of 3
    let mut cost = Vec::new();
    let mut c: i64 = 3;
    let mut cnt: i64 = 1;
    for _ in 0..21 {
        cost.push(c);
        c = 3 * c + cnt;
        cnt *= 3;
    }

    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: usize = lines.next().unwrap().unwrap().parse().unwrap();
    
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let mut parts = line.split_whitespace();
        let n: u64 = parts.next().unwrap().parse().unwrap();
        let k: u64 = parts.next().unwrap().parse().unwrap();
        
        // Convert n to ternary representation
        let mut tr = Vec::new();
        let mut min_k = 0;
        let mut temp_n = n;
        
        while temp_n > 0 {
            tr.push((temp_n % 3) as i64);
            min_k += temp_n % 3;
            temp_n /= 3;
        }
        
        if min_k > k {
            println!("-1");
            continue;
        }
        
        let mut remaining_k = (k - min_k) / 2;
        
        // Optimize by breaking larger deals into smaller ones
        for i in (1..tr.len()).rev() {
            if tr[i] <= remaining_k as i64 {
                tr[i - 1] += 3 * tr[i];
                remaining_k -= tr[i] as u64;
                tr[i] = 0;
            } else {
                tr[i - 1] += (remaining_k * 3) as i64;
                tr[i] -= remaining_k as i64;
                break;
            }
        }
        
        // Calculate final cost
        let mut ans: i64 = 0;
        for i in (0..tr.len()).rev() {
            ans += cost[i] * tr[i];
        }
        
        println!("{}", ans);
    }
}

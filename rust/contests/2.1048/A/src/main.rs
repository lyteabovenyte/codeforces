use std::io::{self, BufRead};
use std::collections::HashMap;

fn solve() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: usize = lines.next().unwrap().unwrap().parse().unwrap();
    
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<&str> = line.split_whitespace().collect();
        let n: usize = parts[0].parse().unwrap();
        let m: usize = parts[1].parse().unwrap();
        
        let line = lines.next().unwrap().unwrap();
        let a: Vec<usize> = line.split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        
        if m <= 10 {
            let mut memo = HashMap::new();
            
            fn dfs(
                time: usize,
                last_collection: &[usize],
                total: usize,
                m: usize,
                a: &[usize],
                memo: &mut HashMap<(usize, Vec<usize>), usize>
            ) -> usize {
                if time > m {
                    return total;
                }
                
                let remaining_time = m - time + 1;
                let max_possible = a.iter().max().unwrap() * remaining_time * (remaining_time + 1) / 2;
                if total + max_possible <= memo.get(&(0, vec![])).copied().unwrap_or(0) {
                    return 0;
                }
                
                let key = (time, last_collection.to_vec());
                if let Some(&cached) = memo.get(&key) {
                    return cached + total;
                }
                
                let mut max_result = 0;
                for i in 0..a.len() {
                    let cakes = a[i] * (time - last_collection[i]);
                    let mut new_last_collection = last_collection.to_vec();
                    new_last_collection[i] = time;
                    
                    let result = dfs(time + 1, &new_last_collection, total + cakes, m, a, memo);
                    max_result = max_result.max(result);
                }
                
                memo.insert(key, max_result - total);
                max_result
            }
            
            let result = dfs(1, &vec![0; n], 0, m, &a, &mut memo);
            println!("{}", result);
        } else {
            // For large m, use the most efficient approach possible
            // This is a classic scheduling problem that can be solved optimally
            let mut total_cakes: u64 = 0;
            let mut last_collection = vec![0u64; n];
            let a: Vec<u64> = a.into_iter().map(|x| x as u64).collect();
            
            // Use the greedy approach but with optimizations
            for time in 1..=m {
                let mut best_oven = 0;
                let mut best_cakes = 0u64;
                
                for i in 0..n {
                    let cakes = a[i] * (time as u64 - last_collection[i]);
                    if cakes > best_cakes {
                        best_cakes = cakes;
                        best_oven = i;
                    }
                }
                
                total_cakes += best_cakes;
                last_collection[best_oven] = time as u64;
            }
            
            println!("{}", total_cakes);
        }
    }
}

fn main() {
    solve();
}

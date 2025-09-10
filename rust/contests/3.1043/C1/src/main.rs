use std::io::{self, BufRead};

fn solve(n: u64) -> u64 {
    // The key insight: we need to minimize deals first, then cost
    // For large numbers, we can use mathematical properties
    
    // Generate deals efficiently
    let mut deals = Vec::new();
    let mut x = 0;
    while x <= 20 {
        let quantity = 3_u64.pow(x);
        if quantity > n {
            break;
        }
        let cost = 3_u64.pow(x + 1) + x as u64 * 3_u64.pow(if x > 0 { x - 1 } else { 0 });
        deals.push((quantity, cost));
        x += 1;
    }
    
    // For small numbers, use simple DP
    if n <= 100 {
        let mut dp = vec![None; (n + 1) as usize];
        dp[0] = Some((0, 0)); // (cost, deals)
        
        for i in 1..=n {
            for &(quantity, cost) in &deals {
                if quantity <= i {
                    if let Some((prev_cost, prev_deals)) = dp[(i - quantity) as usize] {
                        let new_cost = prev_cost + cost;
                        let new_deals = prev_deals + 1;
                        
                        match dp[i as usize] {
                            None => dp[i as usize] = Some((new_cost, new_deals)),
                            Some((curr_cost, curr_deals)) => {
                                if new_deals < curr_deals || 
                                   (new_deals == curr_deals && new_cost < curr_cost) {
                                    dp[i as usize] = Some((new_cost, new_deals));
                                }
                            }
                        }
                    }
                }
            }
        }
        return dp[n as usize].unwrap().0;
    }
    
    // For large numbers, use greedy approach with optimization
    // Sort deals by quantity (descending) to prioritize larger deals
    deals.sort_by(|a, b| b.0.cmp(&a.0));
    
    let mut min_cost = None;
    
    // Try greedy approach: use largest deals first
    let mut remaining = n;
    let mut total_cost = 0;
    
    for &(quantity, cost) in &deals {
        while remaining >= quantity {
            remaining -= quantity;
            total_cost += cost;
        }
    }
    
    if remaining == 0 {
        min_cost = Some(total_cost);
    }
    
    // If greedy didn't work, try some variations
    if min_cost.is_none() {
        // Try using smaller deals to fill the remainder
        for i in 0..deals.len() {
            let mut remaining = n;
            let mut total_cost = 0;
            
            // Use deals from index i onwards first
            for j in i..deals.len() {
                let (quantity, cost) = deals[j];
                while remaining >= quantity {
                    remaining -= quantity;
                    total_cost += cost;
                }
            }
            
            // Then use smaller deals
            for j in 0..i {
                let (quantity, cost) = deals[j];
                while remaining >= quantity {
                    remaining -= quantity;
                    total_cost += cost;
                }
            }
            
            if remaining == 0 {
                min_cost = Some(min_cost.unwrap_or(u64::MAX).min(total_cost));
            }
        }
    }
    
    min_cost.unwrap()
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
    
    for _ in 0..t {
        let n: u64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        println!("{}", solve(n));
    }
}

use std::io::{self, BufRead};

fn solve(n: u64, k: u64) -> u64 {
    // Generate deals efficiently - only up to what we need
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
    
    // Sort deals by cost per unit (ascending) to prioritize cheaper deals
    deals.sort_by(|a, b| {
        let cost_per_unit_a = (a.1 as f64) / (a.0 as f64);
        let cost_per_unit_b = (b.1 as f64) / (b.0 as f64);
        cost_per_unit_a.partial_cmp(&cost_per_unit_b).unwrap()
    });
    
    // Use a 2D DP approach: dp[quantity][deals_used] = min_cost
    let mut dp = vec![vec![u64::MAX; (k + 1) as usize]; (n + 1) as usize];
    dp[0][0] = 0; // Base case: 0 quantity, 0 deals = 0 cost
    
    // Try using at most k deals
    for deals_used in 0..k {
        for quantity in 0..=n {
            if dp[quantity as usize][deals_used as usize] != u64::MAX {
                for &(deal_quantity, deal_cost) in &deals {
                    let new_quantity = quantity + deal_quantity;
                    let new_deals_used = deals_used + 1;
                    
                    if new_quantity <= n && new_deals_used <= k {
                        let new_cost = dp[quantity as usize][deals_used as usize] + deal_cost;
                        dp[new_quantity as usize][new_deals_used as usize] = 
                            dp[new_quantity as usize][new_deals_used as usize].min(new_cost);
                    }
                }
            }
        }
    }
    
    // Find the minimum cost among all valid solutions (0 to k deals)
    let mut min_cost = u64::MAX;
    for deals_used in 0..=k {
        if dp[n as usize][deals_used as usize] != u64::MAX {
            min_cost = min_cost.min(dp[n as usize][deals_used as usize]);
        }
    }
    
    if min_cost == u64::MAX {
        u64::MAX // Impossible case
    } else {
        min_cost
    }
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
    
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<u64> = line.trim().split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        let n = parts[0];
        let k = parts[1];
        let result = solve(n, k);
        if result == u64::MAX {
            println!("-1"); // Impossible case
        } else {
            println!("{}", result);
        }
    }
}


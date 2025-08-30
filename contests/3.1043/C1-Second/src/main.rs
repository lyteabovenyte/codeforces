use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n: u64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let result = solve(n);
        println!("{}", result);
    }
}

fn solve(n: u64) -> u64 {
    
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

    // greedy
    let mut total_cost = 0;
    let mut remaining = n;

    // sort
    deals.sort_by(|a, b| b.1.cmp(&a.1));

    for &(quantity, cost) in &deals {
        while remaining >= quantity {
            remaining -= quantity;
            total_cost += cost;
        }
    }
    total_cost
}

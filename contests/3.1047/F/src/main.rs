use std::io::{self, Read};

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.trim().split('\n');
    
    let t: usize = lines.next().unwrap().parse().unwrap();
    
    for _ in 0..t {
        let n: usize = lines.next().unwrap().parse().unwrap();
        let a: Vec<i32> = lines.next().unwrap().split_whitespace()
            .map(|x| x.parse().unwrap()).collect();
        let b: Vec<i32> = lines.next().unwrap().split_whitespace()
            .map(|x| x.parse().unwrap()).collect();
        
        let mut total = 0i64;
        
        for l in 0..n {
            for r in l..n {
                let x = &a[l..=r];
                let y = &b[l..=r];
                total += f(x, y);
            }
        }
        
        println!("{}", total);
    }
}

fn f(x: &[i32], y: &[i32]) -> i64 {
    let m = x.len();
    if m == 0 { return 0; }
    
    let mut prefix_max_x = vec![0; m];
    prefix_max_x[0] = x[0];
    for i in 1..m {
        prefix_max_x[i] = prefix_max_x[i-1].max(x[i]);
    }
    
    use std::collections::HashMap;
    let mut memo = HashMap::new();
    
    fn dp(pos: usize, curr_max: i32, x: &[i32], y: &[i32], prefix_max_x: &[i32], memo: &mut HashMap<(usize, i32), i32>) -> i32 {
        if pos >= x.len() {
            return 0;
        }
        
        let key = (pos, curr_max);
        if let Some(&cached) = memo.get(&key) {
            return cached;
        }
        
        let required_max = prefix_max_x[pos];
        let min_val = if pos == 0 { 1 } else { curr_max };
        
        if required_max < min_val {
            memo.insert(key, 0);
            return 0;
        }
        
        let result = if required_max > curr_max {
            let match_bonus = if y[pos] == required_max { 1 } else { 0 };
            match_bonus + dp(pos + 1, required_max, x, y, prefix_max_x, memo)
        } else {
            let match_bonus = if y[pos] >= min_val && y[pos] <= required_max { 1 } else { 0 };
            match_bonus + dp(pos + 1, curr_max, x, y, prefix_max_x, memo)
        };
        
        memo.insert(key, result);
        result
    }
    
    let result = dp(0, 0, x, y, &prefix_max_x, &mut memo);
    result as i64
}

use std::io::{self, BufRead};

fn solve(lines: &mut std::io::Lines<std::io::StdinLock>) {
    let _n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
    let nums: Vec<i32> = lines.next().unwrap().unwrap().trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
    
    let mut ans = 0;
    for &num in &nums {
        ans += num + if num == 0 { 1 } else { 0 };
    }
    
    println!("{}", ans);
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: i32 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        solve(&mut lines);
    }
}

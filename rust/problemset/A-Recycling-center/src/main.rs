use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let parts: Vec<i64> = lines.next().unwrap().unwrap().trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
        let _n = parts[0];
        let c = parts[1];
        let a: Vec<i64> = lines.next().unwrap().unwrap().trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
        let result = solve(a, c);
        println!("{}", result);
    }
}

fn solve(a: Vec<i64>, c: i64) -> i64 {
    let mut arr = a;
    
    while let Some((idx, _)) = arr.iter().enumerate().filter(|&(_, &val)| val <= c).max_by_key(|&(_, &val)| val) {
        arr.remove(idx);
        for x in arr.iter_mut() {
            *x *= 2;
        }
    }

    arr.iter().count() as i64
}
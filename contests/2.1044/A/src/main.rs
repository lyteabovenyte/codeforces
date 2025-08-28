use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: Vec<i64> = lines.next().unwrap().unwrap().trim().split_whitespace().map(|s| s.parse().unwrap()).collect();

        if check(n, a) {
            println!("YES");
        } else {
            println!("NO");
        }
    }
}
fn check(n: i64, a: Vec<i64>) -> bool {
    use std::collections::HashMap;
    let mut freq = HashMap::new();
    for &val in &a {
        *freq.entry(val).or_insert(0) += 1;
    }
    for &count in freq.values() {
        if count >= 2 {
            return true;
        }
    }
    false
}

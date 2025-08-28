use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<i64> = line.trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
        if check(parts[0], parts[1], parts[2]) {
            println!("YES");
        } else {
            println!("NO");
        }
    }
}

fn check(n: i64, a: i64, b: i64) -> bool {
    if n % 2 == 0 {
        if b % 2 != 0 {
            return false;
        } else {
            // b is even and n is even
            if a > b {
                if a % 2 != 0 {
                    return false;
                } else {
                    // a, b, n are all even
                    return true;
                }
            } else {
                // b > a
                return true;
            }
        }

    } else {
        if b % 2 == 0 {
            return false;
        } else {
            // b is odd and n is odd
            if a > b {
                if a % 2 == 0 {
                    return false;
                } else {
                    // a, b, n are all odd
                    return true;
                }
            } else {
                // b > a
                return true;
            }
        }
    }
}

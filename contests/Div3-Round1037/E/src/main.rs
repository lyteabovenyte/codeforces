use std::io::{self, BufRead};

fn gcd(mut a: i64, mut b: i64) -> i64 {
    while b != 0 {
        let tmp = b;
        b = a % b;
        a = tmp;
    }
    a.abs()
}

fn lcm(a: i64, b: i64) -> i64 {
    a / gcd(a, b) * b
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines().map(|l| l.unwrap());

    let t: usize = lines.next().unwrap().parse().unwrap();

    for _ in 0..t {
        let n: usize = lines.next().unwrap().parse().unwrap();

        if n == 0 {
            println!("Yes");
            continue;
        }

        let p: Vec<i64> = lines
            .next()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse::<i64>().unwrap())
            .collect();

        let s: Vec<i64> = lines
            .next()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse::<i64>().unwrap())
            .collect();

        let mut a = vec![0i64; n];
        for i in 0..n {
            a[i] = lcm(p[i], s[i]);
        }

        // Compute prefix and suffix GCDs
        let mut prefix = vec![0i64; n];
        let mut suffix = vec![0i64; n];

        prefix[0] = a[0];
        for i in 1..n {
            prefix[i] = gcd(prefix[i - 1], a[i]);
        }

        suffix[n - 1] = a[n - 1];
        for i in (0..n - 1).rev() {
            suffix[i] = gcd(suffix[i + 1], a[i]);
        }

        let mut ok = true;
        for i in 0..n {
            if prefix[i] != p[i] || suffix[i] != s[i] {
                ok = false;
                break;
            }
        }

        println!("{}", if ok { "Yes" } else { "No" });
    }
}

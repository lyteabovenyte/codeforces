use std::io::{self, BufRead};

fn get_divisors(n: u64) -> Vec<u64> {
    let mut divs = Vec::new();
    let sqrt_n = (n as f64).sqrt() as u64;
    for i in 1..=sqrt_n {
        if n % i == 0 {
            divs.push(i);
            if i != n / i {
                divs.push(n / i);
            }
        }
    }
    divs.sort_unstable();
    divs
}

fn gcd(mut a: u64, mut b: u64) -> u64 {
    while b != 0 {
        let temp = b;
        b = a % b;
        a = temp;
    }
    a
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t_line = lines.next().unwrap().unwrap();
    let t: usize = t_line.trim().parse().unwrap();

    // pow10 k
    let mut pow10: Vec<u64> = vec![1];
    let mut current = 1u64;
    for _ in 0..9 {
        current *= 10;
        pow10.push(current);
    }

    // rdiv k  1..9
    let mut r_divs: Vec<Vec<u64>> = vec![vec![]; 10];
    for k in 1..=9 {
        let r = pow10[k] - 1;
        r_divs[k] = get_divisors(r);
    }

    for _ in 0..t {
        let x_line = lines.next().unwrap().unwrap();
        let x: u64 = x_line.trim().parse().unwrap();

        let x_divs = get_divisors(x);

        let mut found = false;
        let mut ans = 0u64;

        for k in 1..=9 {
            let miny = pow10[k - 1];
            let maxy = pow10[k] - 1;

            for &g in &x_divs {
                let a = x / g;

                for &b in &r_divs[k] {
                    if b <= a {
                        continue;
                    }
                    if gcd(a, b) != 1 {
                        continue;
                    }
                    let diff = b - a;
                    let y = g * diff;
                    if y >= miny && y <= maxy {
                        ans = y;
                        found = true;
                        break;
                    }
                }
                if found {
                    break;
                }
            }
            if found {
                break;
            }
        }

        println!("{}", ans);
    }
}
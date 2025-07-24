use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut input = stdin.lock().lines().map(|l| l.unwrap());

    let t: usize = input.next().unwrap().parse().unwrap();

    for _ in 0..t {
        let n: usize = input.next().unwrap().parse().unwrap();
        let a: Vec<i32> = input
            .next()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();

        let mut out = vec!['0'; n];

        // From left to right: maintain min
        let mut min_val = a[0];
        for i in 0..n {
            min_val = min_val.min(a[i]);
            if min_val >= a[i] {
                out[i] = '1';
            }
        }

        // From right to left: maintain max
        let mut max_val = a[n - 1];
        for i in (0..n).rev() {
            max_val = max_val.max(a[i]);
            if max_val <= a[i] {
                out[i] = '1';
            }
        }

        println!("{}", out.iter().collect::<String>());
    }
}

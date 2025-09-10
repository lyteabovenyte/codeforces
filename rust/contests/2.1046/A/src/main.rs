use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let a: Vec<i64> = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();

        let result = solve(a);
        if result {
            println!("YES");
        } else {
            println!("NO");
        }
    }
}

// here we can solve the problem using the following steps:
fn solve(a: Vec<i64>) -> bool {
    let mut result = 0;

    // first we need to split the vector in 2 parts:
    let mut r = a
        .iter()
        .enumerate()
        .filter(|(index, _)| index % 2 == 0)
        .map(|(_, score)| score)
        .collect::<Vec<&i64>>();
    let mut k = a
        .iter()
        .enumerate()
        .filter(|(index, _)| index % 2 == 1)
        .map(|(_, score)| score)
        .collect::<Vec<&i64>>();

    let first_half = vec![*r[0], *k[0]];
    let second_half = vec![*r[1] - *r[0], *k[1] - *k[0]];


    if !check(first_half) {
        return false;
    }
    if !check(second_half) {
        return false;
    }

    return true;
}

fn check(a: Vec<i64>) -> bool {
    if a[0] > a[1] {
        if a[0] > 2 * a[1] + 2{
            return false;
        }
    } else {
        if a[1] > 2 * a[0] + 2 {
            return false;
        }
    }
    true
}

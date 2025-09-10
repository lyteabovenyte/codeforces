use std::cmp::min;
use std::collections::*;
use std::io::{self, Read};

const INF: i64 = 1_000_000_000_000_000_016;

fn tc(input: &mut impl Iterator<Item = i64>) {
    let n = input.next().unwrap();
    let m = input.next().unwrap();
    let mut va: Vec<i64> = (0..n).map(|_| input.next().unwrap()).collect();
    let mut vb: Vec<i64> = (0..m).map(|_| input.next().unwrap()).collect();

    vb.sort();
    va.insert(0, -INF);
    let mut n = n + 1;

    for i in 1..n as usize {
        let it = vb.binary_search_by(|&a| {
            // equivalent to C++ lambda in lower_bound
            if a - va[i] < va[i - 1] {
                std::cmp::Ordering::Less
            } else {
                std::cmp::Ordering::Greater
            }
        });
        
        let j = match it {
            Ok(idx) | Err(idx) if idx < vb.len() => vb[idx],
            _ => continue,
        };

        if va[i] < va[i - 1] && j - va[i] < va[i - 1] {
            continue;
        }
        va[i] = min(
            if va[i] < va[i - 1] { INF } else { va[i] },
            if j - va[i] < va[i - 1] { INF } else { j - va[i] },
        );
    }

    if va.windows(2).all(|w| w[0] <= w[1]) {
        println!("YES");
    } else {
        println!("NO");
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace().map(|s| s.parse::<i64>().unwrap());

    let t = iter.next().unwrap();
    for _ in 0..t {
        tc(&mut iter);
    }
}
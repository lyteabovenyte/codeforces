use std::io::{self, BufRead};

fn gcd(a: u64, b: u64) -> u64 {
    if b == 0 { a } else { gcd(b, a % b) }
}

fn gcd_vector(vec: &[u64]) -> u64 {
    vec.iter().copied().reduce(gcd).unwrap_or(0)
}

fn main() {
    let stdin = io::stdin();
    let mut it = stdin.lock().lines().map(|l| l.unwrap());
    let t: usize = it.next().unwrap().trim().parse().unwrap();
    let mut out = String::new();

    for _ in 0..t {
        let line = it.next().unwrap();
        let mut parts = line.split_whitespace().map(|c| c.parse::<u64>().unwrap());
        let n = parts.next().unwrap() as usize;

        let first = it
            .next()
            .unwrap()
            .split_whitespace()
            .map(|c| c.parse::<u64>().unwrap())
            .collect::<Vec<u64>>();

        let second = it
            .next()
            .unwrap()
            .split_whitespace()
            .map(|c| c.parse::<u64>().unwrap())
            .collect::<Vec<u64>>();

        let mut doable = true;
        for i in 0..n {
            let mut combined = Vec::new();
            combined.extend_from_slice(&first[..=i]);
            combined.extend_from_slice(&second[i..]);

            let g = gcd_vector(&combined);
            if g == 1 {
                doable = false;
                break;
            }
        }
        out += if doable { "Yes\n" } else { "No\n" };
    }
    print!("{}", out);
}

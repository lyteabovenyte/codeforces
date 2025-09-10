use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();

    for _ in 0..t {
        // Read n, j, k
        let header = lines.next().unwrap().unwrap();
        let mut parts = header.split_whitespace();
        let n: usize = parts.next().unwrap().parse().unwrap();
        let j: usize = parts.next().unwrap().parse().unwrap();
        let k: usize = parts.next().unwrap().parse().unwrap();

        // Read strengths
        let mut strengths: Vec<usize> = lines
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();

        let target = strengths[j - 1];

        strengths.sort_unstable();
        strengths.reverse();
        // Count number of players strictly stronger
        if k > 1 {
            println!("Yes");
        } else {
            if strengths[0] == target {
                println!("Yes");
            } else {
                println!("No");
            }
        }
    }
}

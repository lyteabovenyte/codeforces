use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut it = stdin.lock().lines().map(|l| l.unwrap());

    let t: usize = it.next().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let line = it.next().unwrap();
        let mut parts = line.split_whitespace().map(|s| s.parse::<u64>().unwrap());
        let n = parts.next().unwrap() as usize;
        let mut k = parts.next().unwrap();

        // Read casinos into a vector of tuples (l, r, real)
        let mut casinos = Vec::with_capacity(n);
        for _ in 0..n {
            let line = it.next().unwrap();
            let mut nums = line.split_whitespace().map(|x| x.parse::<u64>().unwrap());
            let l = nums.next().unwrap();
            let r = nums.next().unwrap();
            let real = nums.next().unwrap();
            casinos.push((l, r, real));
        }

        // Sort by l ascending
        casinos.sort_unstable_by_key(|c| c.0);

        // Greedy: scan sorted list and greedily take the best real whenever l <= k
        let mut ans = k;
        for &(l, r, real) in &casinos {
            if l > ans {
                // If we can't even reach the next casino, stop
                break;
            }
            if real > ans {
                // Casino is accessible, upgrade k to real
                ans = real;
            }
        }

        println!("{}", ans);
    }
}

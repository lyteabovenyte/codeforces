use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut it = stdin.lock().lines().map(|l| l.unwrap());

    let t: usize = it.next().unwrap().trim().parse().unwrap();

    for _ in 0..t {
        let line = it.next().unwrap();
        let mut parts = line.split_whitespace().map(|c| c.parse::<u64>().unwrap());
        let n = parts.next().unwrap() as usize;
        let k = parts.next().unwrap() as usize;
        let day = it.next().unwrap();
        let mut d = day
            .split_whitespace()
            .map(|x| x.parse::<u64>().unwrap())
            .collect::<Vec<u64>>();

        let mut res = 0;
        let mut i = 0;

        while i + k <= n {
            if d[i..i + k].iter().all(|&x| x == 0) {
                res += 1;
                i += k + 1;
            } else {
                i += 1;
            }
        }

        println!("{res}");
    }
}

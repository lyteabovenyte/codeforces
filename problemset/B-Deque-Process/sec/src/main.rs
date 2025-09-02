use std::io::{self, Read};

fn main() {
    // Read all input at once
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    let t: usize = iter.next().unwrap().parse().unwrap();
    for _ in 0..t {
        let n: usize = iter.next().unwrap().parse().unwrap();
        let mut p: Vec<i32> = (0..n)
            .map(|_| iter.next().unwrap().parse().unwrap())
            .collect();

        let mut ans = String::with_capacity(n);
        let (mut l, mut r) = (0, n - 1);

        for turn in 1..=n {
            let take_left = if turn % 2 == 1 {
                // odd turn → take minimum
                p[l] < p[r]
            } else {
                // even turn → take maximum
                p[l] > p[r]
            };

            if take_left {
                ans.push('L');
                l += 1;
            } else {
                ans.push('R');
                r = r.saturating_sub(1);
            }
        }

        println!("{}", ans);
    }
}
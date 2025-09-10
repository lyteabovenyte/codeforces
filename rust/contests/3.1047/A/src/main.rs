use std::io::{self, Read};

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let t: usize = it.next().unwrap().parse().unwrap();
    for _ in 0..t {
        let k: usize = it.next().unwrap().parse().unwrap();
        let mut x: u128 = it.next().unwrap().parse().unwrap();

        for step in 0..k {
            if step == k - 1 {
                // last reverse step: try to use (y-1)/3 if possible
                if x > 1 && (x - 1) % 3 == 0 {
                    let p = (x - 1) / 3;
                    if p >= 1 && p % 2 == 1 {
                        x = p;
                        continue;
                    }
                }
            }
            // otherwise, always double
            x *= 2;
        }

        println!("{}", x);
    }
}
use std::io::{self, Read};

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let t: usize = it.next().unwrap().parse().unwrap();
    let mut out = String::new();

    for _ in 0..t {
        let a: i128 = it.next().unwrap().parse().unwrap();
        let b: i128 = it.next().unwrap().parse().unwrap();

        let ans = if b % 2 == 1 {
            // b odd
            if a % 2 == 1 {
                Some(a * b + 1)
            } else {
                None
            }
        } else {
            // b even: count v2(b)
            let mut tb = b;
            let mut v2 = 0;
            while tb % 2 == 0 {
                tb /= 2;
                v2 += 1;
            }

            if a % 2 == 0 || v2 >= 2 {
                Some(a * (b / 2) + 2)
            } else {
                None
            }
        };

        match ans {
            Some(v) => {
                out.push_str(&v.to_string());
            }
            None => {
                out.push_str("-1");
            }
        }
        out.push('\n');
    }

    print!("{}", out);
}

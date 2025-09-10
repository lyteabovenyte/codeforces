use std::io::{self, Read};

fn main() {
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut it = s.split_whitespace();

    let t: usize = it.next().unwrap().parse().unwrap();
    let mut out = String::new();

    for _ in 0..t {
        let k: u32 = it.next().unwrap().parse().unwrap();
        let x: u128 = it.next().unwrap().parse().unwrap();

        let sum: u128 = 1u128 << (k + 1);
        let target: u128 = 1u128 << k;
        let mut a = x;
        let mut b = sum - x;

        let mut ops_rev: Vec<u8> = Vec::new();

        while a != target || b != target {
            if b >= a {
                ops_rev.push(1);
                let prev_a = a << 1;
                let prev_b = b - a;
                a = prev_a;
                b = prev_b;
            } else {
                ops_rev.push(2);
                let prev_b = b << 1;
                let prev_a = a - b;
                a = prev_a;
                b = prev_b;
            }
        }

        ops_rev.reverse();

        out.push_str(&format!("{}\n", ops_rev.len()));
        if ops_rev.is_empty() {
            out.push_str("\n");
        } else {
            for (i, op) in ops_rev.iter().enumerate() {
                if i > 0 { out.push(' '); }
                out.push_str(&op.to_string());
            }
            out.push_str("\n");
        }
    }

    print!("{}", out);
}

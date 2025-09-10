use std::io::{self, Read};

fn main() {
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut it = s.split_whitespace();
    let t: usize = it.next().unwrap().parse().unwrap();
    let mut out = String::new();

    for _ in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        let mut first = true;
        for _ in 0..n {
            let p: usize = it.next().unwrap().parse().unwrap();
            let q = n + 1 - p;
            if !first { out.push(' '); } else { first = false; }
            out.push_str(&q.to_string());
        }
        out.push('\n');
    }

    print!("{}", out);
}

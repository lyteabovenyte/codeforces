use std::io::{self, Read};

fn solve_case(n: usize, k: usize, s: &str) -> &'static str {
    let cnt = s.bytes().filter(|&b| b == b'1').count();
    if cnt <= k || n < 2 * k {
        "Alice"
    } else {
        "Bob"
    }
}

fn main() {
    let mut buf = String::new();
    io::stdin().read_to_string(&mut buf).unwrap();
    let mut it = buf.split_whitespace();
    let t: usize = it.next().unwrap().parse().unwrap();
    let mut out = String::new();
    for _ in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        let k: usize = it.next().unwrap().parse().unwrap();
        let s = it.next().unwrap();
        let winner = solve_case(n, k, s);
        out.push_str(winner);
        out.push('\n');
    }
    print!("{}", out);
}

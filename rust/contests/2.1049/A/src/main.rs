use std::io::{self, Read};

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let t: usize = it.next().unwrap().parse().unwrap();
    let mut out = Vec::with_capacity(t);

    for _ in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        let s = it.next().unwrap().as_bytes();

        let ones = s.iter().filter(|&&ch| ch == b'1').count();
        let left_len = n - ones; 
        let answer = s.iter().take(left_len).filter(|&&ch| ch == b'1').count();

        out.push(answer.to_string()); 
    }

    println!("{}", out.join("\n"));
}

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut it = stdin.lock().lines().map(|l| l.unwrap());

    let t: usize = it.next().unwrap().parse().unwrap();
    for _ in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        if n % 2 != 0 {
            println!("Alice");
        } else {
            if n % 4 == 0 {
                println!("Bob");
            } else {
                println!("Alice");
            }
        }
    }
}

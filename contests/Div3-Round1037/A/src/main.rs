use std::io::{self, BufRead};

fn digits(n: String) -> Vec<u32> {
    n.to_string()
        .chars()
        .map(|c| c.to_digit(10).unwrap())
        .collect()
}

fn main() {
    let stdin = io::stdin();
    let mut it = stdin.lock().lines().map(|l| l.unwrap());

    let t: usize = it.next().unwrap().trim().parse().unwrap();

    for _ in 0..t {
        let number = it.next().unwrap();
        let d = digits(number);
        let smallest = *d.iter().min().unwrap();
        println!("{smallest}");
    }
}

use std::{collections::VecDeque, io::{self, BufRead}};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let x: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: String = lines.next().unwrap().unwrap().trim().to_string();
        let y: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let b: String = lines.next().unwrap().unwrap().trim().to_string();

        let c: String = lines.next().unwrap().unwrap().trim().to_string();

        let result = solve(x, a, y, b, c);
        println!("{}", result);
    }
}

fn solve(x: i64, a: String, y: i64, b: String, c: String) -> String {

    let mut result = VecDeque::from(a.chars().collect::<Vec<char>>());

    // The problem is that you cannot index a String or &str with [i] directly in Rust.
    // Instead, you should convert the strings to Vec<char> or use .chars().nth(i).
    // Here's a corrected version:

    let b_chars: Vec<char> = b.chars().collect();
    let c_chars: Vec<char> = c.chars().collect();

    for i in 0..c_chars.len() {
        if c_chars[i] == 'D' {
            result.push_back(b_chars[i]);
        } else {
            result.push_front(b_chars[i]);
        }
    }

    result.iter().collect::<String>()
    
}
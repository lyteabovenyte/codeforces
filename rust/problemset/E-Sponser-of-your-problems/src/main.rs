/*
    Author: lyteabovenyte
*/

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i32 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<&str> = line.trim().split_whitespace().collect();
        let l = parts[0];
        let r = parts[1];
        
        if l == r {
            println!("{}", 2 * l.len());
            continue;
        }
        
        let mut ptr = 0;
        while ptr < l.len() && l.chars().nth(ptr) == r.chars().nth(ptr) {
            ptr += 1;
        }
        
        if ptr < l.len() && ptr < r.len() {
            let l_char = l.chars().nth(ptr).unwrap();
            let r_char = r.chars().nth(ptr).unwrap();
            
            if (l_char as u8) + 1 < (r_char as u8) {
                println!("{}", 2 * ptr);
            } else {
                let mut res = 2 * ptr + 1;
                for i in ptr + 1..l.len() {
                    if i < r.len() {
                        let l_digit = l.chars().nth(i).unwrap();
                        let r_digit = r.chars().nth(i).unwrap();
                        if l_digit == '9' && r_digit == '0' {
                            res += 1;
                        } else {
                            break;
                        }
                    }
                }
                println!("{}", res);
            }
        } else {
            println!("{}", 2 * ptr);
        }
    }
}
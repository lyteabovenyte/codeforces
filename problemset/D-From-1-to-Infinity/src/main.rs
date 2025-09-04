/*
    Author: lyteabovenyte
*/

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: i32 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    
    for _ in 0..t {
        let k: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        
        let mut cur: i64 = 9; // current group of numbers
        let mut len: i64 = 1; // length of the current group
        let mut k = k; // remaining digits to find
        
        while k - cur * len > 0 {
            k -= cur * len;
            cur *= 10;
            len += 1;
        }
        
        let s = (cur / 9 + (k - 1) / len).to_string();  // it's the exact number we need to calculate the sum of digits for up to it
        let mut ans: i64 = 0;
        
        // calculate the sum of the last digit and add it to the answer, so we don't care it anymore
        for i in 0..((k - 1) % len + 1) as usize {
            ans += (s.chars().nth(i).unwrap() as u8 - b'0') as i64;
        }
        
        let mut pr_s: i64 = 0; // prefix_sum - sum of digits processed so far
        let mut cur = cur;
        let mut len = len;
        
        for (i, ch) in s.chars().enumerate() {
            let curd = (ch as u8 - b'0') as i64;
            if curd != 0 {
                ans += curd * (len - 1) * cur / 2 + curd * (2 * pr_s + curd - 1) / 2 * cur / 9;
            }
            cur /= 10;
            len -= 1;
            pr_s += curd;
        }
        
        println!("{}", ans);
    }
}
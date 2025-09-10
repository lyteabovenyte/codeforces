/*
    Author: lyteabovenyte
*/

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let tc: i32 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    
    for _ in 0..tc {
        let n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: Vec<i32> = lines.next().unwrap().unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        
        let mut ans = a[0];
        let mut mn = 0.min(a[0]);
        let mut sum = a[0];
        
        for i in 1..n {
            if (a[i] % 2).abs() == (a[i - 1] % 2).abs() {
                mn = 0;
                sum = 0;
            }
            sum += a[i];
            ans = ans.max(sum - mn);
            mn = mn.min(sum);
        }
        
        println!("{ans}");
    }
}

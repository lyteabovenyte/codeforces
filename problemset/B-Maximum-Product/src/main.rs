/*
    Author: lyteabovenyte
*/

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: Vec<i64> = lines.next().unwrap().unwrap().split_whitespace().map(|s| s.parse().unwrap()).collect();
        let result = solve(a, n);
        println!("{result}");
    }
}

fn solve(mut a: Vec<i64>, _n: i64) -> i64 {
    if a.iter().all(|x| *x < 0) {
        // return the product of the 5 largest elements
        a.sort();
        return a.iter().rev().take(5).product();
    }

    // sort the array by the absolute value
    a.sort_by_key(|x| x.abs());
    a.reverse();

    let p = a.iter().take(5).product::<i64>();

    if p >= 0 {
        p
    } else {
        // We have a negative product, need to swap one element
        // If we have exactly 5 elements, we can't swap, so return the product
        if a.len() == 5 {
            return p;
        }
        
        // Try to find a better combination by swapping one element
        let mut best = p;
        
        // Try swapping each of the 5 selected elements with each remaining element
        for i in 0..5 {
            for j in 5..a.len() {
                let new_product = (p / a[i]) * a[j];
                best = best.max(new_product);
            }
        }
        best
    }
}
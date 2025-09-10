/*
    Author: lyteabovenyte
*/

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let _n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: Vec<i64> = lines.next().unwrap().unwrap().trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
        let result = solve(a.clone());
        println!("1) {result}");
        let result2 = solve2(a.clone());
        println!("2) {result2}");
        println!("----");
    }
}

fn solve(a: Vec<i64>) -> i64{
    // construct an array, in which the ith element is the miminum we have seen so far
    let mut min_array = Vec::with_capacity(a.len());
    min_array.push(a[0]);
    for i in 1..a.len() {
        min_array.push(std::cmp::min(min_array[i - 1], a[i]));
    }

    min_array[0] + min_array[1]
}

fn solve2(a: Vec<i64>) -> i64{
    std::cmp::min(2*a[0], a[0] + a[1])
}
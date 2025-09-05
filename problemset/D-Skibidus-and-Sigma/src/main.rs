/*
    Author: lyteabovenyte
*/

use std::{collections::HashMap, io::{self, BufRead}};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let mut parts = line.trim().split_whitespace();
        let n = parts.next().unwrap().parse::<i64>().unwrap();
        let m = parts.next().unwrap().parse::<i64>().unwrap();

        let mut a = Vec::new();
        for _ in 0..n {
            let line = lines.next().unwrap().unwrap();
            let vec = line
                .trim()
                .split_whitespace()
                .map(|x| x.parse::<i64>().unwrap())
                .collect::<Vec<i64>>();
            a.push(vec);
        }

        let result = solve(n, m, a);
        println!("{}", result);
    }
}

fn solve(n: i64, m: i64, a: Vec<Vec<i64>>) -> i64 {
    let mut sums = HashMap::new();

    for i in 0..a.len() {
        sums.insert(i, a[i].iter().sum::<i64>());
    }


    let mut sorted_sums: Vec<_> = sums.into_iter().collect();
    sorted_sums.sort_by_key(|(_, sum)| *sum);
    sorted_sums.reverse();



    let mut result = Vec::new();

    for i in 0..sorted_sums.len() {
        result.push(a[sorted_sums[i].0 as usize].clone());
    }

    let mut flattened_result = Vec::new();
    for i in 0..result.len() {
        flattened_result.extend(result[i].clone());
    }



    let mut total_sum = 0;
    let mut prefix_sum = 0;
    for i in 0..flattened_result.len() {
        prefix_sum += flattened_result[i];
        total_sum += prefix_sum;
    }

    total_sum
}

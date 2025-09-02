/*
link: https://codeforces.com/problemset/problem/2124/D
*/

use std::io::{self, Read};

/// Function that checks if we can make the array a palindrome
/// after applying the allowed operations.
fn solve(n: usize, k: usize, aa: Vec<i32>) -> &'static str {
    // If k = 1, we can always delete elements one by one until the array is empty,
    // which is trivially a palindrome.
    if k == 1 {
        return "YES";
    }

    // Step 1: Find the (k-1)-th smallest element, call it "cutoff" (x in the proof).
    // We clone and sort the array to find it.
    let mut bb = aa.clone();
    bb.sort();
    let cutoff = bb[k - 2]; // (k-1)-th smallest element (0-based index)

    // Step 2: Construct array `cc` by keeping only elements <= cutoff.
    // Elements greater than cutoff can always be removed (third group in the proof).
    let mut cc: Vec<i32> = aa.into_iter().filter(|&a| a <= cutoff).collect();

    // Step 3: We are allowed to remove some elements equal to cutoff (the second group),
    // but we must ensure that at least (k-1) smallest elements remain.
    // `spare` tells us how many cutoff elements we are allowed to remove.
    let mut spare = cc.len() as i32 - k as i32 + 1;

    // Step 4: Two-pointer approach to check if `cc` can be rearranged into a palindrome.
    // Initialize left (l) and right (r) pointers.
    let (mut l, mut r) = (0usize, cc.len().saturating_sub(1));
    let mut bad = false;

    while l < r {
        if cc[l] != cc[r] {
            // If mismatch:
            if spare == 0 {
                // No spare cutoff elements left → impossible
                bad = true;
                break;
            }
            // If left side is cutoff, delete it (use up one spare).
            if cc[l] == cutoff {
                l += 1;
                spare -= 1;
            }
            // If right side is cutoff, delete it (use up one spare).
            else if cc[r] == cutoff {
                r = r.saturating_sub(1);
                spare -= 1;
            }
            // If neither side is cutoff and they differ → impossible.
            else {
                bad = true;
                break;
            }
            continue;
        }
        // If cc[l] == cc[r], move both pointers inward.
        l += 1;
        r = r.saturating_sub(1);
    }

    // Final result: YES if palindrome possible, NO otherwise.
    if bad {
        "NO"
    } else {
        "YES"
    }
}

fn main() {
    // Read entire stdin
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    // Number of test cases
    let t: usize = iter.next().unwrap().parse().unwrap();

    for _ in 0..t {
        let n: usize = iter.next().unwrap().parse().unwrap();
        let k: usize = iter.next().unwrap().parse().unwrap();
        let mut aa = Vec::with_capacity(n);
        for _ in 0..n {
            aa.push(iter.next().unwrap().parse::<i32>().unwrap());
        }
        println!("{}", solve(n, k, aa));
    }
}
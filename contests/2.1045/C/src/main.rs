use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let _n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: Vec<i64> = lines.next().unwrap().unwrap().trim().split_whitespace().map(|s| s.parse().unwrap()).collect();

        let (_a, counter) = solve(a);
        println!("{}", counter);
    }
}

fn solve(mut a: Vec<i64>) -> (Vec<i64>, i64) {
    let mut counter = 0;
    if a.len() == 2 {
        // special case
        if a[0] <= a[1] {
            // ok
            return (a, 0);
        } else {
            // not ok, calculate how much to decrement from a[0]
            let decrement = a[0] - a[1];
            a[0] = a[1];
            counter += decrement;
        }
    } else {
        for i in 0..a.len() - 2 {
            check(i, &mut a, &mut counter);
        }
    }

    // don't forget the last two elements
    if a.len() % 2 == 0 {
        // odd, even
        let prev = a.len() - 2;
        let last = a.len() - 1;
        if a[prev] > a[last] {
            let decrement = a[prev] - a[last];
            a[prev] = a[last];
            counter += decrement;
        }
        return (a, counter);
    } else {
        // even, odd
        let prev = a.len() - 2;
        let last = a.len() - 1;
        if a[prev] < a[last] {
            let decrement = a[last] - a[prev];
            a[prev] = 0;
            counter += decrement;
        }
        return (a, counter);
    }
}

fn check(i: usize, a: &mut Vec<i64>, counter: &mut i64) {
    if i % 2 != 0 {
        // even case
        if a[i] + a[i + 2] >= a[i + 1] {
            // ok - nothing to do
        } else {
            // not ok, calculate how much to decrement from a[i + 1]
            let needed = a[i + 1] - (a[i] + a[i + 2]);
            if a[i + 1] > needed {
                a[i + 1] -= needed;
                *counter += needed;
            } else if a[i + 1] > 0 {
                // decrement as much as possible
                *counter += a[i + 1];
                a[i + 1] = 0;
            }
        }        
    } else {
        // odd case
        if a[i] + a[i + 2] <= a[i + 1] {
            // ok - nothing to do
        } else {
            // not ok, calculate how much to decrement
            let needed = (a[i] + a[i + 2]) - a[i + 1];
            
            if a[i + 2] >= needed {
                // decrement from a[i + 2]
                a[i + 2] -= needed;
                *counter += needed;
            } else {
                // decrement all of a[i + 2] first
                let decremented_from_i2 = a[i + 2];
                a[i + 2] = 0;
                *counter += decremented_from_i2;
                
                let remaining = needed - decremented_from_i2;
                if a[i] >= remaining {
                    // decrement remaining from a[i]
                    a[i] -= remaining;
                    *counter += remaining;
                } else if a[i] > 0 {
                    // decrement as much as possible from a[i]
                    *counter += a[i];
                    a[i] = 0;
                }
            }
        }
    }
}
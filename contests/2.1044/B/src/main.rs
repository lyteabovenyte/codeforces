use std::io::{self, Read};

fn main() {
    // Read all input
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut it = s.split_whitespace();

    let t: usize = it.next().unwrap().parse().unwrap();
    for _ in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        let mut a: Vec<i64> = (0..n).map(|_| it.next().unwrap().parse().unwrap()).collect();
        a.sort_unstable();

        // Sum every other element: if n even, start at index 1; if n odd, start at 0.
        let start = if n % 2 == 0 { 1 } else { 0 };
        let ans: i128 = a[start..].iter().step_by(2).map(|&x| x as i128).sum();

        println!("{}", ans);
    }
}

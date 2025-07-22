use std::io::{self, Read};

fn main() {
    let mut buf = String::new();
    io::stdin().read_to_string(&mut buf).unwrap();
    let mut it = buf.split_whitespace();
    let t: usize = it.next().unwrap().parse().unwrap();

    let mut out = String::new();
    for _ in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        let p: usize = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let mut a: Vec<i64> = (0..n)
            .map(|_| it.next().unwrap().parse().unwrap())
            .collect();

        let mut cur = a[p];
        let dist = a[p];
        a.sort_unstable();

        let reachable = a.into_iter().all(|h| {
            if h < cur {
                true
            } else if h - cur <= dist {
                cur = h;
                true
            } else {
                false
            }
        });

        out += if reachable { "YES\n" } else { "NO\n" };
    }

    print!("{}", out);
}

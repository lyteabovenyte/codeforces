use std::cmp::{max, min};
use std::io::{self, Read};

fn main() {
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut it = s.split_whitespace();

    let t: usize = it.next().unwrap().parse().unwrap();
    let mut out = String::new();

    for _ in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();

        let mut l: Vec<i64> = Vec::with_capacity(n);
        let mut r: Vec<i64> = Vec::with_capacity(n);
        let mut a: Vec<(i64, usize)> = Vec::with_capacity(n); // (r+l, idx)

        let mut sum_l: i64 = 0;
        let mut base_len: i64 = 0;

        for i in 0..n {
            let li: i64 = it.next().unwrap().parse().unwrap();
            let ri: i64 = it.next().unwrap().parse().unwrap();
            l.push(li);
            r.push(ri);
            a.push((li + ri, i));
            sum_l += li;
            base_len += ri - li;
        }

        let m = n / 2;

        a.sort_by(|x, y| y.0.cmp(&x.0));

        let mut sum_top_a: i64 = 0;
        for i in 0..m {
            sum_top_a += a[i].0;
        }

        let extra = if n % 2 == 0 {
            -sum_l + sum_top_a
        } else {
            let mut best_l_not_in_top = i64::MIN;
            for i in m..n {
                let idx = a[i].1;
                best_l_not_in_top = max(best_l_not_in_top, l[idx]);
            }

            let a_next = a[m].0;
            let mut min_r_in_top = i64::MAX;
            for i in 0..m {
                let idx = a[i].1;
                min_r_in_top = min(min_r_in_top, r[idx]);
            }
            let candidate2 = a_next - min_r_in_top;

            -sum_l + sum_top_a + max(best_l_not_in_top, candidate2)
        };

        let ans = base_len + extra;
        out.push_str(&format!("{}\n", ans));
    }

    print!("{}", out);
}

use std::io::{self, Read};

fn main() {
    // Read all input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let t: usize = it.next().unwrap().parse().unwrap();
    let mut out = String::new();

    const NEG_INF: i64 = -9_000_000_000_000_000_000i64;

    for _ in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        let mut a = vec![0i64; n + 1]; // 1 idx
        for i in 1..=n {
            a[i] = it.next().unwrap().parse::<i64>().unwrap();
        }

        let mut s0: i64 = 0;
        for i in 1..=n {
            if i % 2 == 1 {
                s0 += a[i];
            } else {
                s0 -= a[i];
            }
        }

        let same_parity_best: i64 = if n == 1 {
            0
        } else if n % 2 == 1 {
            (n as i64) - 1
        } else {
            (n as i64) - 2
        };

        let mut pref_d = vec![NEG_INF; n + 1];
        pref_d[0] = NEG_INF;
        for i in 1..=n {
            let mut val = pref_d[i - 1];
            if i % 2 == 1 {
                let d = -(i as i64) - 2 * a[i];
                if d > val {
                    val = d;
                }
            }
            pref_d[i] = val;
        }

        let mut suf_b = vec![NEG_INF; n + 2];
        suf_b[n + 1] = NEG_INF;
        for i in (1..=n).rev() {
            let mut val = suf_b[i + 1];
            if i % 2 == 1 {
                let b = (i as i64) - 2 * a[i];
                if b > val {
                    val = b;
                }
            }
            suf_b[i] = val;
        }


        let mut cross_best = NEG_INF;
        for p in 2..=n {
            if p % 2 == 0 {
                // even -> p
                let a_p = a[p];
                let a_val = 2 * a_p - p as i64;
                let c_val = 2 * a_p + p as i64;

                let cand1 = if suf_b[p] == NEG_INF { NEG_INF } else { a_val + suf_b[p] };
                let cand2 = if pref_d[p - 1] == NEG_INF { NEG_INF } else { c_val + pref_d[p - 1] };
                let best_here = cand1.max(cand2);

                if best_here > cross_best {
                    cross_best = best_here;
                }
            }
        }

        let improvement = same_parity_best.max(cross_best.max(0));
        let ans = s0 + improvement;

        out.push_str(&format!("{}\n", ans));
    }

    print!("{}", out);
}

/*
q - 2*a[q] pre
-q - 2*a[q] suf
*/
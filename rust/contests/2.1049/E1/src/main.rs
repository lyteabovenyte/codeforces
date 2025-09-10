use std::io::{self, Read};

fn remove_bit(mask: usize, r: usize) -> usize {
    let lower_mask = (1usize << (r - 1)) - 1;
    let lower = mask & lower_mask;
    let higher = mask >> r;
    lower | (higher << (r - 1))
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace().map(|s| s.parse::<i64>().unwrap());

    let t = it.next().unwrap() as usize;
    const MOD: i64 = 1_000_000_007;

    let mut outputs = Vec::with_capacity(t);

    for _case in 0..t {
        let n = it.next().unwrap() as usize;
        let m = it.next().unwrap() as i64;

        let k = it.next().unwrap() as usize;
        let mut good: Vec<usize> = Vec::with_capacity(k);
        for _ in 0..k {
            good.push(it.next().unwrap() as usize);
        }
        good.sort_unstable();

        if m == 1 {
            outputs.push(1i64);
            continue;
        }

        let mut a_prev = vec![false; 1 << 1];
        let mut b_prev = vec![false; 1 << 1];
        a_prev[0] = false;
        a_prev[1] = true;
        b_prev[0] = true;
        b_prev[1] = false;

        let mut idx_good = 0usize;

        for p in 2..=n {
            while idx_good < good.len() && good[idx_good] <= p {
                idx_good += 1;
            }
            let gp = &good[..idx_good];

            let size = 1usize << p;
            let mut a_cur = vec![false; size];
            let mut b_cur = vec![false; size];

            for mask in 0..size {
                let mut a_win = false;
                for &r in gp {
                    let m2 = remove_bit(mask, r);
                    if !b_prev[m2] {
                        a_win = true;
                        break;
                    }
                }
                a_cur[mask] = a_win;

                let mut b_win = false;
                for &r in gp {
                    let m2 = remove_bit(mask, r);
                    if !a_prev[m2] {
                        b_win = true;
                        break;
                    }
                }
                b_cur[mask] = b_win;
            }

            a_prev = a_cur;
            b_prev = b_cur;
        }

        let count_winning = a_prev.iter().filter(|&&v| v).count() as i64;
        let total_configs = 1i64 << n; // 2^n
        let ans = (total_configs + count_winning) % MOD;
        outputs.push(ans);
    }

    println!("{}", outputs.into_iter().map(|x| x.to_string()).collect::<Vec<_>>().join("\n"));
}

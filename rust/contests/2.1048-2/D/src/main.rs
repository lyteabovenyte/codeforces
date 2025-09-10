use std::io::{self, BufRead};
use std::cmp;

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    let t_line = lines.next().unwrap().unwrap();
    let t: usize = t_line.trim().parse().unwrap();

    for _ in 0..t {
        let nq_line = lines.next().unwrap().unwrap();
        let parts: Vec<usize> = nq_line.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        let n = parts[0];
        let q = parts[1];

        let a_line = lines.next().unwrap().unwrap();
        let a: Vec<i32> = a_line.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();

        let m = n.saturating_sub(2);
        let mut bad: Vec<i32> = vec![0i32; m];
        for i in 0..m {
            if a[i] > a[i + 1] && a[i + 1] > a[i + 2] {
                bad[i] = 1;
            }
        }

        let logg = if m == 0 {
            0
        } else {
            ((m as f64).log2() as usize) + 1
        };

        let mut st: Vec<Vec<i32>> = vec![vec![0i32; logg]; m];
        for i in 0..m {
            st[i][0] = bad[i];
        }
        for j in 1..logg {
            let powj = 1usize << j;
            let num_i = if powj > m { 0 } else { m - powj + 1 };
            let half = 1usize << (j - 1);
            for i in 0..num_i {
                st[i][j] = cmp::max(st[i][j - 1], st[i + half][j - 1]);
            }
        }

        for _ in 0..q {
            let query_line = lines.next().unwrap().unwrap();
            let parts: Vec<usize> = query_line.trim().split_whitespace()
                .map(|s| s.parse().unwrap()).collect();
            let l = parts[0];
            let r = parts[1];
            let len = r - l + 1;
            if len < 3 {
                println!("YES");
                continue;
            }
            let left = (l - 1) as usize;
            let right = (r - 3) as usize;
            let lenq = right - left + 1;
            if lenq <= 0 {
                println!("YES");
                continue;
            }
            let k = (lenq as f64).log2() as usize;
            let powk = 1usize << k;
            let mx = if right + 1 > powk {
                let idx = right.saturating_sub(powk - 1);
                if idx < m {
                    cmp::max(st[left][k], st[idx][k])
                } else {
                    st[left][k]
                }
            } else {
                st[left][k]
            };
            if mx > 0 {
                println!("NO");
            } else {
                println!("YES");
            }
        }
    }
}
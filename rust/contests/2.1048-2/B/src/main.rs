use std::io::{self, Read};

fn main() {
    // Read entire stdin
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut it = s.split_whitespace();

    let t: usize = it.next().unwrap().parse().unwrap();
    let mut out = String::new();

    for _case in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        let m: i128 = it.next().unwrap().parse::<i128>().unwrap();

        let mut a: Vec<i128> = Vec::with_capacity(n);
        for _ in 0..n {
            let ai = it.next().unwrap().parse::<i128>().unwrap();
            a.push(ai);
        }

        a.sort();

        let k_usize = {
            let m_usize = if m > (std::usize::MAX as i128) {
                std::usize::MAX
            } else {
                m as usize
            };
            std::cmp::min(n, m_usize)
        };

        
        let start_time: i128 = m - (k_usize as i128) + 1;

        
        let mut sum: i128 = 0;
        if k_usize > 0 {
            let start_idx = n - k_usize;
            for (idx, &val) in a[start_idx..].iter().enumerate() {
                let time = start_time + (idx as i128);
                sum += val * time;
            }
        }

        out.push_str(&format!("{}\n", sum));
    }

    print!("{}", out);
}
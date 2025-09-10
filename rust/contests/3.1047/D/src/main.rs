use std::io::{self, Read};

fn main() {
    // read all input at once
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut it = s.split_whitespace();

    let t: usize = it.next().unwrap().parse().unwrap();
    let mut out = String::new();

    for _case in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        let mut b = vec![0usize; n];
        for i in 0..n {
            b[i] = it.next().unwrap().parse::<usize>().unwrap();
        }

        // positions[val] = vector of indices i such that b[i] == val
        let mut positions: Vec<Vec<usize>> = vec![Vec::new(); n + 1];
        for (i, &val) in b.iter().enumerate() {
            positions[val].push(i);
        }

        let mut a = vec![0usize; n];
        let mut label: usize = n; // start from n downwards
        let mut ok = true;

        // iterate val from 1..=n
        for val in 1..=n {
            let pos_list = &positions[val];
            if pos_list.is_empty() {
                continue;
            }
            if pos_list.len() % val != 0 {
                ok = false;
                break;
            }
            let mut i = 0;
            while i < pos_list.len() {
                for k in 0..val {
                    a[pos_list[i + k]] = label;
                }
                label -= 1;
                i += val;
            }
        }

        if !ok {
            out.push_str("-1\n");
        } else {
            for i in 0..n {
                if i > 0 {
                    out.push(' ');
                }
                out.push_str(&a[i].to_string());
            }
            out.push('\n');
        }
    }

    print!("{}", out);
}

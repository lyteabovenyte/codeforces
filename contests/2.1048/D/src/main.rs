use std::io::{self, Read};
use std::collections::VecDeque;
// ! necessary? or 321/3412 pattern !!!! most important
fn perm_to_index(perm: &Vec<usize>, fact: &Vec<usize>) -> usize {
    let m = perm.len();
    let mut idx: usize = 0;
    for i in 0..m {
        let mut cnt = 0usize;
        for j in (i+1)..m {
            if perm[j] < perm[i] { cnt += 1; }
        }
        idx += cnt * fact[m - 1 - i];
    }
    idx
}

fn inversion_count(perm: &Vec<usize>) -> usize {
    let m = perm.len();
    let mut cnt = 0usize;
    for i in 0..m {
        for j in (i+1)..m {
            if perm[i] > perm[j] { cnt += 1; }
        }
    }
    cnt
}

fn bfs_min_ops(mut start: Vec<usize>) -> Option<usize> {
    let m = start.len();
    if m <= 1 { return Some(0); }

    
    let mut fact = vec![1usize; m + 1];
    for i in 1..=m { fact[i] = fact[i-1] * i; }

    
    let max_allowed_states = 4_000_000usize;
    let states = fact[m];
    if states > max_allowed_states {
        return None;
    }

    let start_idx = perm_to_index(&start, &fact);
    let target_idx = 0usize;

    if start_idx == target_idx {
        return Some(0);
    }

    let mut visited = vec![-1i32; states];
    let mut q: VecDeque<(Vec<usize>, usize)> = VecDeque::new();

    visited[start_idx] = 0;
    q.push_back((start.clone(), start_idx));

    while let Some((cur_perm, cur_idx)) = q.pop_front() {
        let cur_dist = visited[cur_idx] as usize;

        
        // ! adj swaps   
        for i in 0..(m-1) {
            let mut nxt = cur_perm.clone();
            nxt.swap(i, i+1);
            let nxt_idx = perm_to_index(&nxt, &fact);
            if visited[nxt_idx] == -1 {
                visited[nxt_idx] = (cur_dist + 1) as i32;
                if nxt_idx == target_idx { return Some((cur_dist + 1) as usize); }
                q.push_back((nxt, nxt_idx));
            }
        }
        
        for i in 0..(m-2) {
            let mut nxt = cur_perm.clone();
            nxt.swap(i, i+2);
            let nxt_idx = perm_to_index(&nxt, &fact);
            if visited[nxt_idx] == -1 {
                visited[nxt_idx] = (cur_dist + 1) as i32;
                if nxt_idx == target_idx { return Some((cur_dist + 1) as usize); }
                q.push_back((nxt, nxt_idx));
            }
        }
    }

    // !!!!!!!!
    None
}

fn main() {
    
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut it = s.split_whitespace();

    let t: usize = it.next().unwrap().parse().unwrap();
    let mut outputs: Vec<String> = Vec::new();

    for _case in 0..t {
        let n: usize = it.next().unwrap().parse().unwrap();
        let q: usize = it.next().unwrap().parse().unwrap();
        let mut a: Vec<i64> = Vec::with_capacity(n);
        for _ in 0..n {
            a.push(it.next().unwrap().parse::<i64>().unwrap());
        }

        for _ in 0..q {
            let l: usize = it.next().unwrap().parse().unwrap();
            let r: usize = it.next().unwrap().parse().unwrap();
            let sub_slice = &a[(l-1)..r];
            let m = sub_slice.len();

            
            let mut idxs: Vec<usize> = (0..m).collect();
            idxs.sort_by_key(|&i| (sub_slice[i], i));
            let mut rank = vec![0usize; m];
            for (rnk, &pos) in idxs.iter().enumerate() {
                rank[pos] = rnk;
            }
            let perm: Vec<usize> = (0..m).map(|i| rank[i]).collect();

            // ! g(b) pfffffffffffff
            let g = inversion_count(&perm);

            let f_opt = bfs_min_ops(perm.clone());

            let is_equal = match f_opt {
                Some(fv) => fv == g,
                None => {
                    let already_sorted = perm.windows(2).all(|w| w[0] <= w[1]);
                    already_sorted && g == 0
                }
            };

            outputs.push(if is_equal { "YES".to_string() } else { "NO".to_string() });
        }
    }

    println!("{}", outputs.join("\n"));
}

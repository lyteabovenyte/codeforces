use std::io::{self, BufRead};
use std::collections::VecDeque;

#[derive(Clone)]
struct BitSet {
    words: Vec<u64>,
}

const MAX_S: usize = 200010;
const WS: usize = (MAX_S + 63) / 64;

impl BitSet {
    fn new() -> Self {
        Self {
            words: vec![0u64; WS],
        }
    }

    fn set(&mut self, pos: usize) {
        if pos >= MAX_S {
            return;
        }
        let wi = pos / 64;
        let bi = (pos % 64) as u32;
        self.words[wi] |= 1u64 << bi;
    }

    fn get(&self, pos: usize) -> bool {
        if pos >= MAX_S {
            return false;
        }
        let wi = pos / 64;
        let bi = (pos % 64) as u32;
        (self.words[wi] & (1u64 << bi)) != 0
    }

    fn or_with(&mut self, other: &BitSet) {
        for i in 0..WS {
            self.words[i] |= other.words[i];
        }
    }

    fn shift_left(&self, k: usize) -> BitSet {
        if k == 0 {
            return self.clone();
        }
        if k >= MAX_S {
            return BitSet::new();
        }
        let word_shift = k / 64;
        let bit_shift = k % 64;
        let mut res = BitSet::new();
        for i in 0..WS {
            if i + word_shift >= WS {
                break;
            }
            let shifted = self.words[i] << bit_shift;
            res.words[i + word_shift] |= shifted & 0xFFFFFFFFFFFFFFFFu64;
            let carry = if bit_shift > 0 { (self.words[i] >> (64 - bit_shift)) } else { 0 };
            if carry != 0 && i + word_shift + 1 < WS {
                res.words[i + word_shift + 1] |= carry;
            }
        }
        res
    }

    fn has_in_range(&self, lo: i64, hi: i64) -> bool {
        if lo > hi {
            return false;
        }
        let l = lo as usize;
        let h = hi as usize;
        let start_w = l / 64;
        let end_w = h / 64;
        for w in start_w..=end_w {
            let word_full = self.words[w];
            if word_full == 0 {
                continue;
            }
            let word_start = w * 64;
            let rlo = std::cmp::max(l, word_start);
            let rhi = std::cmp::min(h, word_start + 63);
            if rlo > rhi {
                continue;
            }
            let local_lo = (rlo - word_start) as u32;
            let local_len = (rhi - rlo + 1) as u32;
            let mask = if local_len < 64 {
                (((1u64 << local_len) - 1) << local_lo)
            } else {
                !0u64 << local_lo
            };
            if (word_full & mask) != 0 {
                return true;
            }
        }
        false
    }
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    let t_line = lines.next().unwrap().unwrap();
    let t: usize = t_line.trim().parse().unwrap();
    for _ in 0..t {
        let nk_line = lines.next().unwrap().unwrap();
        let nk: Vec<i64> = nk_line
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        let n = nk[0] as usize;
        let k = nk[1];
        let p_line = lines.next().unwrap().unwrap();
        let ps: Vec<usize> = p_line
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        let mut adj: Vec<Vec<usize>> = vec![vec![]; n + 1];
        for i in 0..(n - 1) {
            let pp = ps[i];
            let child = i + 2;
            adj[pp].push(child);
        }
        // BFS to compute depth and level_sz
        let mut depth = vec![-1i32; n + 1];
        let mut level_sz = vec![0i64; n + 1];
        let mut q = VecDeque::new();
        depth[1] = 0;
        level_sz[0] += 1;
        q.push_back(1);
        while let Some(u) = q.pop_front() {
            for &v in &adj[u] {
                depth[v] = depth[u] + 1;
                level_sz[depth[v] as usize] += 1;
                q.push_back(v);
            }
        }
        // compute min_h
        let mut min_h = if n == 1 { 1usize } else { usize::MAX };
        for i in 1..=n {
            if adj[i].is_empty() {
                min_h = std::cmp::min(min_h, (depth[i] as usize) + 1);
            }
        }
        if n == 1 {
            min_h = 1;
        }
        // now bitset
        let mut bs = BitSet::new();
        bs.set(0);
        let mut cum_prefix = 0i64;
        let mut answer = 0usize;
        for lev in 0..min_h {
            let x = level_sz[lev];
            let temp = bs.shift_left(x as usize);
            bs.or_with(&temp);
            cum_prefix += x;
            let fr = n as i64 - cum_prefix;
            let lo = std::cmp::max(0i64, k - fr);
            let hi = std::cmp::min(k, cum_prefix);
            if bs.has_in_range(lo, hi) {
                answer = lev + 1;
            }
        }
        println!("{}", answer);
    }
}
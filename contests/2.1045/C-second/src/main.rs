use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: i32 = lines.next().unwrap().unwrap().parse().unwrap();
    
    for _ in 0..t {
        let n: usize = lines.next().unwrap().unwrap().parse().unwrap();
        let a: Vec<i32> = lines.next().unwrap().unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        
        let mut b = vec![0; n + 1];
        let mut ans: i64 = 0;
        
        for i in (0..n).step_by(2) {
            let mut mn = a[i];
            
            if i >= 2 {
                mn = mn.min(a[i - 1] - b[i - 2]);
            }
            
            if i + 1 < n {
                mn = mn.min(a[i + 1]);
            }
            
            b[i] = mn;
            ans += (a[i] - b[i]);
        }
        
        println!("{}", ans);
    }
}

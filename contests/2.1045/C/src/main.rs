fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<i64> = line.trim().split_whitespace().map(|s| s.parse().unwrap()).collect();

        
    }
}
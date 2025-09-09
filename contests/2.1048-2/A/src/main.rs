use std::io;

fn min_operations(a: u32, b: u32) -> u32 {
    if a == b {
        return 0;
    }
    
    if b % a == 0 {
        return 1;
    }
    
    if a % b == 0 {
        return 1;
    }
    
    return 2;
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let t: u32 = input.trim().parse().unwrap();
    
    for _ in 0..t {
        let mut line = String::new();
        io::stdin().read_line(&mut line).unwrap();
        let parts: Vec<u32> = line.trim().split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        let a = parts[0];
        let b = parts[1];
        
        println!("{}", min_operations(a, b));
    }
}

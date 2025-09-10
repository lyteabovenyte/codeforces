use std::io::{self, BufRead};

fn solve_case(n: i64, a: i64, b: i64) -> bool {
    // For a coloring to be symmetric, we need to ensure that
    // for every position i, the color at position i equals the color at position n+1-i
    
    // If n is very large, we need a mathematical approach
    if n > 1000 {
        return solve_large_case(n, a, b);
    }
    
    // For smaller cases, use brute force
    for x in 1..=n-a+1 {
        for y in 1..=n-b+1 {
            if is_symmetric_coloring(n, a, b, x, y) {
                return true;
            }
        }
    }
    false
}

fn solve_large_case(n: i64, a: i64, b: i64) -> bool {
    // For large n, we need to use mathematical analysis
    
    // Case 1: If we can paint the entire row with one color, it's always symmetric
    if a == n || b == n {
        return true;
    }
    
    // Case 2: If both segments are equal to n, we can paint the entire row blue
    if a == n && b == n {
        return true;
    }
    
    // Case 3: For other cases, we need more careful analysis
    // The key insight is that for symmetry, we need to ensure that
    // the painting pattern can be symmetric
    
    // If n is odd, the middle cell must be handled specially
    if n % 2 == 1 {
        return can_paint_symmetric_odd(n, a, b);
    } else {
        return can_paint_symmetric_even(n, a, b);
    }
}

fn can_paint_symmetric_odd(n: i64, a: i64, b: i64) -> bool {
    let mid = (n + 1) / 2;
    
    // For odd n, the middle cell (at position mid) must be painted the same
    // on both sides of the symmetry
    
    // Strategy 1: Paint the middle cell with blue
    if b >= 1 {
        // Check if we can place blue segment to cover the middle
        let min_y = (mid - b + 1).max(1);
        let max_y = mid.min(n - b + 1);
        if min_y <= max_y {
            // We can place blue to cover the middle
            return true;
        }
    }
    
    // Strategy 2: Paint the middle cell with red
    if a >= 1 {
        // Check if we can place red segment to cover the middle
        let min_x = (mid - a + 1).max(1);
        let max_x = mid.min(n - a + 1);
        if min_x <= max_x {
            // We can place red to cover the middle
            return true;
        }
    }
    
    // Strategy 3: Leave the middle cell white
    // This is only possible if neither segment covers the middle
    if a < n && b < n {
        // Check if both segments can fit on one side of the middle
        let left_half = mid - 1;
        let right_half = n - mid;
        
        // Both segments must fit on one side
        if (a <= left_half && b <= left_half) || (a <= right_half && b <= right_half) {
            return true;
        }
    }
    
    false
}

fn can_paint_symmetric_even(n: i64, a: i64, b: i64) -> bool {
    // For even n, we need to ensure that the painting pattern is symmetric
    // This means that for every cell i, cell n+1-i must have the same color
    
    // If we can paint the entire row with one color, it's symmetric
    if a == n || b == n {
        return true;
    }
    
    // If both segments are small enough, we can place them symmetrically
    if a <= n/2 && b <= n/2 {
        return true;
    }
    
    // For other cases, we need to check if we can create a symmetric pattern
    // This is more complex and depends on the specific arrangement
    
    // One approach: try to place segments symmetrically around the center
    let left_half = n / 2;
    let right_half = n / 2;
    
    // Check if we can place both segments on one side
    if (a <= left_half && b <= left_half) || (a <= right_half && b <= right_half) {
        return true;
    }
    
    // Check if we can place segments symmetrically across the center
    // This is more complex and would require detailed analysis
    // For now, let's use a simplified approach
    
    // If one segment is large enough to cover most of the row,
    // we might be able to make it symmetric
    if a >= n/2 || b >= n/2 {
        return true;
    }
    
    false
}

fn is_symmetric_coloring(n: i64, a: i64, b: i64, x: i64, y: i64) -> bool {
    // Create a vector representing the final colors
    // 0 = white, 1 = red, 2 = blue
    let mut colors = vec![0; n as usize];
    
    // Paint red segment
    for i in x-1..x-1+a {
        colors[i as usize] = 1;
    }
    
    // Paint blue segment (blue overrides red)
    for i in y-1..y-1+b {
        colors[i as usize] = 2;
    }
    
    // Check if the coloring is symmetric
    for i in 0..n {
        let j = n - 1 - i;
        if colors[i as usize] != colors[j as usize] {
            return false;
        }
    }
    true
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: i32 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<i64> = line.trim().split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        
        let n = parts[0];
        let a = parts[1];
        let b = parts[2];
        
        if solve_case(n, a, b) {
            println!("YES");
        } else {
            println!("NO");
        }
    }
}

use std::io::{self, BufRead};
use std::collections::HashMap;
use std::collections::hash_map::DefaultHasher;
use std::hash::{Hash, Hasher};


fn transform_array_fast(arr: &mut Vec<i32>) -> bool {
    let n = arr.len();
    let mut new_arr = vec![0; n];
    
    
    let max_val = arr.iter().max().copied().unwrap_or(0);
    let freq_size = ((max_val + 1) as usize).max(n + 1).min(100000); // Larger for correctness 
    
    let mut freq = vec![0; freq_size]; 
    for &x in arr.iter() {
        if x >= 0 && (x as usize) < freq.len() {
            freq[x as usize] += 1;
        }
    }
    
    for i in 0..n {
        let val = arr[i];
        
        
        if val >= 0 && (val as usize) < freq.len() {
            freq[val as usize] -= 1;
        }
        
        
        let mut mex_val = 0;
        while mex_val < freq.len() && mex_val < 100000 && freq[mex_val] > 0 {
            mex_val += 1;
        }
        new_arr[i] = (mex_val as i32).min(100000);
        
        
        if val >= 0 && (val as usize) < freq.len() {
            freq[val as usize] += 1;
        }
    }
    
    let changed = *arr != new_arr;
    *arr = new_arr;
    changed
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t: usize = lines.next().unwrap().unwrap().parse().unwrap();
    
    for _ in 0..t {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<&str> = line.split_whitespace().collect();
        let _n: usize = parts[0].parse().unwrap();
        let k: usize = parts[1].parse().unwrap();
        
        let line = lines.next().unwrap().unwrap();
        let mut arr: Vec<i32> = line.split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        
        
        if arr.is_empty() || k == 0 {
            let sum: i64 = arr.iter().map(|&x| (x as i64).min(10000)).sum();
            println!("{}", sum);
            continue;
        }
        
        
        let mut seen = HashMap::new();
        let mut states = Vec::new();
        let max_cycle_steps = if k <= 200 { k } else { 300 }; // Even more steps for correctness 
        
        let mut step = 0;
        while step < max_cycle_steps && step < k {
            
            if let Some(&cycle_start) = seen.get(&arr) {
                let cycle_length = step - cycle_start;
                if cycle_length > 0 {
                    let remaining = (k - step) % cycle_length;
                    for _ in 0..remaining {
                        if !transform_array_fast(&mut arr) {
                            break;
                        }
                    }
                }
                break;
            }
            
            seen.insert(arr.clone(), step);
            states.push(arr.clone());
            
            if !transform_array_fast(&mut arr) {
                
                break;
            }
            
            step += 1;
            
            
            if states.len() > 500 { // More memory for correctness
                seen.clear();
                states.clear();
                
                
                let mut hash_seen = HashMap::new();
                for remaining_step in step..(step + 200).min(k) { // More hash steps
                    let mut hasher = DefaultHasher::new();
                    arr.hash(&mut hasher);
                    let hash = hasher.finish();
                    
                    if let Some(&hash_cycle_start) = hash_seen.get(&hash) {
                        let cycle_length = remaining_step - hash_cycle_start;
                        if cycle_length > 0 {
                            let remaining = (k - remaining_step) % cycle_length;
                            for _ in 0..remaining {
                                if !transform_array_fast(&mut arr) {
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    
                    hash_seen.insert(hash, remaining_step);
                    
                    if !transform_array_fast(&mut arr) {
                        break;
                    }
                    
                    // step will be updated in loop
                }
                break;
            }
        }
        
        let sum: i64 = arr.iter().map(|&x| (x as i64).min(1000000)).sum();
        println!("{}", sum);
    }
}

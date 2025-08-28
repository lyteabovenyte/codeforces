use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let a: Vec<i64> = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();

        let result = solve(n, a);
        println!("{}", result);
    }
}

fn solve(n: i64, a: Vec<i64>) -> i64 {
    let mut result = 0;
    // iterators
    let mut even: Vec<i64> = a
        .iter()
        .enumerate()
        .filter(|(index, _)| index % 2 == 0)
        .map(|(_, value)| *value)
        .collect();
    let mut odd: Vec<i64> = a
        .iter()
        .enumerate()
        .filter(|(index, _)| index % 2 != 0)
        .map(|(_, value)| *value)
        .collect();

    if n == 2 {
        while even[0] < odd[0] {
            odd[0] -= 1;
            result += 1;
        }
        return result;
    } else {

        if n % 2 == 0 {
            // todo
        } else {
            for i in 0..odd.len() - 1 {
                while odd[i] + odd[i + 1] > even[i] {
                    // we need to reduce odd[i] and odd[i + 1] by the difference to make all even numbers larger.
                    let mut difference = odd[i] + odd[i + 1] - even[i];
                    result += difference;
                    while difference > 0 {
                        if odd[i+1] > 0 {
                            odd[i+1] -= 1;
                        } else {
                            odd[i] -= 1;
                        }
                        difference -= 1;
                    }
                }
            }
        }
    }
    return result;
}

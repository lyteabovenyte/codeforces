use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let t: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
    for _ in 0..t {
        let n = lines.next().unwrap().unwrap().trim().parse().unwrap();
        let result = solve(n, vec![2, 3, 7]);
        println!("{}", result);
    }
}

fn solve(final_score: usize, individual_play_score: Vec<usize>) -> usize {
    // dp[i][j] = number of ways to score j points using plays 0 to i
    let mut num_combinations: Vec<Vec<i64>> = vec![vec![0; final_score + 1]; individual_play_score.len()];
    
    // Base case: empty set can only make score 0
    for i in 0..individual_play_score.len() {
        num_combinations[i][0] = 1;
    }

    for i in 0..individual_play_score.len() {
        for j in 1..=final_score {
            let without_this_play = if i >= 1 {
                num_combinations[i - 1][j] // previously computed
            } else {
                0
            };

            let with_this_play = if j >= individual_play_score[i] {
                num_combinations[i][j - individual_play_score[i]] // we add one of this play to the previously computed combinations
            } else {
                0
            };

            num_combinations[i][j] = without_this_play + with_this_play;
        }
    }

    return num_combinations.last().unwrap()[final_score] as usize;
}

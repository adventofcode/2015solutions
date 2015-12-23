#![feature(io)]

use std::collections::HashSet;
use std::io::{self, Read};

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let input = stdin.chars()
        .map(|c| c.expect("reading from stdin should succeed"))
        .collect::<String>().parse::<u64>()
        .expect("the input should be properly formatted");

    let mut minimum = 0;
    for i in 1.. {
        let mut seen = HashSet::new();
        let mut sum = 0;
        for j in 1..((i as f64).sqrt() as u64 + 2) {
            if i % j == 0 {
                if i / j <= 50 && !seen.contains(&j) { sum += j * 11; seen.insert(j); }
                if j <= 50 && !seen.contains(&(i / j)) { sum += (i / j) * 11; seen.insert(i / j); }
            }
        }

        if sum >= input {
            minimum = i;
            break;
        }
    }

    println!("Minimum: {}", minimum);
}

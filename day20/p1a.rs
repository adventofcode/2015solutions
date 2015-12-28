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

    let expected_sum = input / 10;

    let mut minimum = 0;
    for i in 1.. {
        let mut seen = HashSet::new();
        let mut sum = 0;
        for j in 1..((i as f64).sqrt() as u64 + 2) {
            if i % j == 0 {
                if !seen.contains(&j) { sum += j; seen.insert(j); }
                if !seen.contains(&(i / j)) { sum += i / j; seen.insert(i / j); }
            }
        }

        if sum >= expected_sum {
            minimum = i;
            break;
        }
    }

    println!("Minimum: {}", minimum);
}

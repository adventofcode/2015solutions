#![feature(io)]

use std::io::{self, Read};

fn rle(inp: &[u8]) -> Vec<u8> {
    let mut prev_val = None;
    let mut count = 0;
    let mut res = Vec::new();
    for val in inp.iter() {
        let val = *val;

        match prev_val {
            Some(prev_val_i) => {
                if val == prev_val_i {
                    count += 1;
                } else {
                    res.push(count);
                    res.push(prev_val_i);
                    prev_val = Some(val);
                    count = 1;
                }
            },
            None => {
                prev_val = Some(val);
                count = 1;
            }
        }
    }

    res.push(count);
    res.push(prev_val.expect("there should be input"));

    res
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    // First run, convert the character sequence into an integer sequence
    let mut current_rle = stdin.chars()
        .map(|c| c.expect("reading from stdin should succeed") as u8 - '0' as u8)
        .collect::<Vec<u8>>();

    for _ in 0..50 {
        current_rle = rle(&current_rle);
    }

    println!("Length: {}", current_rle.len());
}

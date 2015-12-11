#![feature(io)]

use std::io::{self, Read};

fn has_run(pass: &Vec<u8>) -> bool {
    let mut run_length = 1;
    let mut prev_val = pass[0];

    for i in pass.iter().skip(1) {
        if *i == prev_val + 1 {
            run_length += 1;
        } else {
            run_length = 1;
        }

        if run_length >= 3 {
            return true;
        }

        prev_val = *i;
    }

    false
}
fn has_pairs(pass: &Vec<u8>) -> bool {
    let min_find = pass.windows(2)
        .enumerate()
        .filter(|&(_, p)| p[0] == p[1])
        .min_by_key(|&(i, _)| i)
        .map(|(i, _)| i)
        .unwrap_or(0);
    let max_find = pass.windows(2)
        .enumerate()
        .filter(|&(_, p)| p[0] == p[1])
        .max_by_key(|&(i, _)| i)
        .map(|(i, _)| i)
        .unwrap_or(0);

    (max_find - min_find) >= 2
}

fn passing(pass: &Vec<u8>) -> bool {
    has_run(pass) && has_pairs(pass)
}
fn increment_pass(pass: &mut Vec<u8>) {
    for i in 0..pass.len() {
        let i = pass.len() - i - 1;

        pass[i] = pass[i] + 1;

        if pass[i] == 'i' as u8 || pass[i] == 'o' as u8 || pass[i] == 'l' as u8 {
            pass[i] += 1;
        }

        if pass[i] >= 26 {
            pass[i] = 0;
        } else {
            break;
        }
    }
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut current_pass = stdin.chars()
        .map(|c| c.expect("reading from stdin should succeed") as u8 - 'a' as u8)
        .collect::<Vec<u8>>();

    while !passing(&current_pass) {
        increment_pass(&mut current_pass);
    }

    println!("Pass: {}", String::from_utf8(current_pass.into_iter()
                                           .map(|c| c + 'a' as u8)
                                           .collect::<Vec<u8>>()).unwrap());
}

#![feature(advanced_slice_patterns, io, slice_patterns)]

use std::io::{self, Read};

fn rle(mut inp: &[u8]) -> Vec<u8> {
    let mut res = Vec::new();

    while !inp.is_empty() {
        match inp {
            [ref x, ref y, ref z, rest..] if y == x && z == x => {
                res.push(3);
                res.push(*x);
                inp = rest;
            },
            [ref x, ref y, rest..] if y == x => {
                res.push(2);
                res.push(*x);
                inp = rest;
            },
            [ref x, rest..] => {
                res.push(1);
                res.push(*x);
                inp = rest;
            },
            [] => unreachable!(),
        }
    }

    res
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    // First run, convert the character sequence into an integer sequence
    let mut current_rle = stdin.chars()
        .map(|c| c.expect("reading from stdin should succeed") as u8 - '0' as u8)
        .collect::<Vec<u8>>();

    for _ in 0..40 {
        current_rle = rle(&current_rle);
    }

    println!("Length: {}", current_rle.len());
}

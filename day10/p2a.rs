#![feature(advanced_slice_patterns, io, slice_patterns)]

use std::io::{self, Read};
use std::mem::swap;

fn rle(mut inp: &[u8], storage: &mut Vec<u8>) {
    storage.clear();

    while !inp.is_empty() {
        match inp {
            [ref x, ref y, ref z, rest..] if y == x && z == x => {
                storage.push(3);
                storage.push(*x);
                inp = rest;
            },
            [ref x, ref y, rest..] if y == x => {
                storage.push(2);
                storage.push(*x);
                inp = rest;
            },
            [ref x, rest..] => {
                storage.push(1);
                storage.push(*x);
                inp = rest;
            },
            [] => unreachable!(),
        }
    }
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    // First run, convert the character sequence into an integer sequence
    let mut a = stdin.chars()
        .map(|c| c.expect("reading from stdin should succeed") as u8 - '0' as u8)
        .collect::<Vec<u8>>();
    let mut b = Vec::new();

    for _ in 0..50 {
        rle(&a, &mut b);
        swap(&mut a, &mut b);
    }

    println!("Length: {}", a.len());
}

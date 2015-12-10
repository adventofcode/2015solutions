//! This file is in the [cargo-script][1] format.
//!
//! [1]: https://github.com/DanielKeep/cargo-script
//!
//! ```cargo
//! [dependencies]
//! itertools = "^0.4"
//! ```

#![feature(io)]

#[macro_use]
extern crate itertools;

use itertools::Itertools;

use std::io::{self, Read};

fn rle(inp: Vec<u8>) -> Vec<u8> {
    let mut res = Vec::new();

    for (key, group) in inp.into_iter().group_by_lazy(|i| *i).into_iter() {
        res.push(group.fold(0, |l, _| l + 1));
        res.push(key);
    }

    res
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();
    let mut current_rle = stdin.chars()
        .map(|c| c.expect("reading from stdin should succeed") as u8 - '0' as u8)
        .collect::<Vec<u8>>();

    for _ in 0..50 {
        current_rle = rle(current_rle);
    }

    println!("Length: {}", current_rle.len());
}

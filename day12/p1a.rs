//! This file is in the [cargo-script][1] format.
//!
//! [1]: https://github.com/DanielKeep/cargo-script
//!
//! ```cargo
//! [dependencies]
//! itertools = "^0.4"
//! ```

#![feature(io, iter_arith)]

#[macro_use]
extern crate itertools;

use itertools::Itertools;

use std::io::{self, Read};

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let res = stdin.chars()
        .map(|c| c.expect("reading from stdin should succeed"))
        .group_by_lazy(|c| *c == '-' || c.is_digit(10)).into_iter()
        .filter_map(|(like_num, item)| if like_num { Some(item) } else { None })
        .filter_map(|s| s.collect::<String>().parse::<i64>().ok())
        .sum::<i64>();

    println!("Sum: {}", res);
}

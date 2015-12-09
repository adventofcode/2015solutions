//! This file is in the [cargo-script][1] format.
//!
//! [1]: https://github.com/DanielKeep/cargo-script
//!
//! ```cargo
//! [dependencies]
//! rust-crypto = "^0.2"
//! ```

extern crate crypto;

use crypto::digest::Digest;
use crypto::md5::Md5;

use std::io::{self, Read};

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();
    let input = stdin.bytes()
        .map(|b| b.expect("reading from stdin should succeed"))
        .collect::<Vec<u8>>();

    let mut md5 = Md5::new();

    for i in 0.. {
        let i_repr = i.to_string();

        md5.reset();
        md5.input(&input[..]);
        md5.input(i_repr.as_bytes());

        let hex = md5.result_str();
        if &hex[0..5] == "00000" {
            println!("Number: {}", i);
            return;
        }
    }
}

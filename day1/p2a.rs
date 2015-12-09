#![feature(io)]

use std::io::{self, Read};

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut current_floor = 0;

    for (pos, c) in stdin.chars().enumerate() {
        match c.expect("reading from stdin should succeed") {
            '(' => current_floor += 1,
            ')' => current_floor -= 1,
            _ => {},
        }

        if current_floor <= -1 {
            println!("Character: {}", pos + 1);
            return;
        }
    }

    panic!("never went below floor zero");
}

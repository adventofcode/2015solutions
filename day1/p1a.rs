#![feature(io)]

use std::io::{self, Read};

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut current_floor = 0;

    for c in stdin.chars() {
        match c.expect("reading from stdin should succeed") {
            '(' => current_floor += 1,
            ')' => current_floor -= 1,
            _ => {},
        }
    }

    println!("Floor: {}", current_floor);
}

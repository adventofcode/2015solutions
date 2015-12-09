#![feature(io)]

use std::collections::HashSet;
use std::io::{self, Read};

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut visited = HashSet::new();
    visited.insert((0, 0));
    let mut current_x = 0;
    let mut current_y = 0;

    for c in stdin.chars() {
        match c.expect("reading from stdin should succeed") {
            '^' => current_y += 1,
            'v' => current_y -= 1,
            '<' => current_x -= 1,
            '>' => current_x += 1,
            _ => {},
        }

        visited.insert((current_x, current_y));
    }

    println!("Visited: {}", visited.len());
}

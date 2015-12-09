#![feature(io)]

use std::collections::HashSet;
use std::io::{self, Read};

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut visited = HashSet::new();
    visited.insert((0, 0));
    let mut controlling_robot = false;
    let mut santa_x = 0;
    let mut santa_y = 0;
    let mut robot_x = 0;
    let mut robot_y = 0;

    for c in stdin.chars() {
        match c.expect("reading from stdin should succeed") {
            '^' => if controlling_robot { robot_y += 1 } else { santa_y += 1 },
            'v' => if controlling_robot { robot_y -= 1 } else { santa_y -= 1 },
            '<' => if controlling_robot { robot_x -= 1 } else { santa_x -= 1 },
            '>' => if controlling_robot { robot_x += 1 } else { santa_x += 1 },
            _ => {},
        }

        if controlling_robot {
            visited.insert((robot_x, robot_y));
        } else {
            visited.insert((santa_x, santa_y));
        }

        controlling_robot = !controlling_robot;
    }

    println!("Visited: {}", visited.len());
}

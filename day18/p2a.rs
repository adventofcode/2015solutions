#![feature(io, iter_arith)]

use std::io::{self, Read};
use std::mem::swap;

fn neighbors(cells: &[bool], x: i64, y: i64) -> usize {
    let mut count = 0;

    for &xoff in [-1, 0, 1].into_iter() {
        for &yoff in [-1, 0, 1].into_iter() {
            if xoff == 0 && yoff == 0 {
                continue;
            }
            if (xoff < 0 && x <= 0) || (xoff > 0 && x >= 99) {
                continue;
            }
            if (yoff < 0 && y <= 0) || (yoff > 0 && y >= 99) {
                continue;
            }

            if cells[(x + xoff) as usize * 100 + (y + yoff) as usize] {
                count += 1;
            }
        }
    }

    count
}
fn game_of_life(cells: &[bool], buffer: &mut [bool]) {
    for x in 0..100 {
        for y in 0..100 {
            let num_neighbors = neighbors(cells, x, y);

            let loc: usize = x as usize * 100 + y as usize;
            if cells[loc] {
                buffer[loc] = num_neighbors == 2 || num_neighbors == 3;
            } else {
                buffer[loc] = num_neighbors == 3;
            }
        }
    }

    buffer[0 * 100 + 0] = true;
    buffer[99 * 100 + 0] = true;
    buffer[0 * 100 + 99] = true;
    buffer[99 * 100 + 99] = true;
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut cells = Vec::with_capacity(100 * 100);
    for c in stdin.chars() {
        match c.expect("reading from stdin should succeed") {
            '#' => cells.push(true),
            '.' => cells.push(false),
            _ => {},
        }
    }
    let mut buffer = vec![false; 100 * 100];

    cells[0 * 100 + 0] = true;
    cells[99 * 100 + 0] = true;
    cells[0 * 100 + 99] = true;
    cells[99 * 100 + 99] = true;

    for _ in 0..100 {
        game_of_life(&cells, &mut buffer);
        swap(&mut cells, &mut buffer);
    }

    let count = cells.into_iter().map(|b| if b { 1 } else { 0 }).sum::<usize>();
    println!("Count: {}", count);
}

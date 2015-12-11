use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut chars_read = 0;
    let mut repr_size = 0;

    for line in stdin.lines() {
        let line = line.expect("reading from stdin should succeed");

        chars_read += line.len();
        repr_size += format!("{:?}", line).len();
    }

    println!("Memory: {}", repr_size - chars_read);
}

use std::io::{self, BufRead};

fn parse_line(line: &str) -> usize {
    let line = &line[1..line.len() - 1];

    let mut num_chars = 0;
    let mut is_escape_seq = false;
    let mut is_hex_escape = 0;
    for c in line.chars() {
        if is_escape_seq {
            is_escape_seq = false;

            if c == 'x' {
                is_hex_escape = 2;
            }
        } else if is_hex_escape > 0 {
            is_hex_escape -= 1;
        } else {
            is_escape_seq = c == '\\';
            num_chars += 1;
        }
    }

    num_chars
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut chars_read = 0;
    let mut memory_consumed = 0;

    for line in stdin.lines() {
        let line = line.expect("reading from stdin should succeed");

        chars_read += line.len();
        memory_consumed += parse_line(&line);
    }

    println!("Memory: {}", chars_read - memory_consumed);
}

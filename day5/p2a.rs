use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut nice_strings = 0;

    for line in stdin.lines() {
        let line = line.expect("reading from stdin should succeed");

        let has_repeat = line.as_bytes()
            .windows(2)
            .enumerate()
            .any(|(i, window)| {
                line.as_bytes()
                    .windows(2)
                    .enumerate()
                    .any(|(j, other_window)| {
                        (i as i64 - j as i64).abs() > 1
                            && window == other_window
                    })
        });
        let has_aba = line.chars()
            .zip(line.chars().skip(2))
            .any(|(a, b)| a == b);

        if has_repeat && has_aba {
            nice_strings += 1;
        }
    }

    println!("Nice: {}", nice_strings);
}

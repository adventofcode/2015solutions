use std::io::{self, BufRead};

fn is_vowel(c: char) -> bool {
    c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
}
fn contains_bad_sequence(s: &str) -> bool {
    s.contains("ab") || s.contains("cd") || s.contains("pq") || s.contains("xy")
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut nice_strings = 0;

    for line in stdin.lines() {
        let line = line.expect("reading from stdin should succeed");

        let has_three_vowels = line.chars()
            .fold(0, |res, c| if is_vowel(c) { res + 1 } else { res }) >= 3;
        let has_double_appearance = line.chars()
            .zip(line.chars().skip(1))
            .any(|(a, b)| a == b);
        let no_bad_sequences = !contains_bad_sequence(&line);

        if has_three_vowels && has_double_appearance && no_bad_sequences {
            nice_strings += 1;
        }
    }

    println!("Nice: {}", nice_strings);
}

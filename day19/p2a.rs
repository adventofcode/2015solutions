#![feature(negate_unsigned)]

use std::collections::HashMap;
use std::io::{self, BufRead};

fn parse_language(language: &[String]) -> HashMap<String, Vec<String>> {
    let mut res = HashMap::new();

    for item in language.iter() {
        let split = item.find(" => ").unwrap();
        res.entry(item[0..split].to_owned())
            .or_insert_with(Vec::new)
            .push(item[split + 4..].to_owned());
    }

    res
}

fn path_len(language: &HashMap<String, Vec<String>>, current: String, num_replacements: usize, lowest_replacements: &mut usize, seen: &mut HashMap<String, usize>) {
    if *seen.get(&current).unwrap_or(&-1) <= num_replacements || num_replacements > *lowest_replacements {
        return
    }
    seen.insert(current.clone(), num_replacements);
    println!("{} ({}): {}", *lowest_replacements, num_replacements, current);

    for (grapheme, replacements) in language.iter() {
        for replacement in replacements {
            for (idx, _) in current.match_indices(replacement) {
                let new_str = current[0..idx].to_owned() + grapheme + &current[idx + replacement.len()..];
                if new_str == "e" {
                    if num_replacements + 1 < *lowest_replacements {
                        println!("New record set: {}", num_replacements + 1);
                        *lowest_replacements = num_replacements + 1;
                    }
                } else {
                    path_len(language, new_str, num_replacements + 1, lowest_replacements, seen);
                }
            }
        }
    }
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let (language, input) = stdin.lines()
        .map(|line| line.expect("reading from stdin should succeed"))
        .partition::<Vec<String>, _>(|line| line.find("=>").is_some());
    let language = parse_language(&language);
    let ref input = input[1];

    let mut lowest_replacements = -1;
    let mut seen = HashMap::new();

    path_len(&language, input.clone(), 0, &mut lowest_replacements, &mut seen);
    println!("Shortest path: {}", lowest_replacements);
}

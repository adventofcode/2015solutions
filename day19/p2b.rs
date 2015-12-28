#![feature(negate_unsigned)]

use std::collections::{BinaryHeap, HashMap, HashSet};
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

fn path_len(language: &HashMap<String, Vec<String>>, input: &str) -> usize {
    let mut seen = HashSet::new();
    let mut q = BinaryHeap::new();
    q.push((-(input.len() as isize), 0, input.to_owned()));

    let mut lowest_replacements = -1;
    while !q.is_empty() {
        let (_, num_replacements, current) = q.pop().unwrap();

        if current == "e" {
            // We only add an item to the heap if num_replacements will be < lowest_replacements
            lowest_replacements = num_replacements as usize;
            println!("Reduced to electron in {} steps", lowest_replacements);
            continue;
        }

        seen.insert(current.clone());

        for (grapheme, replacements) in language.iter() {
            for replacement in replacements {
                for (idx, _) in current.match_indices(replacement) {
                    let new_str = current[0..idx].to_owned() + grapheme + &current[idx + replacement.len()..];

                    if !seen.contains(&new_str) && num_replacements + 1 < lowest_replacements {
                        q.push((-(new_str.len() as isize), num_replacements + 1, new_str));
                    }
                }
            }
        }
    }

    lowest_replacements
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let (language, input) = stdin.lines()
        .map(|line| line.expect("reading from stdin should succeed"))
        .partition::<Vec<String>, _>(|line| line.find("=>").is_some());
    let language = parse_language(&language);
    let ref input = input[1];

    let lowest_replacements = path_len(&language, input);
    println!("Shortest path: {}", lowest_replacements);
}

use std::collections::{HashMap, HashSet};
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

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let (language, input) = stdin.lines()
        .map(|line| line.expect("reading from stdin should succeed"))
        .partition::<Vec<String>, _>(|line| line.find("=>").is_some());
    let language = parse_language(&language);
    let ref input = input[1];

    let mut seen_items = HashSet::new();

    for (grapheme, replacements) in language.iter() {
        for (idx, _) in input.match_indices(grapheme) {
            for replacement in replacements {
                seen_items.insert(input[0..idx].to_owned() + replacement + &input[idx + grapheme.len()..]);
            }
        }
    }

    println!("# of ways: {}", seen_items.len());
}

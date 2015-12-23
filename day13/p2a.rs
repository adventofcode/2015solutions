#![feature(iter_arith)]

use std::collections::HashMap;
use std::i64;
use std::io::{self, BufRead};

fn parse_line(line: &str) -> (String, i64, String) {
    let split_sitting_next_to = line.find(" happiness units by sitting next to ")
        .expect("the input should be properly formatted");
    let name_gainsloses = &line[0..split_sitting_next_to];
    let target = line[split_sitting_next_to + 36..line.len() - 1].to_owned();

    if let Some(would_gain_pos) = name_gainsloses.find(" would gain ") {
        let source = name_gainsloses[0..would_gain_pos].to_owned();
        let n: i64 = name_gainsloses[would_gain_pos + 12..].parse().expect("the input should be properly formatted");
        (source, n, target)
    } else if let Some(would_lose_pos) = name_gainsloses.find(" would lose ") {
        let source = name_gainsloses[0..would_lose_pos].to_owned();
        let n: i64 = name_gainsloses[would_lose_pos + 12..].parse().expect("the input should be properly formatted");
        (source, -n, target)

    } else {
        panic!("the input should be properly formatted")
    }
}

fn permutations_worker<T, F: FnMut(&Vec<T>)>(arr: &mut Vec<T>, f: &mut F, min_idx: usize) {
    if min_idx >= arr.len() {
        f(arr);
    } else {
        for i in min_idx..arr.len() {
            arr.swap(min_idx, i);
            permutations_worker(arr, f, min_idx + 1);
            arr.swap(min_idx, i);
        }
    }
}
fn permutations<T, F: FnMut(&Vec<T>)>(mut arr: &mut Vec<T>, mut f: F) {
    permutations_worker(&mut arr, &mut f, 0);
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut happiness_delta = HashMap::new();
    for line in stdin.lines() {
        let (source, n, target) = parse_line(&line.expect("reading from stdin should succeed"));
        happiness_delta.entry(source)
            .or_insert_with(HashMap::new)
            .insert(target, n);
    }
    happiness_delta.insert("Myself".to_owned(), HashMap::new());

    let mut best_value = i64::MIN;
    permutations(&mut happiness_delta.keys().collect::<Vec<&String>>(), |ordering| {
        // ordering[0] sits next to ordering[1] ... so on, so forth
        // ordering[$] sits next to ordering[0]

        let total_value = ordering.iter().zip(ordering.iter().skip(1)).map(|(a, b)| {
            happiness_delta.get(*a).unwrap().get(*b).unwrap_or(&0) +
                happiness_delta.get(*b).unwrap().get(*a).unwrap_or(&0)
        }).sum::<i64>() +
            happiness_delta.get(ordering[ordering.len() - 1]).unwrap().get(ordering[0]).unwrap_or(&0) +
            happiness_delta.get(ordering[0]).unwrap().get(ordering[ordering.len() - 1]).unwrap_or(&0);

        if total_value > best_value {
            best_value = total_value;
        }
    });

    println!("Optimal happiness: {}", best_value);
}

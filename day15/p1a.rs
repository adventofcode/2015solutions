use std::cmp::max;
use std::collections::HashMap;
use std::io::{self, BufRead};

trait DropLast {
    fn drop_last(&self) -> &Self;
}

impl DropLast for str {
    fn drop_last(&self) -> &str {
        &self[0..self.len() - 1]
    }
}

fn parse_line(line: &str) -> (String, i64, i64, i64, i64, i64) {
    let mut segments = line.split_whitespace();

    let name = segments.nth(0).unwrap().drop_last().to_owned();
    let capacity = segments.nth(1)
        .expect("the input should be properly formatted")
        .drop_last().parse()
        .expect("the input should be properly formatted");
    let durability = segments.nth(1)
        .expect("the input should be properly formatted")
        .drop_last().parse()
        .expect("the input should be properly formatted");
    let flavor = segments.nth(1)
        .expect("the input should be properly formatted")
        .drop_last().parse()
        .expect("the input should be properly formatted");
    let texture = segments.nth(1)
        .expect("the input should be properly formatted")
        .drop_last().parse()
        .expect("the input should be properly formatted");
    let calories = segments.nth(1)
        .expect("the input should be properly formatted")
        .parse()
        .expect("the input should be properly formatted");

    (name, capacity, durability, flavor, texture, calories)
}

fn get_max_value(remaining: i64, num_seen: usize, stats: &Vec<(i64, i64, i64, i64, i64)>, cur_capacity: i64, cur_durability: i64, cur_flavor: i64, cur_texture: i64) -> i64 {
    if num_seen >= stats.len() {
        max(0, cur_capacity) * max(0, cur_durability) * max(0, cur_flavor) * max(0, cur_texture)
    } else {
        stats.iter().skip(num_seen).map(|&(capacity, durability, flavor, texture, _)| {
            let mut max_value = 0;
            for amt in 0..remaining + 1 {
                let value = get_max_value(remaining - amt, num_seen + 1, stats,
                                          cur_capacity + amt * capacity,
                                          cur_durability + amt * durability,
                                          cur_flavor + amt * flavor,
                                          cur_texture + amt * texture);

                if value > max_value {
                    max_value = value;
                }
            }

            max_value
        }).max().unwrap()
    }
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut ingredient_stats = HashMap::new();
    for line in stdin.lines() {
        let (name, capacity, durability, flavor, texture, calories) =
            parse_line(&line.expect("reading from stdin should succeed"));
        ingredient_stats.insert(name, (capacity, durability, flavor, texture, calories));
    }

    let max_value = get_max_value(100, 0, &ingredient_stats.values().map(|t| *t).collect(), 0, 0, 0, 0);
    println!("Max: {}", max_value);
}

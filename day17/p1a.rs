use std::io::{self, BufRead};

fn combinations(containers: &[i64], remaining: i64) -> i64 {
    let mut num_found = 0;

    for i in 0..containers.len() {
        if containers[i] == remaining {
            num_found += 1;
        } else if containers[i] < remaining {
            num_found += combinations(&containers[i + 1..], remaining - containers[i]);
        }
    }

    num_found
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut container_sizes = Vec::new();
    for line in stdin.lines() {
        container_sizes.push(line
                             .expect("reading from stdin should succeed")
                             .parse()
                             .expect("the input should be correctly formatted"));
    }

    let num_ways = combinations(&container_sizes, 150);
    println!("# of ways: {}", num_ways);
}

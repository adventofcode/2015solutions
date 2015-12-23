use std::io::{self, BufRead};

fn combinations(containers: &[i64], remaining: i64, num_used: usize, min_num_used: &mut usize, num_min_num_used: &mut usize) -> i64 {
    let mut num_found = 0;

    for i in 0..containers.len() {
        if containers[i] == remaining {
            num_found += 1;

            if num_used < *min_num_used {
                *min_num_used = num_used;
                *num_min_num_used = 1;
            } else if num_used == *min_num_used {
                *num_min_num_used += 1;
            }
        } else if containers[i] < remaining {
            num_found += combinations(&containers[i + 1..], remaining - containers[i], num_used + 1, min_num_used, num_min_num_used);
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

    let mut min_num_used = container_sizes.len();
    let mut num_min_num_used = 0;
    combinations(&container_sizes, 150, 0, &mut min_num_used, &mut num_min_num_used);
    println!("# of smallest solutions: {}", num_min_num_used);
}

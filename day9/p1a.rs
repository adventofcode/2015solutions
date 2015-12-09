use std::collections::HashMap;
use std::io::{self, BufRead};

fn parse_line(line: &str) -> (String, String, u64) {
    let to_pos = line.find(" to ")
        .expect("the input should be correctly formatted");

    let src = line[0..to_pos].to_owned();

    let equal_pos = line.find(" = ")
        .expect("the input should be correctly formatted");

    let dest = line[to_pos + 4..equal_pos].to_owned();
    let dist = line[equal_pos + 3..].parse()
        .expect("the input should be correctly formatted");

    (src, dest, dist)
}

fn permutations_worker<F: FnMut(&Vec<usize>)>(arr: &mut Vec<usize>, f: &mut F, min_idx: usize) {
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
fn permutations<F: FnMut(&Vec<usize>)>(max: usize, mut f: F) {
    let mut arr = vec![0; max];
    for (i, elem) in arr.iter_mut().enumerate() {
        *elem = i;
    }

    permutations_worker(&mut arr, &mut f, 0);
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut graph = HashMap::new();

    for line in stdin.lines() {
        let line = line.expect("reading from stdin should succeed");

        let (src, dest, dist) = parse_line(&line);

        let mut routes = graph.entry(src)
                .or_insert_with(|| Vec::new());
        routes.push((dest, dist));
    }

    let mut name_to_id = HashMap::new();
    let mut cur_id = 0;

    for (src, conns) in graph.iter() {
        name_to_id.entry(src).or_insert_with(|| {
            let id = cur_id;
            cur_id += 1;
            id
        });

        for conn in conns.iter() {
            let &(ref dest, _) = conn;

            name_to_id.entry(dest).or_insert_with(|| {
                let id = cur_id;
                cur_id += 1;
                id
            });
        }
    }

    let fixed_size = cur_id;
    let mut fixed_graph = vec![0; fixed_size * fixed_size];

    for (src, conns) in graph.iter() {
        let id = name_to_id[src];

        for conn in conns.iter() {
            let &(ref dest, ref dist) = conn;
            let oth_id = name_to_id[dest];

            fixed_graph[id * fixed_size + oth_id] = *dist;
            fixed_graph[oth_id * fixed_size + id] = *dist;
        }
    }

    let mut min_len_seen = None;
    permutations(cur_id, |ids| {
        let mut current_len = 0;

        let pairs = ids.iter().zip(ids.iter().skip(1));
        for (a, b) in pairs {
            current_len += fixed_graph[a * fixed_size + b];
        }

        match min_len_seen {
            None => min_len_seen = Some(current_len),
            Some(n) => if current_len < n {
                min_len_seen = Some(current_len)
            },
        }
    });

    println!("Minimum: {}", min_len_seen.expect("something should be visited"));
}

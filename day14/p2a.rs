use std::collections::HashMap;
use std::io::{self, BufRead};

enum ReindeerState {
    Active(i64, i64, i64),
    Passive(i64, i64, i64),
}

fn parse_line(line: &str) -> (String, i64, i64, i64) {
    let split_can_fly = line.find(" can fly ")
        .expect("the input should be properly formatted");
    let split_for = line.find(" km/s for ")
        .expect("the input should be properly formatted");
    let split_seconds = line.find(" seconds, but then must rest for ")
        .expect("the input should be properly formatted");
    let split_end = line.find(" seconds.")
        .expect("the input should be properly formatted");

    (line[0..split_can_fly].to_owned(),
     line[split_can_fly + 9..split_for].parse().expect("the input should be properly formatted"),
     line[split_for + 10..split_seconds].parse().expect("the input should be properly formatted"),
     line[split_seconds + 33..split_end].parse().expect("the input should be properly formatted"))
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut reindeer_stats = HashMap::new();
    for line in stdin.lines() {
        let (name, speed, active, rest) = parse_line(&line.expect("reading from stdin should succeed"));
        reindeer_stats.insert(name, (speed, active, rest));
    }

    let mut reindeer_state = HashMap::new();
    for name in reindeer_stats.keys() {
        reindeer_state.insert(name, ReindeerState::Active(0, 0, 0));
    }

    for _ in 0..2503 {
        for name in reindeer_stats.keys() {
            let state = reindeer_state.get_mut(name).unwrap();
            match state {
                &mut ReindeerState::Active(time, distance, points) => {
                    if time + 1 >= reindeer_stats.get(name).unwrap().1 {
                        *state = ReindeerState::Passive(0,
                                                        distance + reindeer_stats.get(name).unwrap().0,
                                                        points);
                    } else {
                        *state = ReindeerState::Active(time + 1,
                                                       distance + reindeer_stats.get(name).unwrap().0,
                                                       points);
                    }
                },
                &mut ReindeerState::Passive(time, distance, points) => {
                    if time + 1 >= reindeer_stats.get(name).unwrap().2 {
                        *state = ReindeerState::Active(0, distance, points);
                    } else {
                        *state = ReindeerState::Passive(time + 1, distance, points);
                    }
                }
            }
        }

        let mut max_dist = 0;
        for state in reindeer_state.values() {
            let dist = match state {
                &ReindeerState::Active(_, dist, _) => dist,
                &ReindeerState::Passive(_, dist, _) => dist,
            };

            if dist > max_dist {
                max_dist = dist;
            }
        }

        for name in reindeer_stats.keys() {
            match reindeer_state.get_mut(name).unwrap() {
                &mut ReindeerState::Active(_, dist, ref mut points) if dist == max_dist => {
                    *points += 1;
                },
                &mut ReindeerState::Passive(_, dist, ref mut points) if dist == max_dist => {
                    *points += 1;
                },
                _ => {},
            }
        }
    }

    let mut max_points = 0;
    for state in reindeer_state.values() {
        let points = match state {
            &ReindeerState::Active(_, _, points) => points,
            &ReindeerState::Passive(_, _, points) => points,
        };

        if points > max_points {
            max_points = points;
        }
    }

    println!("Max: {}", max_points);
}

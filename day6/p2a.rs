use std::cmp::max as max_f;
use std::io::{self, BufRead};

enum Command {
    TurnOn, Toggle, TurnOff
}

fn parse_tuple(tup: &str) -> (u32, u32) {
    let split = tup.find(',')
        .expect("the input should be properly formatted");

    (tup[0..split].parse().expect("the input should be properly formatted"),
     tup[split + 1..].parse().expect("the input should be properly formatted"))
}
fn parse_command(line: &str) -> (Command, (u32, u32), (u32, u32)) {
    let split_start = line.find(" through ")
        .expect("the input should be properly formatted");
    let split_end = split_start + 9;

    if &line[0..7] == "turn on" {
        (Command::TurnOn,
         parse_tuple(&line[8..split_start]),
         parse_tuple(&line[split_end..]))
    } else if &line[0..6] == "toggle" {
        (Command::Toggle,
         parse_tuple(&line[7..split_start]),
         parse_tuple(&line[split_end..]))
    } else if &line[0..8] == "turn off" {
        (Command::TurnOff,
         parse_tuple(&line[9..split_start]),
         parse_tuple(&line[split_end..]))
    } else {
        panic!("the input should be correctly formatted")
    }
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut lights = vec![0i64; 1_000_000];

    for line in stdin.lines() {
        let line = line.expect("reading from stdin should succeed");

        let (command, min, max) = parse_command(&line);

        for x in min.0 .. max.0 + 1 {
            for y in min.1 .. max.1 + 1 {
                let idx = x as usize * 1000 + y as usize;

                match command {
                    Command::TurnOn => lights[idx] += 1,
                    Command::Toggle => lights[idx] += 2,
                    Command::TurnOff => lights[idx] = max_f(0, lights[idx] - 1),
                }
            }
        }
    }

    let brightness = lights.into_iter()
        .fold(0, |amt, n| amt + n);
    println!("Brightness: {}", brightness);
}

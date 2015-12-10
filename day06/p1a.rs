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

    let mut lights = vec![false; 1_000_000];

    for line in stdin.lines() {
        let line = line.expect("reading from stdin should succeed");

        let (command, min, max) = parse_command(&line);

        for x in min.0 .. max.0 + 1 {
            for y in min.1 .. max.1 + 1 {
                let idx = x as usize * 1000 + y as usize;

                match command {
                    Command::TurnOn => lights[idx] = true,
                    Command::Toggle => lights[idx] = !lights[idx],
                    Command::TurnOff => lights[idx] = false,
                }
            }
        }
    }

    let num_lit = lights.into_iter()
        .fold(0, |amt, b| if b { amt + 1 } else { amt });
    println!("Lit: {}", num_lit);
}

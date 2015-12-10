use std::collections::HashMap;
use std::io::{self, BufRead};

#[derive(Clone, Debug)]
enum Value {
    Integer(u16),
    Name(String),
}

#[derive(Clone, Debug)]
enum Computation {
    Value(Value),
    Not(Value),
    And(Value, Value),
    Or(Value, Value),
    LeftShift(Value, u8),
    RightShift(Value, u8),
}

fn parse_value(s: &str) -> Value {
    if let Ok(n) = s.parse() {
        Value::Integer(n)
    } else {
        Value::Name(s.to_owned())
    }
}
fn parse_computation(line: &str) -> (String, Computation) {
    let split_arrow = line.find(" -> ")
        .expect("the input should be properly formatted");
    let comp = &line[0..split_arrow];
    let target = line[split_arrow + 4..].to_owned();

    (target, if comp.len() >= 4 && &comp[0..4] == "NOT " {
        Computation::Not(parse_value(&comp[4..]))
    } else {
        let and_pos = comp.find(" AND ");
        let or_pos = comp.find(" OR ");
        let lshift_pos = comp.find(" LSHIFT ");
        let rshift_pos = comp.find(" RSHIFT ");

        if let Some(pos) = and_pos {
            Computation::And(parse_value(&comp[0..pos]),
                             parse_value(&comp[pos + 5..]))
        } else if let Some(pos) = or_pos {
            Computation::Or(parse_value(&comp[0..pos]),
                            parse_value(&comp[pos + 4..]))
        } else if let Some(pos) = lshift_pos {
            Computation::LeftShift(parse_value(&comp[0..pos]),
                                   comp[pos + 8..].parse().expect("the value should be properly formatted"))
        } else if let Some(pos) = rshift_pos {
            Computation::RightShift(parse_value(&comp[0..pos]),
                                    comp[pos + 8..].parse().expect("the value should be properly formatted"))
        } else {
            Computation::Value(parse_value(comp))
        }
    })
}

fn evaluate(val: &mut HashMap<String, Computation>, key: &Value) -> u16 {
    // Replace val[key] by the result of its computation
    match *key {
        Value::Name(ref key) => {
            let res = match val[key].clone() {
                Computation::Value(Value::Integer(n)) => n,
                Computation::Value(name) => evaluate(val, &name),
                Computation::Not(name) => !evaluate(val, &name),
                Computation::And(a, b) => evaluate(val, &a) & evaluate(val, &b),
                Computation::Or(a, b) => evaluate(val, &a) | evaluate(val, &b),
                Computation::LeftShift(name, amt) => evaluate(val, &name) << amt,
                Computation::RightShift(name, amt) => evaluate(val, &name) >> amt,
            };

            val.insert(key.clone(), Computation::Value(Value::Integer(res)));

            res
        },
        Value::Integer(n) => n,
    }
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut values = HashMap::new();

    for line in stdin.lines() {
        let line = line.expect("reading from stdin should succeed");

        let (target, computation) = parse_computation(&line);
        values.insert(target, computation);
    }

    println!("{} -> a", evaluate(&mut values, &Value::Name("a".to_owned())));
}

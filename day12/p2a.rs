//! This file is in the [cargo-script][1] format.
//!
//! [1]: https://github.com/DanielKeep/cargo-script
//!
//! ```cargo
//! [dependencies]
//! serde = "^0.6"
//! serde_json = "^0.6"
//! ```

extern crate serde;
extern crate serde_json;

use serde_json::{Value, from_reader};

use std::io;

fn remove_red(val: &mut Value) {
    match val {
        &mut Value::Array(ref mut arr) => {
            for mut item in arr.iter_mut() {
                remove_red(&mut item);
            }
        },
        &mut Value::Object(ref mut obj) => {
            if obj.iter()
                .filter(|&(_, v)| v.as_string().map(|s| s == "red").unwrap_or(false))
                .next().is_some() {
                    obj.clear();
            } else {
                for (_, mut item) in obj.iter_mut() {
                    remove_red(&mut item);
                }
            }
        },
        _ => {},
    }
}

fn sum_of_value(val: &Value) -> i64 {
    match val {
        &Value::I64(i) => i,
        &Value::U64(u) => u as i64,
        &Value::F64(f) => f as i64,
        &Value::Array(ref arr) => {
            let mut sum = 0;

            for item in arr.iter() {
                sum += sum_of_value(item);
            }

            sum
        },
        &Value::Object(ref obj) => {
            let mut sum = 0;

            for (_, item) in obj.iter() {
                sum += sum_of_value(item);
            }

            sum
        },
        _ => 0,
    }
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut input: Value = from_reader(stdin)
        .expect("the input should be properly formatted");

    remove_red(&mut input);
    let sum = sum_of_value(&input);

    println!("Sum: {}", sum);
}

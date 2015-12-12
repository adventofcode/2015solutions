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

fn sum_value(val: &Value) -> i64 {
    match val {
        &Value::I64(i) => i,
        &Value::U64(u) => u as i64,
        &Value::F64(f) => f as i64,
        &Value::Array(ref arr) => {
            let mut sum = 0;

            for item in arr.iter() {
                sum += sum_value(&item);
            }

            sum
        },
        &Value::Object(ref obj) => {
            let mut sum = 0;

            for (_, item) in obj.iter() {
                if let Some(true) = item.as_string().map(|s| s == "red") {
                    return 0;
                }

                sum += sum_value(&item);
            }

            sum
        },
        _ => 0,
    }
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let input: Value = from_reader(stdin)
        .expect("the input should be properly formatted");

    let sum = sum_value(&input);

    println!("Sum: {}", sum);
}

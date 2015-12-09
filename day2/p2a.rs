use std::cmp::min;
use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut total_length = 0;

    for line in stdin.lines() {
        let line = line.expect("reading from stdin should succeed");

        let nums = line.split('x')
            .map(|s| s.parse()
                 .expect("the input should be correctly formatted"))
            .collect::<Vec<i32>>();

        if nums.len() != 3 {
            panic!("the input should be correctly formatted")
        }

        let l = nums[0];
        let w = nums[1];
        let h = nums[2];

        let top_perimeter = 2 * (l + w);
        let front_perimeter = 2 * (w + h);
        let side_perimeter = 2 * (h + l);

        let min_perimeter = min(top_perimeter, min(front_perimeter, side_perimeter));
        let bow_size = l * w * h;

        total_length += min_perimeter + bow_size;
    }

    println!("Total length: {}", total_length);
}

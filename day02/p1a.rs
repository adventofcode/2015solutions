use std::cmp::min;
use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut total_area = 0;

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

        let lw = l * w;
        let wh = w * h;
        let hl = h * l;

        let surface_area = 2 * (lw + wh + hl);
        let min_side = min(lw, min(wh, hl));

        total_area += surface_area + min_side;
    }

    println!("Total area: {}", total_area);
}

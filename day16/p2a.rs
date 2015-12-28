use std::collections::HashMap;
use std::io::{self, BufRead};

trait DropLast {
    fn drop_last(&self) -> &Self;
}
impl DropLast for str {
    fn drop_last(&self) -> &str {
        &self[0..self.len() - 1]
    }
}

fn parse_line(line: &str) -> HashMap<String, i64> {
    line.split_whitespace().skip(2).collect::<Vec<_>>().chunks(2).map(|item| {
        let id = item[0].drop_last();
        let val = item[1];

        (id.to_owned(), (if val.find(',').is_some() {
            val.drop_last().parse()
        } else {
            val.parse()
        }).expect("the input should be properly formatted"))
    }).collect()
}

fn main() {
    let stdin = io::stdin();
    let stdin = stdin.lock();

    let mut sue_stats = Vec::new();
    for line in stdin.lines() {
        sue_stats.push(parse_line(&line.expect("reading from stdin should succeed")));
    }

    let mut mfcsam_readout = HashMap::new();
    mfcsam_readout.insert("children".to_owned(), 3);
    mfcsam_readout.insert("cats".to_owned(), 7);
    mfcsam_readout.insert("samoyeds".to_owned(), 2);
    mfcsam_readout.insert("pomeranians".to_owned(), 3);
    mfcsam_readout.insert("akitas".to_owned(), 0);
    mfcsam_readout.insert("vizslas".to_owned(), 0);
    mfcsam_readout.insert("goldfish".to_owned(), 5);
    mfcsam_readout.insert("trees".to_owned(), 3);
    mfcsam_readout.insert("cars".to_owned(), 2);
    mfcsam_readout.insert("perfumes".to_owned(), 1);

    let mut matching_sues = sue_stats.into_iter()
        .enumerate()
        .filter(|&(_, ref stats)| {
            stats.into_iter().all(|(k, v)| {
                if k == "cats" || k == "trees" {
                    mfcsam_readout.get(k).unwrap() < v
                } else if k == "pomeranians" || k == "goldfish" {
                    mfcsam_readout.get(k).unwrap() > v
                } else {
                    mfcsam_readout.get(k).unwrap() == v
                }
            })
        }).map(|(i, stats)| {
            (i + 1, stats)
        });

    println!("Sue #: {}", matching_sues.next().unwrap().0);
}

mod myvec;
mod my_vec;
mod into_iter;
mod raw_vec;
mod drain;
mod rawvaliter;


use ferris_says::say;
use std::io::{stdout, BufWriter};
fn main() {
    let stdout = stdout();
    let message = String::from("Hello fellow Rustaceans!");
    let width = message.chars().count();

    let mut writer = BufWriter::new(stdout.lock());
    say(message.as_str(), width, &mut writer).unwrap();
    println!("Hello, world!");
}

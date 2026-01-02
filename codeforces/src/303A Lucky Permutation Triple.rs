use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: i32 = input.trim().parse().unwrap();
    if n % 2 == 0 {
        println!("-1");
    } else {
        for i in 0..n { print!("{} ", i); }
        println!();
        for i in 0..n { print!("{} ", (i + 1) % n); }
        println!();
        for i in 0..n { print!("{} ", (i + i + 1) % n); }
        println!();
    }
}
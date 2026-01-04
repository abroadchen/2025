use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<f64> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let a = parts[0];
    let b = parts[1];
    let c = parts[2];
    let d = parts[3];
    let res = a * d / (a * d + b * c - a * c);
    println!("{:.12}", res);
}
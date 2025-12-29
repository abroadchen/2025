use std::io;
fn main() {
    let ans = [0i64, 1, 0, 18, 0, 1800, 0, 670320, 0,
        734832000, 0, 890786230, 0, 695720788, 0, 150347555, 0];
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    println!("{}", ans[n]);
}
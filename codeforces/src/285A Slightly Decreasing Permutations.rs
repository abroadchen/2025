/**
首先输出k个数：n, n-1, n-2, ..., n-k+1
然后输出数字1
最后输出从2到(n-k)的所有数字
*/
use std::io;

fn main() {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let n = parts[0];//从parts向量中获取第一个元素
    let k = parts[1];
    for i in 0..k { println!("{} ", n - i); }
    println!("1");
    for i in 2..=n - k { println!(" {}", i); }
    println!();
}
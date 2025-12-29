use std::io;

fn main() {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let n = parts[0];
    let mut s = parts[1];
    let t = parts[2];
    input.clear();
    stdin.read_line(&mut input).unwrap();
    let a: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let mut arr = vec![0; (n + 1) as usize];//索引从1开始使用
    for i in 1..=n as usize { arr[i] = a[i - 1]; }
    for i in 0..=n {//从0到n循环，i表示步数
        if s == t { println!("{}", i); return; }
        s = arr[s as usize];
    }
    println!("-1");//循环结束后仍未找到目标
}
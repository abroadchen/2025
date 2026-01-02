/**
for (i = 0; i < n; ++i) {
    cin >> a;  // 每次循环读取一个新值
    // 处理 a
} <=>  for &a in numbers.iter().take(n as usize)

// 等价于：
for i in 0..n as usize {
    if i >= numbers.len() {
        break;
    }
    let a = numbers[i];  // 获取值
    // 处理 a
}
*/
use std::io;

fn main() {
    // 读取 p 和 q
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i64> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let mut p = parts[0];
    let mut q = parts[1];

    // 读取 n
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let n: i64 = input.trim().parse().unwrap();

    // 读取 n 个数字
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let numbers: Vec<i64> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();

    let mut i = 0;
    for &a in numbers.iter().take(n as usize) {
        if q == 0 { break; }
        if a > p / q { break; }
        p -= a * q;
        let t = p; p = q; q = t;
        i += 1;
    }

    if i < n || q != 0 { println!("NO"); } else { println!("YES"); }
}
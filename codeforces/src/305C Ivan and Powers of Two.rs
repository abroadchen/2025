use std::collections::HashSet;
use std::io;
//通过移除-递增-插入的操作来确保每个处理后的值都是唯一的
fn uni(x: &mut i32, s: &mut HashSet<i32>) {
    while s.contains(x) {
        s.remove(x);
        *x += 1;
    }
    s.insert(*x);
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut s = HashSet::new();
    let mut mx = -1_000_000_000;
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    for &i in parts.iter().take(n) {
        let mut x: i32 = i;
        uni(&mut x, &mut s);
        mx = mx.max(x);
    }
    let v = mx + 1;
    println!("{}", v - s.len() as i32);//缺失的数字个数
}
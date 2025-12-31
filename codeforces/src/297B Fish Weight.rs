use std::io::{self, BufRead};

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace().map(|x| x.parse().unwrap()).collect();
    let n = parts[0] as usize;
    let m = parts[1] as usize;
    let k = parts[2];
    let mut a = vec![0; n + 1];
    let mut b = vec![0; m + 1];
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let av: Vec<i32> = input.trim().split_whitespace().map(|x| x.parse().unwrap()).collect();
    for i in 1..=n { a[i] = av[i - 1]; }
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let bv: Vec<i32> = input.trim().split_whitespace().map(|x| x.parse().unwrap()).collect();
    for i in 1..=m { b[i] = bv[i - 1]; }
    a[1..].sort(); b[1..].sort();//只对索引1到n的部分排序
    let mut ni = n;//从后往前遍历数组
    let mut mi = m;
    while ni > 0 && mi > 0 {//两个索引都大于0时继续循环
        if b[mi] >= a[ni] { mi -= 1; ni -= 1; } else { break }//向前移动
    }
    if ni > 0 { println!("YES"); } else { println!("NO"); }
}
/**
map(): 这是一个迭代器方法，用于将一个函数应用到序列中的每个元素
|i|: 这是 Rust 中的闭包参数声明，i 是传入的参数名
letter[i as usize]: 闭包的函数体，执行数组索引访问操作

*/
use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    let s = lines.next().unwrap().unwrap();
    let sv: Vec<char> = s.chars().collect();//转换为字符向量便于索引
    let mut cnt = [0; 128];//字母出现情况，大小为128（ASCII码范围）
    let mut w = 0;//'?'的数量
    for ch in sv.iter() {
        if *ch >= 'A' && *ch < 'K' { cnt[*ch as usize] = 1; }
        else if *ch == '?' { w += 1; }
    }
    let mut res = 1;
    let tot = (b'A'..b'K').map(|i| cnt[i as usize]).sum::<i32>();
    if tot > 0 { if sv[0] >= 'A' && sv[0] < 'K' { res *= 9; } else { res *= 10; } }
    for i in 1..tot { res *= 10 - i; }
    if w > 0 && sv[0] == '?' { res *= 9; w -= 1; }
    let p = "0".repeat(w as usize);
    println!("{}{}", res, p);
}
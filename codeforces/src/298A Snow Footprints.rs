use std::io::{self, BufRead};

fn get_r(input: &str) -> (i32, i32) {
    let mut r1 = -1;//表示未找到 R
    let mut r2 = -1;
    for (i, c) in input.chars().enumerate() {// 为每个字符添加索引
        if c == 'R' { r1 = i as i32; break }//找到第一个 R
    }
    if r1 != -1 {//找到第一个（从右往左第一个，即从左往右最后一个)
        for (i, c) in input.chars().rev().enumerate() {
            if c == 'R' { r2 = (input.len() - 1 - i) as i32; break }//原始字符串中从右数第 i 个字符的索引
        }
    }
    (r1, r2)
}

fn get_l(input: &str) -> (i32, i32) {
    let mut l1 = -1;
    let mut l2 = -1;
    for (i, c) in input.chars().rev().enumerate() {
        if c == 'L' { l2 = (input.len() - 1 - i) as i32; break }
    }
    if l2 != -1 {
        for (i, c) in input.chars().enumerate() {
            if c == 'L' { l1 = i as i32; break }
        }
    }
    (l1, l2)
}

fn out(r1: i32, r2: i32, l1: i32, l2: i32) {
    if r1 == -1 { println!("{} {}", l2 + 1, l1); }//只有 L 存在
    else if l2 == -1 { println!("{} {}", r1 + 1, r2 + 2); } else {//只有 R 存在
        println!("{} {}", r1 + 1, r2 + 1);
    }
}



fn main() {
    loop {//无限循环
        let mut input = String::new();
        if io::stdin().read_line(&mut input).is_err() { break; }
        let len: usize = match input.trim().parse() {//尝试将字符串转换为数字
            Ok(n) => n,
            Err(_) => break,
        };
        let mut input = String::new();//另一个可变字符串变量
        if io::stdin().read_line(&mut input).is_err() { break; }
        let s = input.trim_end();//处理后的字符串引用
        let (r1, r2) = get_r(s);// R 的第一个和最后一个位置
        let (l1, l2) = get_l(s);// L 的第一个和最后一个位置
        out(r1, r2, l1, l2);
    }
}
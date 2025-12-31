use std::io::{self, BufRead};

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let a = input.trim().to_string();//转换为新字符串
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let b = input.trim().to_string();
    let mut x = 0;//统计字符串a中'1'的个数
    for c in a.chars() { if c == '1' { x += 1; } }
    let mut y = 0;
    for c in b.chars() { if c == '1' { y += 1; } }
    if x + x % 2 >= y { println!("YES"); } else {println!("NO"); }
}
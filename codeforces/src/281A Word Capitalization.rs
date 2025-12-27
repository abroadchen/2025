/**
s.chars()将字符串分割为字符迭代器

将第一个字符转换为大写
to_uppercase()返回一个大写字符的迭代器
.next()获取迭代器的第一个元素
.unwrap_or(first_char)如果迭代器为空则返回原字符
将结果赋值给向量的第一个位置

将字符向量转换回字符串
into_iter()创建获取所有权的迭代器
.collect()收集为String类型
*/
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let s = input.trim();//去除首尾空白的新字符串切片
    let mut chars: Vec<char> = s.chars().collect();
    if !chars.is_empty() {
        let first_char = chars[0];
        if first_char.is_lowercase() {
            chars[0] = first_char.to_uppercase().next().unwrap_or(first_char);
        }
    }
    let res: String = chars.into_iter().collect();
    println!("{}", res);
}
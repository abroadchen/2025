//
// Created by Psy.C on 2025/12/26.
//
/*
创建一个可变的字符串变量 input，用于存储用户输入
String::new() 创建一个新的空字符串
io::stdin() 获取标准输入句柄
.read_line(&mut input) 读取一行输入并存储到 input 变量中
&mut input 是对 input 的可变引用
.unwrap() 解包结果，如果读取失败则程序崩溃

input.trim() 去除字符串首尾的空白字符
.split(' ') 按空格分割字符串，返回一个迭代器
.collect() 将迭代器收集为 Vec<&str>（字符串切片向量）
parts 包含分割后的字符串片段
parts[0] 获取第一个字符串元素
.parse::<i32>() 将字符串解析为 32 位有符号整数
::<i32> 是类型参数，指定解析的目标类型
.unwrap() 解包解析结果
x 和 y 分别存储解析后的整数值
*/
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<&str> = input.trim().split(' ').collect();
    let x = parts[0].parse::<i32>().unwrap();
    let y = parts[1].parse::<i32>().unwrap();
    if y <= 0 && x >= 1 + y && x <= 1 - y { println!("{}", (-y) * 4); }
    else if x > 0 && y >= 2 - x && y <= x { println!("{}", x * 4 - 3); }
    else if y > 0 && x >= -y && x <= y - 1 { println!("{}", y * 4 - 2); }
    else if x < 0 && y >= x && y <= -1 - x { println!("{}", (-x) * 4 - 1); }
    else { println!("0"); }
}
//
// Created by Psy.C on 2025/12/24.
//
/*
创建一个可变的字符串变量input，用于存储从控制台读取的输入
mut关键字表示这个变量是可变的，可以被修改
从标准输入读取一行文本
&mut input：传递input的可变引用，让read_line函数可以修改input的内容
unwrap()：处理可能的错误，如果读取失败则程序崩溃
定义numbers变量，类型为i64整数向量
.trim()：去除字符串首尾的空白字符（包括换行符）
.split_whitespace()：按空白字符（空格、制表符、换行符等）分割字符串
.map(|x| x.parse().expect("Invalid number"))：对每个分割后的字符串应用转换
|x|：定义一个闭包，参数为x
x.parse()：将字符串x解析为数字
.expect("Invalid number")：如果解析失败则显示错误信息
.collect()：将迭代器的结果收集到Vec中
从numbers向量中提取第一个元素赋值给变量a
从numbers向量中提取第二个元素赋值给变量b
计算a和b的按位异或结果，存储在变量c中
^是Rust中的异或运算符
创建一个可变的i64类型变量ans，初始值为1
1i64明确指定这是64位整数类型
当ans小于等于c时继续循环
ans <<= 1：将ans左移1位（等价于ans *= 2）
这个循环找到第一个大于c的2的幂
输出ans-1的值
{}是格式化输出的占位符
println!宏输出结果并自动换行
*/
use std::io;

fn main() {
  let mut input = String::new();
  io::stdin().read_line(&mut input).unwrap();

  let nums: Vec<i64> = input
    .split_whitespace()
    .map(|s| s.parse().unwrap())
    .collect();

  let (a, b) = (nums[0], nums[1]);
  let c = a ^ b;
  let mut ans = 1i64;

  while ans <= c { ans <<= 1; }
  println!("{}", ans - 1);
}
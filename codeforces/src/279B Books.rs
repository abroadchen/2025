/*
创建一个可变的字符串变量 input，用于存储用户输入
从标准输入读取一行到 input 变量中
is_err() 检查是否读取失败（如遇到 EOF）
如果读取失败，跳出循环
input.trim() 去除字符串首尾的空白字符
.split_whitespace() 按空白字符（空格、制表符、换行符等）分割字符串
.collect() 将分割结果收集为字符串切片向量
检查分割后的部分数量是否为2（n和time）
如果不是2个部分，跳出循环

parts[0].parse() 将第一个部分解析为 usize 类型（数组长度）
parts[1].parse() 将第二个部分解析为 i64 类型（时间限制）
expect 在解析失败时显示错误信息

map(|x| ...) 对每个部分应用闭包，解析为 i64
.collect() 收集为 Vec<i64> 类型

检查读取的数组长度是否与 n 匹配
不匹配则跳出循环
j: 滑动窗口的左边界索引，初始化为-1
sum: 当前窗口的和，初始化为0
ans: 记录最大窗口大小，初始化为0

如果当前和加上新元素不超过时间限制
将新元素加入当前窗口
否则，将新元素加入窗口
当窗口和超过时间限制时，移动左边界
j as usize 将 i64 转换为 usize 用于数组索引
更新最大窗口大小
i - j as usize 计算当前窗口的大小

*/
use std::io;

fn main() {
    loop {
        let mut input = String::new();
        if io::stdin().read_line(&mut input).is_err() { break }
        let parts: Vec<&str> = input.split_whitespace().collect();
        if parts.len() != 2 { break }
        let n: usize = parts[0].parse().expect("Invalid n");
        let time: i64 = parts[1].parse().expect("Invalid time");

        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let book: Vec<i64> = input.trim().split_whitespace()
            .map(|x| x.parse().expect("Invalid number")).collect();
        if book.len() != n { break }
        let mut j: i64 = -1;
        let mut sum: i64 = 0;
        let mut ans: usize = 0;
        for i in 0..n {
            if sum + book[i] <= time { sum += book[i]; }
            else {
                sum += book[i];
                while sum > time {
                    j += 1;
                    sum -= book[j as usize];
                }
            }
            ans = ans.max(i - j as usize)
        }
        println!("{}", ans);
    }
}
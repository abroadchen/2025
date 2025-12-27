/**
导入标准输入输出库和BufRead trait
self表示导入io模块本身
BufRead提供了按行读取的功能

获取输入的锁并创建一个行迭代器
lock()获取stdin的互斥锁以提高效率
lines()创建一个按行读取的迭代器

循环读取输入行
lines.next()获取迭代器的下一个元素
Some(Ok(line1))模式匹配，确保读取成功且不是结尾
读取第二行输入
与第一行类似，确保读取成功
去除行首行尾的空白字符（包括换行符）
将输入行转换为字符串切片
获取两个字符串的长度
检查两个字符串长度是否相等
初始化两个变量用于标记是否在字符串中找到'1'

遍历str1的每个字符
如果找到'1'，设置sum1为1并跳出循环
chars()将字符串转换为字符迭代器

比较两个字符串是否都包含'1'或都不包含'1'
如果相同则输出"YES"，否则输出"NO"
如果长度不相等，直接输出"NO"
如果没有第二行输入，则跳出循环
*/
use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();//获取标准输入句柄
    let mut lines = stdin.lock().lines();

    while let Some(Ok(line1)) = lines.next() {
        if let Some(Ok(line2)) = lines.next() {
            let s1 = line1.trim();
            let s2 = line2.trim();
            let l1 = s1.len();
            let l2 = s2.len();
            if l1 == l2 {
                let mut sum1 = 0;
                let mut sum2 = 0;
                for ch in s1.chars() { if ch == '1' { sum1 = 1; break; } }
                for ch in s2.chars() { if ch == '1' { sum2 = 1; break; } }
                if sum1 == sum2 { println!("YES"); } else { println!("NO"); }
            } else { println!("NO"); }
        } else { break; }
    }
}
///
/// BufRead：提供缓冲读取功能的trait
// BufReader：带缓冲的读取器，提高读取效率

use std::io::{self, BufRead, BufReader};

fn main() {
    let stdin = io::stdin();//返回标准输入流
    let mut reader = BufReader::new(stdin);//带缓冲的读取器实例
    let mut line = String::new();//临时存储读取的字符串行
    reader.read_line(&mut line).unwrap();//处理Result类型
    let n: usize = line.trim().parse().unwrap();
    line.clear();
    reader.read_line(&mut line).unwrap();
    let str0 = line.trim().chars().collect::<Vec<char>>();//存储第一个字符串的字符向量
    line.clear();
    reader.read_line(&mut line).unwrap();
    let str1 = line.trim().chars().collect::<Vec<char>>();
    let mut c1 = 0;//第一个字符串为'1'，第二个字符串不为'1'的位置数
    let mut c2 = 0;//第一个字符串不为'1'，第二个字符串为'1'的位置数
    let mut c3 = 0;//两个字符串都为'1'的位置数
    for i in 0..str0.len() {
        if str0[i] == '1' && str1[i] == '1' { c3 += 1 }//访问str0的第i个字符
        else if str0[i] == '1' { c1 += 1 }
        else if str1[i] == '1' { c2 += 1 }
    }
    c3 %= 2;//保留奇偶性
    if c2 == c1 + c3 + 1 { c3 += 1 }
    if c1 + c3 > c2 { println!("First") }
    else if c1 + c3 == c2 { println!("Draw") }
    else { println!("Second") }
}
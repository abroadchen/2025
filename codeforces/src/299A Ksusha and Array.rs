/**
.split(' ')
只分割单个空格字符
如果有多个连续空格，会产生空字符串元素
只识别 ASCII 空格字符（U+0020）
.split_whitespace()
分割所有空白字符
包括：空格、制表符（\t）、换行符（\n）、回车符（\r）、换页符等
自动跳过连续的空白字符，不会产生空字符串
识别所有 Unicode 空白字符
*/
use std::io::{self, BufRead};

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let t: usize = input.trim().parse().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let mut a: Vec<i64> = input.trim().split(' ').map(|x| x.parse().unwrap()).collect();
    a.sort();
    let mut c = 0;//能被最小元素整除的元素个数
    for j in 0..t {
        if a[j] % a[0] == 0 { c += 1; }
    }
    //if 表达式（不是语句），会返回一个值
    //是否所有元素都能被最小元素整除
    //如果是，则 ans 被赋值为 a[0]（最小元素）
    let ans = if c == t { a[0] } else { -1 };
    println!("{}", ans);
}
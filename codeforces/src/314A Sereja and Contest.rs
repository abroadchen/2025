use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();//获取标准输入流
    let mut lines = stdin.lock().lines();//获取输入行的迭代器，用于逐行读取输入
    let first_line = lines.next().unwrap().unwrap();//读取第一行
    let parts: Vec<i64> = first_line.split_whitespace()
        .map(|s| s.parse().unwrap()).collect();//将每个子串解析为数字
    let mut n = parts[0];
    let k = parts[1];
    let second_line = lines.next().unwrap().unwrap();//读取第二行
    let arr: Vec<i64> = second_line.split_whitespace()
        .map(|s| s.parse().unwrap()).collect();//解析每个元素为数字
    let mut t = 0i64;//存储计算结果
    let mut j = 1i64;//输出索引
    let mut i = 1i64;//循环计数器
    let mut idx = 0;//数组索引，从0开始
    while i <= n  && idx < arr.len() {//i小于等于n且数组索引未越界
        let a: i64 = arr[idx];//获取当前数组元素
        if t - (i - 1) * (n - i) * a < k {
            println!("{}", j);
            n -= 1;//模拟删除元素
            i -= 1;//下次循环i不变
        } else { t += a * (i - 1); }
        j += 1;//更新
        i += 1;
        idx += 1;
    }
}
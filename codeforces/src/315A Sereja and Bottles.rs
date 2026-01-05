/**
// 方案1: 使用 BufRead (推荐)
use std::io::{self, BufRead};
let mut lines = io::stdin().lock().lines();

// 方案2: 一次性读取所有内容
use std::io;
let mut input = String::new();
io::stdin().read_to_string(&mut input)?;
let mut lines = input.lines();

// 方案3: 使用 io::stdin().read_line()
use std::io::{self, Write};
let mut input = String::new();
io::stdin().read_line(&mut input)?;  // 但只能读一行
*/
use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    let n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
    let mut a = vec![0; 1_000];//每对数据的第一个数
    let mut b = vec![0; 1_000];//每对数据的第二个数
    let mut c = [0; 1_001];//统计数字出现次数
    for i in 0..n {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<i32> = line.split_whitespace()
            .map(|x| x.parse().unwrap()).collect();
        a[i] = parts[0];
        b[i] = parts[1];
        c[b[i] as usize] += 1;//b[i]位置的计数加1
    }
    let mut cnt = 0;
    for i in 0..n {
        c[b[i] as usize] -= 1;
        //移除了当前对的b值后，a[i]是否在剩余的b值中不存在
        if c[a[i] as usize] == 0 { cnt += 1; }
        c[b[i] as usize] += 1;
    }
    println!("{}", cnt);
}
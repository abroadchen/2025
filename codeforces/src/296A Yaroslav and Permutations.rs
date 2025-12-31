use std::io::{self, BufRead};

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();//从标准输入读取一行到 input 变量中
    let mut a: Vec<i32> = input.trim().split_whitespace().map(|s| s.parse().unwrap()).collect();
    a.sort();
    let mut c = 1;//连续相同元素
    let mut mx = 1;
    for i in 1..n {
        if a[i] == a[i - 1] { c += 1; if c > mx { mx = c; } } else { c = 1; }//当前元素不等于前一个元素，重置
    }
    if mx <= (n + 1) / 2 { println!("YES"); } else { println!("NO"); }
}
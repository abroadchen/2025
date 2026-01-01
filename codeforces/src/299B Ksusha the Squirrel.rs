use std::io::{self, BufRead};

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<&str> = input.trim().split_whitespace().collect();
    let n: usize = parts[0].parse().unwrap();
    let k: usize = parts[1].parse().unwrap();
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let s = input.trim();//去除字符串末尾的换行符
    let mut cnt = 0;//连续的 '#' 字符数量
    for c in s.chars().take(n) {//限制迭代次数为 n（最多遍历 n 个字符）
        if c == '#' { cnt += 1; } else { cnt = 0; }
        if cnt >= k { println!("NO"); return }
    }
    println!("YES");
}

use std::io;

fn main() {
    loop {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let s = input.trim();
        if s.is_empty() { break; }
        let chars: Vec<char> = s.chars().collect();//将迭代器收集到Vec<char>中便于索引访问
        let len = chars.len();//字符数组的长度
        let mut a = vec![0; 100005];//a[100005] = { 0 }
        for i in 1..len {
            if chars[i - 1] == chars[i] { a[i] = a[i - 1] + 1; } else {//如果相同，累加计数
                a[i] = a[i - 1];//不相同，保持前一个值不变
            }
        }
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let n: usize = input.trim().parse().unwrap();
        for _ in 0..n {
            input.clear();
            io::stdin().read_line(&mut input).unwrap();
            let parts: Vec<usize> = input.trim().split_whitespace()
                .map(|s| s.parse().unwrap()).collect();
            let x = parts[0];//查询的起始位置x和结束位置y
            let y = parts[1];
            println!("{}", a[y - 1] - a[x - 1]);//[x-1, y-1]内连续相同字符对的数量
        }
    }
}
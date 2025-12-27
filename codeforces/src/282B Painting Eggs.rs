use std::io;

struct Node {
    first: i64,
    second: i64,
}

fn main() {
    let mut buff = String::new();
    io::stdin().read_line(&mut buff).unwrap();
    let n: usize = buff.trim().parse().unwrap();
    let mut p = Vec::with_capacity(n);//预分配空间以提高效率
    for _ in 0..n {
        let mut buff = String::new();
        io::stdin().read_line(&mut buff).unwrap();
        let nums: Vec<i64> = buff.trim().split_whitespace()
            .map(|x| x.parse().unwrap()).collect();//将输入字符串处理为整数向量
        p.push(Node { first: nums[0], second: nums[1] });
    }
    let mut s = String::new();//存储结果
    let mut a = 0i64;
    let mut g = 0i64;
    for i in 0..n {
        let x = (a + p[i].first - g).abs();//选择A时的新差值
        let y = (g + p[i].second - a).abs();
        if x <= y {
            s.push('A');
            a += p[i].first;
        } else {
            s.push('G');
            g += p[i].second;
        }
    }
    if (a - g).abs() <= 500 { println!("{}", s); } else { print!("-1"); }
}
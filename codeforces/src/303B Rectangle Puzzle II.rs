use std::io;

// 如果余数为 0，则最大公约数就是被除数
fn gcd(x: i32, y: i32) -> i32 { if y == 0 { return x; } gcd(y, x % y) }
fn min(a: i32, b: i32) -> i32 { if a < b { a } else { b } }
fn main() {
    let stdin = io::stdin();
    loop {
        let mut input = String::new();
        stdin.read_line(&mut input).unwrap();
        let val: Vec<i32> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();//.map() 将每个字符串转换为整数
        if val.len() != 6 { break }
        let [n, m, x, y, a, b] =
            [val[0], val[1], val[2], val[3], val[4], val[5]];
        let g = gcd(a, b);
        let a = a / g;//将 a 和 b 约分到最简形式
        let b = b / g;
        let pw = min(n / a, m / b);//计算最大比例因子
        let len = pw * a;//计算矩形的实际长度和宽度 比例因子乘以基本比例
        let w = pw * b;
        let h1 = w / 2;
        let h2 = if w & 1 == 1 { h1 + 1 } else { h1 };
        //点 (x,y) 是否在中心区域 向上扩展 h1，向下扩展 h2
        let (u, d) = if m - y >= h1 && y >= h2 { (y + h1, y - h2) }
        //如果上边界不够空间，将上边界设为 m 如果下边界不够空间，将下边界设为 0
        else if m - y < h1 { (m, m - h1 - h2) } else { (h1 + h2, 0) };
        let h1 = len / 2;
        let h2 = if len & 1 == 1 { h1 + 1 } else { h1 };
        let (l, r) = if n - x >= h1 && x >= h2 { (x - h2, x + h1) }
        else if n - x < h1 { (n - h1 - h2, n) } else { (0, h1 + h2) };
        println!("{} {} {} {}", l, d, r, u);
    }
}
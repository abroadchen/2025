use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let n = parts[0];
    let k = parts[1];
    let mut ans = 0;
    for _ in 0..n {//循环n次，_表示不使用循环变量
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<i32> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        let x = parts[0];
        let y = parts[1];
        ans += (y - x + 1);//计算区间[x, y]中整数的个数（包含端点）
    }
    //需要多少个额外的单位才能使ans成为k的倍数
    if ans % k == 0 { println!("0"); } else { println!("{}", k - (ans % k)); }
}
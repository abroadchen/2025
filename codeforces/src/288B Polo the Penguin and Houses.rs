use std::io;

const MOD: i64 = 1000000007;
fn pw(mut base: i64, mut exp: i64, mode: i64) -> i64 {
    let mut ans = 1;
    base %= mode;//防止初始值过大
    while exp > 0 {
        if exp & 1 == 1 { ans = (ans * base) % mode; }//exp为奇数，将当前base乘到结果中
        base = (base * base) % mode;//将base平方
        exp >>= 1;
    }
    ans
}

fn main() {
    let stdin = io::stdin();
    let mut input = String::new();
    loop {
        input.clear();
        let x = stdin.read_line(&mut input).unwrap();//存储读取的字节数
        if x == 0 { break }
        let parts: Vec<i32> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        if parts.len() < 2 { break }//检查是否有足够的输入
        let n = parts[0] as i64;
        let k = parts[1] as i64;
        let ans = (pw(k, k - 1, MOD) * pw(n - k, n - k, MOD)) % MOD;
        println!("{}", ans);
    }
}
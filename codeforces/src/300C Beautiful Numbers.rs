use std::io;

const MOD: i64 = 1_000_000_007;

fn pw(x: i64, n: i64, p: i64) -> i64 {//(x^n) % p    x（底数），n（指数）
    let mut res = 1;
    let mut base = x % p;//底数
    let mut exp = n;//指数
    while exp > 0 {
        if exp & 1 == 1 { res = (res * base) % p; }//如果是奇数，将当前 base 乘入结果
        base = (base * base) % p;//底数平方
        exp >>= 1;
    }
    res
}

fn ok(x: i64, num: &[i64; 3]) -> bool {//数字 x 的每一位是否只包含 num[1] 或 num[2]
    let mut t = x.abs();
    if t == 0 { return t == num[1] || t == num[2]; }//目标数字包含 0
    while t > 0 {
        let d = t % 10;//取最后一位数字
        if d != num[1] && d != num[2] { return false; }//是否等于目标数字之一
        t /= 10;//去掉最后一位
    }
    true
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i64> = input.trim().split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut num = [0i64; 3];//索引0未使用
    num[1] = parts[0];//存储两个目标数字
    num[2] = parts[1];
    let n = parts[2];//存储总数
    let mut f = vec![0i64; (n + 1) as usize]; f[0] = 1;//阶乘数组
    for i in 1..=n as usize { f[i] = (f[i - 1] * i as i64) % MOD; }//f[i] = i! % MOD
    let mut ans = 0i64;
    for i in 0..=n as usize {
        if ok(num[1] * i as i64 + (n - i as i64) * num[2], &num) {
            let d = (f[i] * f[(n - i as i64) as usize]) % MOD;//f[i] * f[n-i]（分母）
            let x = pw(d, MOD - 2, MOD);//使用费马小定理计算逆元
            ans = (ans + x) % MOD;
        }
    }
    let res = (f[n as usize] * ans) % MOD;//n! * ans % MOD
    println!("{}", res);
}
use std::io;

const MOD: i64 = 1_000_000_007;

fn low_bit(x: i32) -> i32 { x & (-x) }
fn sum(x: i32, dp: &mut [i64]) -> i64 {//1到x位置的前缀和
    let mut t = 0i64;//结果变量
    let mut x = x;//避免借用冲突
    while x > 0 {
        t = (t + dp[x as usize]) % MOD;//累加dp[x]到t
        x = x - low_bit(x);//移动到树状数组的下一个节点
    }
    t
}
fn add(x: i32, s: i64, dp: &mut [i64]) {//x位置添加值s
    let mut x = x;
    while x <= 1_000_000 {
        dp[x as usize] = (dp[x as usize] + s) % MOD;
        x = x + low_bit(x);//移动到树状数组的父节点
    }
}

fn main() {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let n: i32 = input.trim().parse().unwrap();//解析第一行输入
    let mut dp = vec![0i64; 1_100_000];//树状数组
    let mut ans = 0i64;
    input.clear();
    std::io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i64> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    for i in 0..n as usize {
        let x = parts[i] as i32;//获取当前数字
        let s1 = sum(x, &mut dp);
        let s2 = sum(x - 1, &mut dp);
        let mut t = ((s1 + 1) % MOD) * (x as i64 % MOD) % MOD;//当前位置的贡献值
        t = (t - ((s1 - s2) % MOD)) % MOD;//减去重复计算的部分
        t = (t + MOD) % MOD;//确保结果为正数
        add(x, t, &mut dp);//x位置添加计算出的贡献值t
        ans = (ans + t) % MOD;//贡献值累加到最终答案
    }
    println!("{}", ans);
}
// dp[i][0]: 第i位s[i] <= ss[i]的方案数 55（00-99中满足条件的对数）
// dp[i][1]: 第i位s[i] >= ss[i]的方案数
// dp[i][3]: 第i位s[i] == ss[i]的方案数 10（00,11,22,...,99）
use std::io::{self, BufRead};
const MOD: i64 = 1_000_000_007;
fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let s: Vec<char> = input.trim().chars().collect();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let ss: Vec<char> = input.trim().chars().collect();
    let a = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    let aa = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1];
    let mut dp = vec![vec![0i64; 4]; n + 1];
    for i in 1..=n {
        if s[i-1] == '?' && ss[i-1] == '?' {
            dp[i][0] = 55; dp[i][1] = 55; dp[i][3] = 10;
        } else if s[i-1] == '?' {
            let x = ss[i-1].to_digit(10).unwrap() as usize;//数字值作为索引
            dp[i][0] = a[x] as i64; dp[i][1] = aa[x] as i64; dp[i][3] = 1;
        } else if ss[i-1] == '?' {
            let x = s[i-1].to_digit(10).unwrap() as usize;
            dp[i][0] = aa[x] as i64; dp[i][1] = a[x] as i64; dp[i][3] = 1;
        } else {
            if s[i-1] <= ss[i-1] { dp[i][0] = 1; }
            if s[i-1] >= ss[i-1] { dp[i][1] = 1; }
            if s[i-1] == ss[i-1] { dp[i][3] = 1; }
        }
    }
    let mut mn = 1i64;//s <= ss的总方案数
    let mut mx = 1i64;//s >= ss的总方案数
    let mut ans = 1i64;//总的方案数（无限制）
    let mut anse = 1i64;//s == ss的总方案数
    for i in 1..=n {
        mn = (mn * dp[i][0]) % MOD; mx = (mx * dp[i][1]) % MOD;
        anse = (anse * dp[i][3]) % MOD;
        if s[i-1] == '?' && ss[i-1] == '?' {//如果两个都是'?'，则有10*10=100种可能
            ans = (ans * 100) % MOD;
        } else if s[i-1] == '?' || ss[i-1] == '?' {//如果只有一个'?'，则有10种可能
            ans = (ans * 10) % MOD;
        }
    }
    let res = ((ans - mn - mx + anse) % MOD + MOD) % MOD;
    println!("{}", res);
}
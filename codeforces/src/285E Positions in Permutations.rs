use std::io;
const N: usize = 1007;
const MOD: i64 = 1_000_000_007;
fn add(a: &mut i64, b: i64) {
    *a += b;
    if *a >= MOD { *a -= MOD; }
}
fn c(n: usize, m: usize, f: &[i64], _inv: &[i64]) -> i64 {
    if n < m || n == 0 || m > n {//如果n<m或n=0且不是C(0,0)
        if n == 0 && m == 0 { return 1; }
        return 0;
    }
    (f[n] * _inv[m] % MOD * _inv[n - m]) % MOD//C(n,m) = n! / (m! * (n-m)!)
}

fn main() {
    let mut f = vec![0i64; N];//阶乘数组 f[i] = i!
    let mut _inv = vec![0i64; N];//阶乘逆元数组，_inv[i] = (i!)^(-1) mod MOD
    let mut inv = vec![0i64; N];//逆元数组，inv[i] = i^(-1) mod MOD
    f[0] = 1; _inv[0] = 1; inv[1] = 1;//0! = 1 (0!)^(-1) = 1^(-1) = 1 1^(-1) = 1
    for i in 2..N {//计算每个数的逆元
        inv[i] = ((MOD - MOD / i as i64) * inv[(MOD % i as i64) as usize]) % MOD;
    }
    for i in 1..N { f[i] = (f[i - 1] * i as i64) % MOD; }//计算阶乘
    for i in 1..N { _inv[i] = (_inv[i - 1] * inv[i]) % MOD; }//计算阶乘逆元
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.read_line(&mut input).unwrap();
    let parts: Vec<usize> = input.trim().split(' ').map(|x| x.parse().unwrap()).collect();
    let n = parts[0];
    let k = parts[1];
    //前i个位置，有j个相邻对，当前状态为u和v的方案数
    let mut dp = vec![vec![vec![vec![0i64; 2]; 2]; N]; N];
    dp[0][0][1][0] = 1;
    for i in 0..n {
        for j in 0..=i {
            for u in 0..2 {
                for v in 0..2 {
                    if dp[i][j][u][v] == 0 { continue; }//当前状态的方案数为0
                    let val = dp[i][j][u][v];//获取当前状态的值
                    add(&mut dp[i+1][j][v][0], val);//不将位置i+1与位置i形成相邻对
                    if u == 0 {//如果u为0，可以创建新的相邻对
                        add(&mut dp[i+1][j+1][v][0], val);//将val加到相邻对数+1的状态
                        if i + 1 < n { add(&mut dp[i+1][j+1][v][1], val); }//如果不是最后一个位置 将val加到另一个状态
                    } else {
                        if i + 1 < n { add(&mut dp[i+1][j+1][v][1], val); }
                    }
                }
            }
        }
    }
    let mut way = vec![0i64; N];//way[j]表示恰好有j个相邻对的方案数
    for j in 0..=n {
        for u in 0..2 {
            for v in 0..2 {
                add(&mut way[j], dp[n][j][u][v]);//累加所有状态的方案数
            }
        }
    }
    let mut ans = 0i64;
    for i in k..=n {
        let t = (c(i, k, &f, &_inv) * way[i]) % MOD * f[n - i] % MOD;//计算当前项
        if (i - k) % 2 == 0 { ans = (ans + t) % MOD; }
        else { ans = (ans - t + MOD) % MOD; }
    }
    println!("{}", ans);
}
/**
枚举到第i个数 加入了j个数 能产生l个满足恰有c个0空隙的准良好序列
*/
use std::io;

const N: usize = 105;
const P: i64 = 1_000_000_007;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<usize> = input.trim().split_whitespace().map(|x| x.parse().unwrap()).collect();
    let n = parts[0];
    let m = parts[1];
    let k = parts[2];
    let mut c = [[0; N]; N];//组合数数组
    let mut f = [[[[0i64; N]; N]; N]; 2];//表示状态
    let mut ans = 0i64;
    c[0][0] = 1;//C(0,0) = 1
    for i in 1..=n { f[1][i][i][1] = 1; }
    let mut i = 0;
    while i <= n {
        c[i + 1][0] = 1;
        i += 1;
        for j in 1..=i {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]).min(101);//限制值不超过 101
        }
    }
    let mut num = 1;//当前处理的阶段数
    let mut e = 1;//当前状态索引（0 或 1）
    while num < m {
        for i in num..=n {
            for j in 1..=i - num + 2 {
                for cv in 1..=k {
                    if f[e][i][j][cv] != 0 {
                        let mut x = j;//从 j 开始
                        while x + i <= n {
                            let t = cv * c[x - 1][j - 1];
                            if t <= k && t != 0 {
                                f[e^1][i + x][x - j][t] =
                                    (f[e^1][i+x][x-j][t]+f[e][i][j][cv]) % P;
                            }
                            x += 1;
                        }
                    }
                }
            }
            for j in 1..=k {//在阶段 e、已处理 i 个元素、某种模式/段落完成、约束值为 j 的状态下的方案数
                ans = (ans + ((m - num + 1) as i64) * f[e][i][0][j]) % P;
            }
        }
        for i in 0..N {
            for j in 0..N {
                for k in 0..N {
                    f[e][i][j][k] = 0;
                }
            }
        }
        num += 1;
        e ^= 1;
    }
    for i in m..=n {
        for j in 1..=k {
            ans = (ans + f[m&1][i][0][j]) % P;
        }
    }
    println!("{}", ans);
}
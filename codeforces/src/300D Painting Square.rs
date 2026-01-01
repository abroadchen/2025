/**
t[c-1][j]：用 c-1 维度处理 j 个元素的方案数
t[c-1][i-1-j]：用 c-1 维度处理 i-1-j 个元素的方案数
j + (i-1-j) = i-1：两部分元素总数为 i-1

构造一棵高度为 c 的树（有 i 个节点）
选择一个根节点（占1个节点）
左子树有 j 个节点（高度 ≤ c-1）
右子树有 i-1-j 个节点（高度 ≤ c-1）
两子树高度都 ≤ c-1，但整棵树高度为 c

dp[c][i]：通过 t[c-1] 计算高度恰好为 c 的树
t[c][i]：通过 dp[c] 计算高度不超过 c 的树
这样逐层构建，每一层都基于前一层的结果


*/
use std::io;

const MOD: i64 = 7340033;
const N: usize = 1_010;

fn main() {
    let mut dp = [[0i64; N]; 50];
    let mut t = [[0i64; N]; 50];
    for i in 0..=31 { dp[i][0] = 1; t[i][0] = 1; }
    for c in 1..=31 {//维度参数
        for i in 1..=1000 {//状态参数
            for j in 0..i {//遍历所有可能的分割点
                dp[c][i] = (dp[c][i] + t[c-1][j] * t[c-1][i-1-j]) % MOD;
            }
        }
        for i in 1..=1000 {
            for j in 0..=i {
                t[c][i] = (t[c][i] + dp[c][j] * dp[c][i-j] % MOD) % MOD;
            }
        }
    }
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let q: usize = input.trim().parse().unwrap();
    for _ in 0..q {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<usize> = input.trim().split_whitespace().map(|x| x.parse().unwrap()).collect();
        let mut n = parts[0];
        let k = parts[1];//连续1的个数
        let mut cnt = 0;
        while n & 1 == 1 && n > 1 { cnt += 1; n /= 2; }
        println!("{}", dp[cnt][k]);
    }
}
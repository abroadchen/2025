/**
idx: 当前处理的起始位置索引
rem: 剩余需要选择的区间数量
n: 总长度
cost: 二维向量，存储从位置i到位置j的最小成本
dp: 记忆化搜索数组，避免重复计算
如果剩余区间数为0，说明任务完成，返回成本0
如果当前索引超过n，说明无法完成任务，返回无穷大
检查记忆化数组，如果已经计算过该状态，直接返回结果

考虑不选择以idx开始的区间，直接跳到idx+1的情况
遍历所有可能的结束位置i（从idx到n）
检查剩余区间数是否足够覆盖[idx, i]这个区间
计算选择[idx, i]区间后的最小成本：选择该区间的成本+后续子问题的解
将结果存储到记忆化数组中并返回

n: 总长度
m: 可用区间数量
k: 需要选择的区间数
每个区间由左端点l、右端点r、成本c组成
更新cost数组，对每个可能的区间[l,j]记录最小成本
调用DFS函数，从位置1开始，选择k个区间
如果结果小于无穷大，输出最小成本
否则输出-1，表示无法完成任务
*/
use std::io;

const N: usize = 301;
const INF: i64 = 1_000_000_000_000_000_000;

fn dfs(idx: usize, rem: usize, n: usize, cost: &Vec<Vec<i64>>,
    dp: &mut Vec<Vec<i64>>) -> i64 {
    if rem == 0 { return 0; }
    if idx > n { return INF; }
    if dp[idx][rem] != -1 { return dp[idx][rem]; }
    let mut ret = INF;
    ret = ret.min(dfs(idx + 1, rem, n, cost, dp));
    for i in idx..=n {
        if rem >= i - idx + 1 {
            ret = ret.min(dfs(i + 1, rem - (i - idx + 1), n, cost, dp) +
                cost[idx][i]);
        }
    }
    dp[idx][rem] = ret;
    ret
}
fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let n = parts[0] as usize;
    let m = parts[1] as usize;
    let k = parts[2] as usize;
    let mut cost = vec![vec![INF; N]; N];
    let mut dp = vec![vec![-1; N]; N];
    for _ in 0..m {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<i32> = input.trim().split_whitespace()
            .map(|x| x.parse().unwrap()).collect();
        let l = parts[0] as usize;
        let r = parts[1] as usize;
        let c = parts[2] as i64;
        for j in l..=r { cost[l][j] = cost[l][j].min(c); }
    }
    let res = dfs(1, k, n, &cost, &mut dp);
    if res < INF { println!("{}", res) } else { println!("-1") }
}
/**
读取第一行输入（n, q, t） n（节点数）、q（查询数）、t（目标值）
按空白字符分割并解析为i64向量
s：存储每个节点的初始值
p：存储节点的父节点关系
fa：并查集的父节点数组
dp：背包DP数组
*/
use std::io;

const N: usize = 100010;
const M: usize = 310;
const MOD: i64 = 1_000_000_007;

fn dfs(x: usize, s: &[i64], p: &[usize]) -> i64 {
    if p[x] == 0 { return s[x]; }//没有父节点
    let fa = dfs(p[x], s, p);//从节点x到根的路径和
    fa + s[x]//父节点的路径和 + s[x]
}

fn find(x: usize, fa: &mut [usize]) -> usize {
    if fa[x] == x { x }
    else {
        fa[x] = find(fa[x], fa);//递归查找根节点并进行路径压缩
        fa[x]
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i64> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let n = parts[0] as usize;
    let q = parts[1] as usize;
    let mut t = parts[2];
    let mut s = vec![0i64; N];
    let mut p = vec![0usize; N];
    let mut fa = vec![0usize; N];
    let mut dp = vec![0i64; (t + 1) as usize];
    let mut input  = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let v: Vec<i64> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();//读取节点的初始值
    for i in 1..=n { s[i] = v[i - 1]; }//将输入值存储到s数组中（索引从1开始）
    for i in 1..=n { fa[i] = i; }
    for _ in 1..=q {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<usize> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        let a = parts[0];//读取每对节点a和b
        let b = parts[1];
        let f1 = find(a, &mut fa);//查找a和b的根节点
        let f2 = find(b, &mut fa);
        if f1 == f2 { println!("0"); return; }//如果在同一连通分量中（形成环），输出0并返回
        fa[f1] = f2;//合并两个连通分量
        p[b] = a;//设置b的父节点为a
    }
    let mut k = vec![0i64; M * 4];//物品数组k
    let mut op = 0i64;
    for i in 1..=n {
        if p[i] != 0 {//节点i有父节点
            k[op as usize + 1] = dfs(i, &s, &p);//从i到根节点的路径和
            t -= k[op as usize + 1] - s[i];//调整目标值t
            op += 1;
        } else {
            k[op as usize + 1] = s[i];//使用s[i]的原始值
            op += 1;
        }
    }
    if t < 0 { println!("0"); return }//目标值小于0，无法达成
    dp[0] = 1;//0元有1种方法
    for i in 1..=op as usize {
        for l in k[i]..=t {//对于每个物品k[i]
            dp[l as usize] = (dp[l as usize] + dp[(l - k[i]) as usize]) % MOD;
        }
    }
    println!("{}", dp[t as usize] % MOD);
}
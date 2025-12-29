/**
当前节点u，父节点f，子树大小数组siz，父节点数组fa，邻接表g
初始化当前节点u的子树大小为1（包含自己）
记录节点u的父节点为f
遍历与节点u相邻的所有节点v
如果相邻节点v是父节点f，则跳过（避免往回走）
递归调用DFS，以v为当前节点，u为父节点继续遍历
将子节点v的子树大小累加到当前节点u上
C(n,2) = n*(n-1)/2

Vec<usize>实现了IntoIterator，其Item类型是&usize
*/
use std::io;

fn dfs(u: usize, f: usize, siz: &mut Vec<usize>, fa: &mut Vec<usize>, g: &Vec<Vec<usize>>) {
    siz[u] = 1;
    fa[u] = f;
    for &v in &g[u] {
        if v == f { continue }
        dfs(v, u, siz, fa, g);
        siz[u] += siz[v];
    }
}

fn c(n: i64) -> i64 {
    if n < 2 { return 0 }
    n * (n - 1) >> 1
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut g: Vec<Vec<usize>> = vec![Vec::new(); n + 1];//节点编号从1开始
    for _ in 0..n-1 {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<usize> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        let u = parts[0];
        let v = parts[1];
        g[u].push(v); g[v].push(u);
    }
    let mut siz: Vec<usize> = vec![0; n + 1];
    let mut fa: Vec<usize> = vec![0; n + 1];
    dfs(1, 0, &mut siz, &mut fa, &g);//计算每个节点的子树大小
    let ans = c(n as i64) * c(n as i64);//总的可能组合数
    let mut ret = ans;
    for u in 1..=n {//遍历每个节点u，计算与当前节点相关的组合数
        let mut n1 = c(n as i64);//跨过节点u的路径数
        let mut n2 = c(siz[u] as i64);//u子树内的路径数
        for &v in &g[u] {
            if v != fa[u] {
                n1 -= c(siz[v] as i64);//减去v子树的贡献
                n2 -= c(siz[v] as i64);
            } else { n1 -= c((n - siz[u]) as i64); }//减去除了u子树以外的部分
        }
        ret -= (2 * n1 * n2 - n2 * n2);//减去重复计算的部分 双向路径对数 2内部的路径对数
    }
    println!("{}", ret);
}
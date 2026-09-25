//
// Created by Psy.C on 2026/9/24.
//
/**
f[n][k] 存储 dfs(n,k) 的结果，避免重复递归
边界：
k == 0 → 返回 1（什么都没有，唯一）。
n == 1 → 只在 k==1 时返回 1，否则 0。
f[n][k] != -1 表示已算过，直接返回（记忆化）。
每个转移都用 dfs(n-1, i) * dfs(n-1, 剩余) 的形式，把"长度为 n-1 的两部分"拼起来（卷积），再乘上对应系数（表示该组合方式的排列/赋值数量）。
四种转移对应四种不同的组合/连接规则：
A：两个子结构直接拼接，i 与 k-i 分配，系数 1。
B：拼接时合并掉 1 个 k（k-i-1），i < k，系数 1。
C：拼接后某种位置有 2k 种赋值/旋转方式。
D：拼接后某种合并会多出 k+1 个选项，组合成 (k+1)*k 种方式。
系数 k*2 和 (k+1)*k 是有组合含义的：某结构有 k 个"可插入位置"，每个位置有两种方向 → 2k；两个位置独立选 → k(k+1) 等。
所有累加取模 mod
读入 n，记忆化表初始化为 -1（未计算）。
输出 dfs(n, 1)：即规模为 n 时 k=1 的结构总数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 410, mod = 1e9+7;

int f[N][N];
int dfs(int n, int k) {
    if (!k) return 1;
    if (n == 1) return k == 1;
    if (f[n][k] != -1) return f[n][k];
    f[n][k] = 0;
    for (int i = 0; i <= k; ++i)
        f[n][k] = (f[n][k] + 1ll*dfs(n-1, i)*dfs(n-1, k-i))%mod;
    for (int i = 0; i < k; ++i)
        f[n][k] = (f[n][k] + 1ll*dfs(n-1, i)*dfs(n-1, k-i-1))%mod;
    for (int i = 0; i <= k; ++i)
        f[n][k] = (f[n][k] + 1ll*dfs(n-1, i)*dfs(n-1, k-i)%mod*k*2)%mod;
    for (int i = 0; i <= k+1; ++i)
        f[n][k] = (f[n][k] + 1ll*dfs(n-1, i)*dfs(n-1, k+1-i)%mod*(k+1)*k)%mod;
    return f[n][k];
}

int main() {
    fast;
    int n; cin >> n;
    memset(f, -1, sizeof(f));
    cout << dfs(n, 1) << '\n';
    return 0;
}
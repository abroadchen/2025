//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
f[N][3]：DP 数组，f[u][0/1/2] 表示以 u 为根的子树的三种状态计数。
G[N]：邻接表，存储无向树的边（G[u] 存与 u 相邻的所有节点）
深搜，u 是当前节点，p 是它的父节点（用于避免往回走）
初始化当前节点三种状态的基础值：

f[u][0] = 1（初始：不选 u 的一种基础情况）
f[u][1] = 0（初始 0）
f[u][2] = 1（初始：选 u 的一种基础情况）
不同题目对三种状态含义定义不同，这题里大致是：0 表示某类选择方案、1 表示另一类、2 表示第三类的数量
定义 pre 数组，用来暂存某个关键时刻的 f[u][2] 值（前缀信息），供后面的后缀计算使用
遍历 u 的所有邻居 v：

若 v == p（是父节点），往 pre 里压入占位 0 并 continue，跳过。
否则递归 dfs(v, u) 先算子树。
把当前 f[u][2] 压入 pre（注意：这是更新前的旧值，即"还未把这个孩子算进去"的 f[u][2]）。
更新 f[u][0]：
f[u][0] = f[u][0] * ((f[v][0] + f[v][1]) % mod) % mod
即孩子 v 用 f[v][0] + f[v][1] 两种方案的乘积累乘进 f[u][0]。
更新 f[u][2]：
f[u][2] = f[u][2] * ((f[v][0] + (f[v][1]+f[v][1]) % mod) % mod) % mod
孩子 v 用 f[v][0] + 2*f[v][1] 累乘进 f[u][2]（f[v][1]+f[v][1] 就是 2*f[v][1]）
第二个循环从后往前遍历邻居（逆序，后缀方式处理）：

suf 初始为 1，是"后缀累积"的量。
对每个非父孩子的 v：
更新 f[u][1]：
f[u][1] += f[v][2] * pre[i] % mod * suf % mod
pre[i] 是逆序前那个"前缀"信息（前面对应位置存的 f[u][2] 旧值），这样 pre[i] * suf 就是"除了当前这个孩子以外所有孩子的某种乘积"，再乘上 f[v][2]，累加进 f[u][1]。
更新后缀乘积 suf = suf * ((f[v][0] + 2*f[v][1]) % mod) % mod
读入 n（节点数）。
循环读入 n-1 条边 u v，由于是无向边，所以 G[u].push_back(v) 和 G[v].push_back(u) 都压入。
以节点 1 为根（父节点设为 0）调用 dfs(1, 0)。
输出最终答案：(f[1][0] + f[1][1]) % mod，即根节点状态 0 和状态 1 的方案数之和，取模

这套 pre 前缀 + suf 后缀的技巧，通常用于做"所有子树的某种乘积"时，单独排除某一个子树（避免 O(deg²) 的重复累乘），是树上 DP 中常见的优化写法。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define sz(x) ((int)(x).size())
using namespace std;

constexpr int N = 3e5+10, mod = 998244353;

int f[N][3];
vector<int> G[N];
void dfs(int u, int p) {
    f[u][0] = 1; f[u][1] = 0; f[u][2] = 1;
    vector<int> pre;
    for (auto v : G[u]) {
        if (v == p) { pre.push_back(0); continue; }
        dfs(v, u);
        pre.push_back(f[u][2]);
        f[u][0] = 1ll*f[u][0]*((f[v][0]+f[v][1])%mod)%mod;
        f[u][2] = 1ll*f[u][2]*((f[v][0]+(f[v][1]+f[v][1])%mod)%mod)%mod;
    }
    int suf = 1;
    for (int i = sz(G[u])-1; i >= 0; i--) {
        int v = G[u][i];
        if (v == p) continue;
        (f[u][1] += 1ll*f[v][2]*pre[i]%mod*suf%mod) %= mod;
        suf = 1ll*suf*((f[v][0]+(f[v][1]+f[v][1])%mod)%mod)%mod;
    }
}

int n;
void out() {
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }
    dfs(1, 0);
    cout << (f[1][0]+f[1][1])%mod << '\n';
}



int main() {
    fast;
    int T = 1;
    while (T--) out();
    return 0;
}
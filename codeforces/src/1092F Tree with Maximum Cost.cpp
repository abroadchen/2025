//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
head[u]：u 的第一条边的编号；e[i].nxt：下一条边；e[i].to：边的另一端点。
add 在头部插入一条边（无向图各加一次）。N<<1 因为每条无向边存两条
从根 1 出发，d 表示当前深度。
dep[x]=d：记录 x 的深度。
sz[x]=a[x] 初始化，然后累加所有子树的 sz → sz[x] = 以 x 为根的子树内所有节点权值之和。
作用：求出每个点的深度 dep 和子树权值和 sz
如果 x 不是根，dp[x] = dp[fa] + z - sz[x] - sz[x]，其中 z = 全树权值总和。
推导：把根从 fa 换到 x 时，x 子树内的那些点（权值和 sz[x]）离根各近了 1（贡献 -sz[x]），而其余点（权值和 z - sz[x]）离根各远了 1（贡献 + (z - sz[x])）。合计变化 = -(sz[x]) + (z - sz[x]) = z - 2*sz[x]。
所以 dp[x] = dp[fa] + (z - 2*sz[x])，即题目里写的 dp[fa] + z - sz[x] - sz[x]。
递归继续换根，算出所有点的 dp
读 n 个点权值，边读边累加 z = 全树总权值
读 n-1 条边，建成无向图。
dfs(1,0,0)：第一次 DFS，求出所有点的 dep 和 sz。
计算根节点 1 的初始代价 dp[1] = Σ(dep[i] * a[i])（所有点到根的带权距离和，根深度为 0，x 越深贡献越大）。
dfs2(1,0)：从根开始换根递推，填出所有点的 dp
遍历所有点，取 dp 的最大值作为答案输出。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 1e6+10;

struct edge { int to, nxt; } e[N<<1];
int head[N], tot;
void add(int u, int v) {
    e[++tot].to = v; e[tot].nxt = head[u]; head[u] = tot;
}

int dep[N], sz[N], a[N];
void dfs(int x, int fa, int d) {
    dep[x] = d; sz[x] = a[x];
    for (int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v,x,d+1);
        sz[x] += sz[v];
    }
}
int dp[N], z;
void dfs2(int x, int fa) {
    if (x != 1) dp[x] = dp[fa] + z - sz[x] - sz[x];
    for (int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs2(v,x);
    }
}

int n, u, v, ans;
signed main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> a[i]; z += a[i]; }
    rep(i,n-1) {
        cin >> u >> v; add(u, v); add(v, u);
    }
    dfs(1,0,0);
    rep(i,n) dp[1] += dep[i]*a[i];
    dfs2(1,0);
    rep(i,n) ans = max(ans, dp[i]);
    cout << ans;
    return 0;
}
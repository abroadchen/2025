//
// Created by Psy.C on 2026/10/12.
//
/**
dfs 从某点出发遍历整棵树，把每个节点的深度（到根距离）写进数组 d。fa 是父节点避免回走
标准求树直径的两遍 DFS 法：

先随便从 1 出发找最远点 p1，
再从 p1 出发找最远点 p2，p1-p2 即为一条直径，
d1[] = 每个点到 p1 的距离，d2[] = 每个点到 p2 的距离。
直径上任意点满足 d1[i] + d2[i] == d1[p2]（到两端距离之和 = 直径长度）。
所以筛选出不在直径上、且 du[i]==1（当前是叶子）的点进入队列——这些是要通过操作"连出去"的候选点。
对每个叶子 i，操作记录为 (i, 目标端点, i)：把 i 连到 d1、d2 中更远的那一端（p1 或 p2）。
贡献 ans += max(d1[i], d2[i])。
把 i 标记处理（f[i]=1，从树中"删掉"），它的父节点 v 度数减 1；若 v 变成叶子则入队，继续处理。这是自叶子向上"剥洋葱"式的删除顺序。
意义：每次将一个点连接到直径端点，得到最大可增的路径长度；从叶子开始能保证贪心正确（离直径最远的分支先连）
(1+d)*d/2 是等差数列求和：把直径上的点（含 p1、p2）依次连起来，贡献为 1+2+...+d = d(d+1)/2，其中 d = d1[p2] 是直径长度。
先输出 m 条叶子操作，再 dfs2(p1, -1, p2) 输出直径主干上的操作
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ll long long
using namespace std;

constexpr int N = 2e5+10;

vector<int> g[N];
void dfs(int x, int fa, int *d) {
    rep(i,g[x].size()) {
        int v = g[x][i];
        if (v != fa) { d[v] = d[x] + 1; dfs(v, x, d); }
    }
}

int f[N];
//从 p1 出发，沿直径（未处理点）依次输出 (当前点, p2, 当前点)，把直径主干上的连接操作补全输出
void dfs2(int x, int fa, int p) {
    rep(i,g[x].size()) {
        int v = g[x][i];
        if (!f[v] && v != fa) {//未处理过且不是父节点
            cout << x << ' ' << p << ' ' << x << '\n';
            dfs2(v, x, p);//沿直径继续
        }
    }
}

int n, j, k, du[N], d1[N], d2[N], a[N], b[N], c[N];
queue<int> q;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        cin >> j >> k;
        g[j].push_back(k); g[k].push_back(j);
        du[k]++, du[j]++;
    }
    int p1 = 0, p2 = 0, m = 0; d1[1] = 0; dfs(1, -1, d1);
    for (int i = 1; i <= n; ++i)
        if (m < d1[i]) { m = d1[i]; p1 = i; }
    d1[p1] = 0; dfs(p1, -1, d1);
    m = 0;
    for (int i = 1; i <= n; ++i)
        if (m < d1[i]) { m = d1[i]; p2 = i; }
    d2[p2] = 0; dfs(p2, -1, d2);
    ll ans = 0; m = 0;
    for (int i = 1; i <= n; ++i)
        if (d1[i]+d2[i] != d1[p2] && du[i] == 1) q.push(i);
    while (!q.empty()) {
        int i = q.front(); q.pop();
        rep(u,g[i].size()) {
            int v = g[i][u];
            if (f[v]) continue;
            ans += max(d1[i], d2[i]);
            a[++m] = i; b[m] = d1[i] > d2[i] ? p1 : p2; c[m] = i;
            f[i] = 1; du[v]--;
            if (du[v] == 1) q.push(v);
        }
    }
    ans += 1ll*(1+d1[p2])*d1[p2]/2;
    cout << ans << '\n';
    for (int i = 1; i <= m; ++i)
        cout << a[i] << ' ' << b[i] << ' ' << c[i] << '\n';
    dfs2(p1, -1, p2);
    return 0;
}
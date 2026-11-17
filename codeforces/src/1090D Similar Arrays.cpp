//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
n 顶点数，m 边数。
(n-1)*n/2 是 n 个顶点完全图的边数。
如果 m 已经等于完全图边数（也就是这个图本身是 N 阶完全图），则无法构造出这样的两组排列 → 输出 NO。
理由：完成图任两顶点都有边，而排列里只有相邻对才被要求"不相邻"；若图是完全图，任何相邻的顶点对都构成边，无法同时满足 → 无解
e[u] 邻接表。
deg[u] 度数
选度数最小的顶点 x。
因为不是完全图，x 的度 < n-1，所以它至少有一个非邻接顶点
先把 x 的所有邻接点都标记 vis=1。
遍历 1..n，找到第一个既不是 x、又不在 x 邻接表中的顶点 → y。
即 (x, y) 这条边不在原图中（x 与 y 不相邻）。这是整个构造的核心
对顶点 x：
a[x] = 1，b[x] = 1。
对顶点 y：
a[y] = 2，b[y] = 1。
其余顶点：a[i] = b[i] = 3,4,5,...（依次递增）。
最终输出这两个序列 a[1..n] 和 b[1..n]，每个都是一个 1..n 的排列
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5;

int n, m, deg[N], a[N], b[N];
vector<int> e[N];
bool vis[N];
int main() {
    fast;
    cin >> n >> m;
    if (m == (n-1)*n/2) { cout << "NO\n"; return 0; }
    rep(i,m) {
        int u, v; cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
        deg[u]++; deg[v]++;
    }
    int x = 1;
    rep(i,n) if (deg[i] < deg[x]) x = i;
    for (int u : e[x]) vis[u] = 1;
    int y = 0;
    rep(i,n) if (i != x && vis[i] == 0) { y = i; break; }
    a[x] = 1; a[y] = 2; b[x] = 1; b[y] = 1;
    int cnt = 3;
    rep(i,n) {
        if (i == x || i == y) continue;
        a[i] = cnt; b[i] = cnt; cnt++;
    }
    cout << "YES\n";
    rep(i,n) cout << a[i] << ' ';
    cout << '\n';
    rep(i,n) cout << b[i] << ' ';
    return 0;
}
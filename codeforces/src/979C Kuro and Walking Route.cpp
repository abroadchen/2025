//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
从 x 出发，禁止经过节点 nt，统计可达节点数累加到 l。nt 在此作为"跳过该邻居"用，效果上等价于在树中切断与 nt 的连接来遍历
建 n 节点无向树，两个特殊点 x、y。
dfs(x, a, y)：从 x 出发跳过 y，得 x 侧连通块大小，令 a = n - 该大小 = y 侧大小。
dfs(y, b, x)：同样得 y 侧大小，令 b = n - 该大小 = x 侧大小。
答案 = n*(n-1) - a*b = 总"有序点对数"(u≠v) 减去分别落在 x 侧、y 侧的点对数，即统计所有不横跨边 (x,y) 的有序点对数量
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 3e5+10;

struct grh {
    int len = 1, head[N], nxt[N<<1], ver[N<<1];
    void ins(int u, int v) {
        ver[++len] = v; nxt[len] = head[u]; head[u] = len;
    }
    void add(int u, int v) { ins(u, v); ins(v, u); }
} G;

bool vis[N];
void dfs(int x, int &l, int nt) {
    vis[x] = 1, ++l;
    for (int i = G.head[x]; i; i = G.nxt[i]) {
        int v = G.ver[i];
        if (!vis[v] && v != nt) dfs(v, l, nt);
    }
}

int n, x, y, a, b;
int main() {
    fast;
    cin >> n >> x >> y;
    for (int i = 1, u, v; i < n; ++i) cin >> u >> v, G.add(u, v);
    dfs(x, a, y); a = n - a;
    memset(vis, 0, sizeof vis);
    dfs(y, b, x); b = n - b;
    cout << 1ll*n*(n-1)-1ll*a*b;
    return 0;
}
//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
g[c]：颜色 c 的所有点编号（按点的颜色归类）。
f[u]：点 u 的邻接点（无向图邻接表）。
dis[i][c]：点 i 到颜色 c 的最近距离（INF 表示不可达或不存在）
对某种颜色 x：
起点是所有颜色为 x 的点（g[x] 中所有点），它们到颜色 x 的距离为 0（先入队，赋 dis=0）。
多源 BFS：正常 BFS 扩散，dis[v][x] = dis[u][x]+1，松弛到颜色 x 的最近距离。
结果：dis[i][x] 是所有点 i 到最近一个颜色为 x 的点的距离。
（因为 BFS 边权为 1，第一次访问即最短路。）
读入 n 点、m 边、k 种颜色、s（取前 s 小）。
读入每个点颜色 a[i]，并加入 g[颜色]。
建无向图。
dis 初始化为大数（0x3f）。
对 每种颜色 做一次多源 BFS，填 dis[·][该颜色]。
复杂度：k 次 BFS，每次 O(n+m)，总 O(k(n+m))（k 通常 ≤100，可行）
对每个点 i，取出它到所有 k 种颜色的距离 dis[i][1..k]，排序。
取前 s 个最小值求和（即离 i 最近的 s 种颜色），输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+10, M = 105;

vector<int> g[M], f[N];
int dis[N][M];
void bfs(int x) {
    queue<int> q;
    for (auto i : g[x]) q.push(i), dis[i][x] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : f[u])
            if (dis[u][x] + 1 < dis[v][x])
                q.push(v), dis[v][x] = dis[u][x] + 1;
    }
}

int n, m, k, s, a[N];
int main() {
    fast;
    cin >> n >> m >> k >> s;
    for (int i = 1; i <= n; ++i) cin >> a[i], g[a[i]].push_back(i);
    while (m--) {
        int u, v; cin >> u >> v;
        f[u].push_back(v), f[v].push_back(u);
    }
    memset(dis, 0x3f, sizeof dis);
    for (int i = 1; i <= k; ++i) bfs(i);
    for (int i = 1; i <= n; ++i) {
        sort(&dis[i][1], &dis[i][k+1]);
        ll ans = 0;
        for (int j = 1; j <= s; ++j) ans += dis[i][j];
        cout << ans << ' ';
    }
    return 0;
}
//
// Created by Psy.C on 2026/2/27.
//
/**
dis[t][i][j]：从第t个点出发到(i,j)的最短距离
vis[t][i][j]：BFS访问标记
a[N][N]：网格地图
v[N*N*2]：每个点的权重值

从点(x,y)开始BFS计算最短距离
只能在'.'位置移动
每步代价为v[t]

Dinic最大流算法实现
n, m：网格尺寸
k：点对数量
id1, id2：网格点在图中的ID
s, t：源点和汇点

// 建立网络流图
// 添加源点到左部节点
// 添加右部节点到汇点
// 添加左侧点到网格点的边
// 添加网格点到右侧点的边
检查是否可以在距离限制x内完成匹配
构建二分图并跑最大流

如果k=q，交换数据以确保正确的对应关系
为网格中的每个点分配唯一的ID
预计算每个点到网格中各点的最短距离

 */
#include <bits/stdc++.h>
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 23;

ll dis[N*N*2][N][N];
bool vis[N*N*2][N][N];
char a[N][N];
int v[N*N*2];
inline void bfs(const int t, int x, int y) {
    memset(dis[t], 0x7f, sizeof dis[t]);
    memset(vis[t], 0, sizeof vis[t]);
    queue<ii> q; q.emplace(x, y);
    dis[t][x][y] = 0; vis[t][x][y] = true;
    while (!q.empty()) {
        int i = q.front().first, j = q.front().second; q.pop();
        if (!vis[t][i][j-1] && a[i][j-1] == '.') {
            q.emplace(i, j-1);
            dis[t][i][j-1] = dis[t][i][j] + v[t];
            vis[t][i][j-1] = true;
        }
        if (!vis[t][i][j+1] && a[i][j+1] == '.') {
            q.emplace(i, j+1);
            dis[t][i][j+1] = dis[t][i][j] + v[t];
            vis[t][i][j+1] = true;
        }
        if (!vis[t][i-1][j] && a[i-1][j] == '.') {
            q.emplace(i-1, j);
            dis[t][i-1][j] = dis[t][i][j] + v[t];
            vis[t][i-1][j] = true;
        }
        if (!vis[t][i+1][j] && a[i+1][j] == '.') {
            q.emplace(i+1, j);
            dis[t][i+1][j] = dis[t][i][j] + v[t];
            vis[t][i+1][j] = true;
        }
    }
}

struct node { int to, nxt; ll val; } e[1000001];

int cnt=1, head[10001];
inline void add(const int fr, const int to, const ll val) {
    e[++cnt] = {to, head[fr], val};
    head[fr] = cnt;
}

int tot, dep[30001], cur[30001];
inline int bfs(const int s, const int t) {
    for (int i = 0; i <= tot; ++i) dep[i] = 0, cur[i] = head[i];
    static int q[30001], qh, qt; qh = 1, qt = 0;
    q[++qt] = s, dep[s] = 1;
    while (qh <= qt) {
        const int u = q[qh++];
        for (int i = head[u], v; i; i = e[i].nxt) {
            v = e[i].to;
            if (e[i].val && !dep[v]) {
                dep[v] = dep[u] + 1;
                q[++qt] = v;
            }
        }
    }
    return dep[t];
}

inline ll dfs(const int& u, const int& t, const ll& flow) {
    if (u == t) return flow;
    ll res = 0;
    for (int i = cur[u], v; i && res < flow; i = e[i].nxt) {
        cur[u] = i; v = e[i].to;
        if (e[i].val && dep[v] == dep[u] + 1) {
            if (const ll x = dfs(v, t, min(e[i].val, flow-res))) {
                e[i].val -= x;
                e[i^1].val += x;
                res += x;
            }
        }
    }
    if (res < flow) dep[u] = -1;
    return res;
}

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

inline ll dinic(const int s, const int t) {
    ll ans = 0, x;
    while (bfs(s, t))
        for (; (x = dfs(s, t, inf)); ans += x) {}
    return ans;
}

int n, m, k, id1[N][N], id2[N][N], s, t;
inline bool check(const ll x) {
    for (int i = 0; i <= tot; ++i) head[i] = 0;
    cnt = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            add(id1[i][j], id2[i][j], 1);
            add(id2[i][j], id1[i][j], 0);
        }
    for (int i = 1; i <= k; ++i) add(s, i, 1), add(i, s, 0);
    for (int i = k+1; i <= 2*k; ++i) add(i, t, 1), add(t, i, 1);
    for (int i = 1; i <= k; ++i)
        for (int a = 1; a <= n; ++a)
            for (int b = 1; b <= m; ++b) if (dis[i][a][b] <= x) {
                add(i, id1[a][b], 1);
                add(id1[a][b], i, 0);
            }
    for (int i = k+1; i <= 2*k; ++i)
        for (int a = 1; a <= n; ++a)
            for (int b = 1; b <= m; ++b) if (dis[i][a][b] <= x) {
                add(id2[a][b], i, 1);
                add(i, id2[a][b], 0);
            }
    const int c = dinic(s, t);
    return c == k;
}

int p, q, x[N*N*2], y[N*N*2];
int main() {
    scanf("%d%d%d%d", &n, &m, &p, &q);
    if (abs(p - q) != 1) { puts("-1"); return 0; }
    for (int i = 1; i <= n; ++i) scanf("%s", a[i] + 1);
    k = max(p, q);
    for (int i = 1; i <= 2*k; ++i) scanf("%d%d%d", x+i, y+i, v+i), ++tot;
    if (k != q) {
        swap(x[1], x[p+1]);
        swap(y[1], y[p+1]);
        swap(v[1], v[p+1]);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) id1[i][j] = ++tot;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) id2[i][j] = ++tot;
    bfs(1, x[1], y[1]);
    for (int i = 1; i <= 2*k; ++i) bfs(i, x[i], y[i]);
    s = ++tot, t = ++tot;
    ll l = 0, r = inf;
    while (l < r) {
        if (const ll mid = (l + r) >> 1; check(mid)) r = mid;
        else l = mid + 1;
    }
    if (l == inf) puts("-1"); else printf("%lld\n", l);
    return 0;
}
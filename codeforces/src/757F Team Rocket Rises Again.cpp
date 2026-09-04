//
// Created by Psy.C on 2026/9/4.
//
/**
e[] 存储每条边，head[x] 是以 x 为起点的边链表头。每条无向边存两次（add(u,v,w) + add(v,u,w)），所以数组开 N<<1
priority_queue<ii> 默认是大根堆，因此压入 -dis[y] 来当作小根堆用（队首是"负值最小"即"dis 最小"的点）。dis[x] 最终存的是 s 到 x 的最短路
先把深的点跳到同一深度，再一起往上跳到 LCA。f[x][i] 表示 x 向上跳
2
i
2
i
  步到达的祖先。这里 M=19，即最多跳
2
19
2
19
  层

第一遍循环：遍历所有边，凡是"松弛边"（dis[x] + w == dis[y]，即能从 x 一步走到更短路上的 y），就算 y 的一个最短路前驱，v[y]++。所以 v[y] 记录了点 y 在最短路径 DAG 中有几个来源（入度）。
BFS 队列：从源点 s 出发按最短路顺序（用 top[] 数组当队列）逐层扩展。因为最短路边一定是从近到远单向的，所以这个拓扑序是合法的，先处理距离近的点。
求父节点：对每个最短路前驱 x，若 y 还没有父节点就设 f[y][0] = x；若已有父，则把父更新为"当前父与 x 的 LCA"。这样做的含义是：当 y 能由多个最短路前驱到达时，为了保证后续"合并多棵最短路树"的树形结构仍是一棵树，把 y 的父节点抬升到多个前驱的公共祖先（LCA）处。这也解释了为什么需要维护倍增表并求 LCA。
入队条件：只有 y 的所有最短路前驱都被处理完（v[y] 减到 0）才把它放入队列继续往下 BFS

利用 BFS 队列 top[] 的逆序（从远到近）做树上的自底向上统计：
sz[top[i]]++：每个点至少算自己；
sz[f[top[i]][0]] += sz[top[i]]：把子树大小累加给父节点；
沿途用 ans 记录所有子树大小的最大值。
最终输出最大子树大小 ans

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 3e5+10, M = 19;
struct node { int to, nxt, val; } e[N<<1];

int tot, head[N];
void add(int x, int y, int z) {
    e[++tot].to = y; e[tot].nxt = head[x]; e[tot].val = z; head[x] = tot;
}

int dis[N], s, v[N];
priority_queue<ii> q;
void dijkstra() {
    memset(dis, 0x3f, sizeof dis); dis[s] = 0;
    q.emplace(0, s);
    while (!q.empty()) {
        int x = q.top().second; q.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (int i = head[x]; i; i = e[i].nxt) {
            int y = e[i].to;
            if (dis[x] + e[i].val < dis[y]) {
                dis[y] = dis[x] + e[i].val;
                q.emplace(-dis[y], y);
            }
        }
    }
}

int dep[N], f[N][M+1];
int lca(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    for (int i = M; i >= 0; --i)
        if (dep[f[y][i]] >= dep[x]) y = f[y][i];
    if (x == y) return x;
    for (int i = M; i >= 0; --i)
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}

int hd, tl, top[N], n;
void build() {
    hd = 1, tl = 1, top[1] = s;
    memset(v, 0, sizeof v);
    //统计每个点的"最短路前驱"数量
    for (int x = 1; x <= n; ++x) {
        for (int i = head[x]; i; i = e[i].nxt) {
            int y = e[i].to, val = e[i].val;
            if (dis[x] + e[i].val == dis[e[i].to])
                v[e[i].to]++;//y 是 e[i].to 的一个最短路前驱
        }
    }
    while (hd <= tl) {
        int x = top[hd++];
        dep[x] = dep[f[x][0]] + 1;
        for (int i = 1; i <= M; ++i)
            f[x][i] = f[f[x][i-1]][i-1];
        for (int i = head[x]; i; i = e[i].nxt) {
            int y = e[i].to;
            if (dis[x] + e[i].val != dis[y]) continue;//只走最短路边
            v[y]--;//少一个前驱没被处理
            if (!f[y][0]) f[y][0] = x;//第一个前驱，直接设为父
            else f[y][0] = lca(f[y][0], x);//多个前驱取 LCA
            if (!v[y]) top[++tl] = y;//所有前驱处理完，入队
        }
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int m, sz[N];
signed main() {
    fast;
    n = rd(), m = rd(), s = rd();
    for (int i = 1, u, v, w; i <= m; ++i) {
        u = rd(), v = rd(), w = rd();
        add(u, v, w), add(v, u, w);
    }
    dijkstra(); build();
    int ans = 0;
    for (int i = tl; i > 1; --i) {
        sz[top[i]]++, sz[f[top[i]][0]] += sz[top[i]];
        ans = max(ans, sz[top[i]]);
    }
    cout << ans;
    return 0;
}
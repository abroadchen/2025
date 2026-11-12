//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
链式前向星存图，add(u,v,w) 加一条容量为 w 的正向边 + 一条容量 0 的反向边（经典成对加边，i^1 取反向边）
标准的 Dinic 最大流：

bfs() 给每个点赋 dep 层次，从源 s 到汇 t；
dfs(u,flow) 沿 dep[v]=dep[u]+1 且剩余容量>0 的边走，返回可推流量，val[i]^=... 更新正向/反向边（val[i^1] += res 是实现反向边回退的关键）。
用 if (!tot) dep[u]=0 做当前弧/距离标记优化（剪枝，避免重复尝试死点）。
s = n+m+1, t = n+m+2：源点、汇点
n = 顶点数; m = 边数; k = 阈值
每一条边是一个节点，连接源点；这条边只能被分配到它的两个端点之一（即流向端点方向的容量都为1）
若 deg[i] > 2k 直接判无解（因为每个颜色在顶点 i 上最多出现 1 次，若能分到 2k…… 实际上是 2k，超过就没戏）。
now = max(0, (deg[i]-k)*2)：这是额外要求该顶点必须"多流出"的流量。为什么？结合目的：我们要把图的边染成颜色，使每个顶点上同一颜色至多出现…… 让我按常规题解读，这是著名的 "最小 k 边染色/六度流" kind 问题，其中 (deg-k)*2 表示需要从该顶点流走的"多余度数"。
总之：总需求 res = Σ now
若最大流量 = 总需求 res，说明存在可行解；否则输出全 0。
val 是剩余容量。由于初始边容量为1，流量经过某条边后其 val 变 0——剩余容量为0 说明该边被"选中/Oriented"到对应端点。这几行是在找出每条边最终被分配到哪个顶点（把边 i 放进它被分配的端点的 G[顶点] 列表里）。
这里 i*6-2、i*6 是在算编号偏移：因为每条边 p 在链式前向星里有 6 条有向弧（源→边 正反2 条、边→x 正反2 条、边→y 正反2 条），通过索引换算读取相应边的剩余容量。这个 6 是硬编码的索引算术，取决于 add 的调用顺序
每个顶点 i 的已分配边列表 G[i]，每两条边一组（j 和 j+1）给同一种颜色 → 这样同一个顶点上，每种颜色最多出现 1 次（而不是 2 次以上），达到"每个顶点每种颜色至多出现一次/最少"的效果。
剩下的未成对的边，单独开新颜色。
最后输出每条边的颜色编号
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 1e4+9, M = 1e6+9, inf = 1e18;

int to[M<<1], nxt[M<<1], head[N], cnt(1), val[M<<1];
inline void add(int u, int v, int w) {
    to[++cnt] = v; val[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
    to[++cnt] = u; val[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}

int s, t, dep[N], f, e, q[N];
inline bool bfs() {
    rep(i,t) dep[i] = 0; f = 0, e = 1; q[1] = s; dep[s] = 1;
    while (f < e) {
        f++;
        int u = q[f];
        for (int i = head[u]; i; i = nxt[i]) {
            if (!dep[to[i]] && val[i]) {
                q[++e] = to[i];
                dep[to[i]] = dep[u] + 1;
            }
        }
    }
    if (dep[t]) return 1;
    return 0;
}
inline int dfs(int u, int flow) {
    int tot = 0;
    if (u == t) return flow;
    for (int i = head[u]; i && flow; i = nxt[i]) {
        if (dep[to[i]] == dep[u] + 1 && val[i]) {
            int res = dfs(to[i], min(flow, val[i]));
            val[i] -= res; val[i^1] += res; flow -= res;
            tot += res;
        }
    }
    if (!tot) dep[u] = 0;
    return tot;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, k, deg[N], x[M], y[M], ans, col[N];
vector<int> G[N];
void solve() {
    memset(head, 0, sizeof(head)); cnt = 1; ans = 0;
    n = rd(), m = rd(), k = rd(); s = n+m+1, t = n+m+2;
    rep(i,n) deg[i] = 0, G[i].clear();
    rep(i,m) {
        x[i] = rd(), y[i] = rd(); deg[x[i]]++, deg[y[i]]++;//统计每个顶点度数
        //源→每条边，容量1 边→它的端点 x，容量1  边→它的端点 y，容量1
        add(s,i,1); add(i,m+x[i],1); add(i,m+y[i],1);
    }
    int res = 0;
    rep(i,n) {
        if (deg[i] > k*2) {
            rep(j,m) cout << "0 ";
            cout << '\n';
            return;
        }
        int now = max(0ll, (deg[i]-k)*2);
        add(m+i, t, now);
        res += now;
    }
    while (bfs()) ans += dfs(s, inf);//跑满最大流
    if (res != ans) {//流没跑满 → 无可行的染色
        rep(i,m) cout << "0 ";
        cout << '\n';
        return;
    }
    rep(i,m) {
        if (val[i*6-2] == 0) G[to[i*6-2]-m].push_back(i);
        else if (val[i*6] == 0) G[to[i*6]-m].push_back(i);
    }
    int cc = 0;
    rep(i,m) col[i] = 0;
    rep(i,n) for (int j = 0; j < G[i].size(); j += 2)
        col[G[i][j]] = col[G[i][j+1]] = ++cc;//同顶点相邻的两条边给同一种颜色
    rep(i,m) if (!col[i]) col[i] = ++cc;//未配对的边单独给新颜色
    rep(i,m) cout << col[i] << ' ';
    cout << '\n';
}


signed main() {
    fast;
    int T = rd();
    while (T--) solve();
    return 0;
}
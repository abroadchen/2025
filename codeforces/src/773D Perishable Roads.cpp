//
// Created by Psy.C on 2026/9/9.
//
/**
N=2005：节点数上限（n ≤ 2000，因为输入只有 n-1 行下三角）。
f[N][2]：两层状态的最短路数组。f[i][0] 表示"纯普通 Dijkstra 状态"（还未发生过某关键事件）到点 i 的最短路；f[i][1] 表示"已触发某特殊策略"状态的最小值。这是分层图/两类状态的最短路。
g[u]：每个点 u 的「从 u 出发的那条关键最短边对应的……」，稍后会结合题目用途讲。
w[n][n]：带权无向完全图的邻接矩阵。
mn：所有边权中的最小值，后面会全部减去它（边权平移）。
priority_queue<pair<ll, pair<int, bool>>>：Dijkstra 优先队列。注意用的是最大堆（默认大顶堆），但存的是负的最短路值，从而等效于最小堆。
vis[N][2]：两类状态的访问标记

初始化 f 和 g 为大值。
读入 n 和完全图的边（只给上三角，镜像到 w[j][i]），同时记录全局最小边权 mn
关键步骤：所有边权减去全局最小值 mn（边权归一化）‍。这样至少一条边变为 0。
对每条权为 0 的边 (i,j)，把 f[i][1] = f[j][1] = 0：即"从状态 1（已使用那条 0 权边）出发，i 和 j 的代价为 0"
对所有「与某条 0 权边相连」的点 i（即 f[i][1]==0），用它们到其他点 j 的边权去更新 g[j] = min(g[j], w[i][j])。含义：g[j] 是"j 到『与 0 权边相邻的点』的最短距离"

初始化：所有点的状态 0 值为 0 并入队（因为这是多源 Dijkstra，目标是以每个点为起点？其实初始把每个点 f[i][0]=0 入队，是标准多源最短路把起点们统一压入）。
每次弹出 (u, st)，st=0/1 表示当前所处状态层。
若已访问该 (u,st) 则跳过。
状态 0 → 状态 1 的转移（!st）：f[v][1] = min(f[u][0] + w[u][v] + min(w[u][v], g[u]), f[v][1])。即从 u（状态0）走到 v 时，额外加上一段 min(w[u][v], g[u]) 作为"进入关键策略"的代价。g[u] 是上面算出的「从 u 到 0-权边集的最短距离」。这一步是：当从状态0（还没抓住那条 0 权边）走到 v 时，需要在某处补一次那条 0 权边（至少需支付 min(w[u][v], g[u])）。
状态 1 → 状态 1 的转移（st）：f[v][1] = min(f[u][1] + w[u][v], f[v][1])。一旦进入状态 1（已获优惠），就只需走普通边权。
转移成功就入队，值为负（因为最大堆）。
if (u == v || vis[v][1]) continue;：跳过自环和已确定状态1的点。
这段是在做双状态 Dijkstra（0-1/分层 BFS 的加权版）‍，从"未用 0 权边"状态 0 进入"已用 0 权边"状态 1
对每个点 i，计算答案 c = min_j( min(f[i][1], f[i][0]+g[i]) )（这里内层 j 其实没有用 i 的邻居区分，直接对全部 j 取 min，等价于取全局最优值）。
最终输出 c + mn*(n-1)：因为前面把所有边权都减去了 mn，整体结果要加回 mn*(n-1)（n-1 条边各补回 mn
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e3+5, inf = 1e9;
constexpr ll INF = 1e18;
ll f[N][2];
int g[N], n, w[N][N], mn=inf;
priority_queue<pair<ll, pair<int, bool>>> q;
bool vis[N][2];
int main() {
    fast;
    memset(f, 127, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    cin >> n;
    for (int i = 1; i < n; ++i)
        for (int j = i+1; j <= n; ++j)
            cin >> w[i][j], w[j][i] = w[i][j], mn = min(mn, w[i][j]);
    for (int i = 1; i < n; ++i)
        for (int j = i+1; j <= n; ++j) {
            w[i][j] -= mn; w[j][i] -= mn;
            if (!w[i][j]) f[i][1] = f[j][1] = 0;
        }
    for (int i = 1; i <= n; ++i) if (!f[i][1])
        for (int j = 1; j <= n; ++j) g[j] = min(g[j], w[i][j]);
    for (int i = 1; i <= n; ++i) f[i][0] = 0, q.push({0, {i, 0}});
    while (!q.empty()) {
        int u = q.top().second.first, st = q.top().second.second; q.pop();
        if (vis[u][st]) continue;
        vis[u][st] = 1;
        for (int v = 1; v <= n; ++v) {
            if (u == v || vis[v][1]) continue;
            bool flag = false;
            if (!st && f[u][0] + w[u][v] + min(w[u][v], g[u]) < f[v][1]) {
                f[v][1] = f[u][0] + w[u][v] + min(w[u][v], g[u]);
                flag = true;
            } else if (st && f[u][1] + w[u][v] < f[v][1]) {
                f[v][1] = f[u][1] + w[u][v];
                flag = true;
            }
            if (flag) q.push({-f[v][1], {v, 1}});
        }
    }
    for (int i = 1; i <= n; ++i) {
        ll c = INF;
        for (int j = 1; j <= n; ++j) c = min(c, min(f[i][1], f[i][0]+g[i]));
        cout << c + 1ll*mn*(n-1) << '\n';
    }
    return 0;
}
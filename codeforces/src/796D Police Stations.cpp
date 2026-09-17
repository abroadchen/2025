//
// Created by Psy.C on 2026/9/17.
//
/**
对队列里的每个点 fst，遍历它的邻居 v。
若 vis[v]==0（未访问），给它标上来源点 fst 所属的区域编号 snd（注意这里把 fst 的所属当 snd 正确，因为 fst 入队时 vis[fst]=snd）。
入队。这就是标准多源 BFS：所有特殊点同时扩散，每个普通点被遇到的第一个源"吸收"，获得它所属区域编号
n 点数，k 特殊点数，d 距离限制
读入 k 个特殊点的编号 x。
若该点还没被分配区域（!vis[x]），给它分配新的编号 ++idx（不同特殊点不同编号）。
入队 (x, vis[x])。
意义：每个特殊点是各自区域的一个源。若有重复的特殊点（同编号），只分配一次、计算一次
读 n-1 条边，建双向邻接表，并把第 i 条边两端存进 p[i]（后续判断用
执行多源 BFS，给所有点标上所属区域编号
遍历每条边 i：若边的两端点所属区域编号不同（vis[u] != vis[v]），说明这条边是两个不同区域的边界，可以删，记录边编号
输出可删边数，以及这些边的编号
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e6+7;
queue<ii> q;//BFS 队列，存 (节点, 所属区域编号)
vector<int> g[N];//邻接表
int vis[N];//vis[v] = v 所属的区域编号（0=未访问） 既是"是否访问"又是"区域归属编号"
void bfs() {
    while (!q.empty()) {
        auto [fst, snd] = q.front(); q.pop();
        for (int v : g[fst]) {
            if (!vis[v]) {
                vis[v] = snd;
                q.emplace(v, vis[v]);
            }
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

ii p[N];
int main() {
    fast;
    int n = rd(), k = rd(), d = rd();
    for (int i = 1, x, idx = 0; i <= k; ++i) {
        x = rd();
        if (!vis[x]) vis[x] = ++idx;
        q.emplace(x, vis[x]);
    }
    for (int i = 1, u, v; i < n; ++i) {
        u = rd(), v = rd();
        g[u].push_back(v); g[v].push_back(u);
        p[i] = {u, v};
    }
    bfs();
    vector<int> v;
    for (int i = 1; i < n; ++i)
        if (vis[p[i].first] != vis[p[i].second])
            v.push_back(i);
    cout << v.size() << '\n';
    for (int t : v) cout << t << ' ';
    return 0;
}
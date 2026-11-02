//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
以节点 1 为根 DFS，记录每个节点的父节点 fa 和深度 dep
建树，DFS。
把深度 > 3 的节点（深到"必须要被选点/被覆盖"的点）按深度降序放进大顶堆 q
从最深、最深的深度>3的点开始贪心（大顶堆保证每次取最深）。
每次取一个未被覆盖的最深节点 u，选择它的父节点 fa[u] 作为"灯位"（选父节点能覆盖两层：父节点、父节点的所有邻居，距离≤2）。
把这盏灯及其所有邻居标记为 vis（即已满足",可被 ≤2 距离覆盖"）。
累加选择点数量 res，最终输出最少选择点数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int,int>
using namespace std;

constexpr int N = 1e6+10, mod = 998244353;

int fa[N], dep[N];
vector<int> g[N];
void dfs(int u, int f) {
    fa[u] = f;
    for (int v : g[u]) if (v != f) {
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int n;
priority_queue<ii> q;
bool vis[N];
void solve() {
    cin >> n;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    dep[1] = 1; dfs(1, -1);
    for (int i = 1; i <= n; ++i)
        if (dep[i] > 3) q.emplace(dep[i], i);
    int res = 0;
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        u = fa[u]; vis[u] = true;
        for (int v : g[u]) vis[v] = true;
        ++res;
    }
    cout << res;
}


int main() {
    fast;
    int T = 1;
    while (T--) solve();
    return 0;
}
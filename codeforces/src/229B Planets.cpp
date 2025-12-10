//
// Created by Psy.C on 2025/12/10.
//Dijkstra算法：O((V+E)logV)
//每个节点的等待检查：取决于禁止时间点的密度

#include <iostream>
#include <set>
#include <vector>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
#define ii pair<int,int>//目标节点, 边权重
using namespace std;

constexpr ll inf = 1e16;

int main() {
    fast;
    int n, m; cin >> n >> m;
    vector<ii> g[N];//从节点i出发的所有边
    for (int i = 0, u, v, c; i < m; ++i) {
        cin >> u >> v >> c;
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }
    set<int> t[N];//每个节点的禁止时间
    for (int i = 1, k, x; i < n + 1; ++i) {
        cin >> k;//节点i上有k个禁止时间
        while (k--) { cin >> x; t[i].insert(x); }
    }
    vector<ll> d(N, inf);//从起点1到节点i的最短距离
    priority_queue<ii, vector<ii>, greater<>> q;//小顶堆(距离小的优先)
    q.emplace(0,1); d[1] = 0; //(距离, 节点)对
    while (!q.empty()) {
        const int u = q.top().second; q.pop();
        int dist = static_cast<int>(d[u]);//初始化为到达节点u的时间
        while (t[u].count(dist)) dist++;//如果dist在节点u的禁止时间集合中，就需要等待
        for (const auto x : g[u]) {
            int v = x.first;
            const int w = x.second;
            if (dist + w < d[v]) {//通过u到达v的时间(dist+w)小于当前记录的最短距离d[v]
                d[v] = dist + w;
                q.emplace(d[v], v);
            }
        }
    }
    if (d[n] == inf) cout << -1 << '\n';
    else cout << d[n] << '\n';//到达终点的最短时间
    return 0;
}
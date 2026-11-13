//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
因为堆是按距离从小到大弹出的，所以 Dijkstra 弹出的顺序就是距离源点由近到远的顺序，这保证了最短路径树的正确性。
in[u] 记录 u 那条最短路径的入边编号，弹出 u 时把它加入答案。
while 条件含 ans.size() < k，即最多只输出前 k 条边，提前终止循环节省时间。
ans[0] 对应的源点（1号）in[1] 为 -1，所以不会入答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define ll long long
#define pll pair<ll, ll>
using namespace std;

constexpr int N = 3e5+5;
constexpr ll inf = 1e16;

vector<pair<int,pll>> g[N];//(邻接点, (边权, 边编号))
vector d(N,inf);//d[i]：从 1 到 i 的最短距离
bool vis[N];//vis[i]：i 是否已确定最短路径
vector in(N,-1);//in[i]：使 i 最短路径变短的那条边的编号
void solve() {
    int n, m, k; cin >> n >> m >> k;
    rep(i,m) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v,{w,i}});
        g[v].push_back({u,{w,i}});
    }
    priority_queue<pll,vector<pll>,greater<>> q;
    q.emplace(0,1); d[1] = 0;
    vector<int> ans;
    while (!q.empty() && ans.size() < k) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        if (in[u] != -1) ans.push_back(in[u]);//把使 u 变短的边加入答案
        vis[u] = 1;
        for (auto p : g[u]) {//松弛所有邻居
            int v = p.first, w = p.second.first, pos = p.second.second;
            if (d[u] + w < d[v]) {//找到更短路
                d[v] = d[u] + w;
                q.emplace(d[v], v);
                in[v] = pos;//记录这条松弛边
            }
        }
    }
    cout << ans.size() << '\n';
    for (auto it : ans) cout << it << ' ';
}


int main() {
    fast;
    solve();
    return 0;
}
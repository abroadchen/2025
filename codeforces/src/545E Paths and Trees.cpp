//
// Created by Psy.C on 2026/3/7.
//
/**
to（目标节点）、w（权重）、nxt（下一条边）、id（边的编号）
pre[N]：记录最短路径上的前驱边ID
vis[N]：记录节点是否在队列中
val[N]：记录边的权重值
dis[N]：记录最短距离
q：SPFA算法使用的队列

从队列取出节点，更新其邻居的距离
如果找到更短路径：更新距离和前驱边
如果找到相同距离但更小权重的边：更新前驱边

对于每个节点，如果它有前驱边，将其权重加到sum中
输出选择的边的ID
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+5;
constexpr ll inf = 1e16;

struct node { int to, w, nxt, id; } e[N<<1];

int cnt, head[N];
void add(int u, int v, int w, int id) {
    e[cnt] = {v, w, head[u], id}, head[u] = cnt++;
}

int pre[N], vis[N], val[N];
ll dis[N];
queue<int> q;
void spfa(int s) {
    for (ll& x : dis) x = inf;
    q.push(s); dis[s] = 0, vis[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            if (dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                pre[v] = e[i].id;
                if (!vis[v]) { vis[v] = 1; q.push(v); }
            }
            else if (dis[v] == dis[u] + e[i].w) {
                if (e[i].w < val[pre[v]]) {
                    pre[v] = e[i].id;
                    if (!vis[v]) { vis[v] = 1; q.push(v); }
                }
            }
        }
    }
}

int n, m, s;
int main() {
    fast;
    cin >> n >> m;
    memset(head, -1, sizeof head);
    for (int i = 1, u, v, w; i <= m; ++i) {
        cin >> u >> v >> w;
        add(u, v, w, i); add(v, u, w, i);
        val[i] = w;
    }
    cin >> s; spfa(s);
    ll sum = 0;
    for (int i = 1; i <= n; ++i)
        if (pre[i]) sum += val[pre[i]];
    cout << sum << '\n';
    for (int i = 1; i <= n; ++i)
        if (pre[i]) cout << pre[i] << ' ';
    cout << '\n';
    return 0;
}
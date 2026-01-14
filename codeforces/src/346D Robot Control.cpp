//
// Created by Psy.C on 2026/1/13.
//
/**
 * g[N]：邻接表存储图结构
 *deg[N]：节点入度数组
 *s, t：起点和终点
 *dp[N]：距离数组
 *bitset<N> vis：访问标记位集
 *
 *从终点开始BFS，距离为0
 *如果到达起点，返回
 *
 *O(n + m)，其中n是节点数，m是边数
 *
*当 dp[v] 被初始化为 -1 时：
dp[v] = -1（二进制全为1）
~dp[v] = ~(-1) = ~(全1) = 0（二进制全为0）
!~dp[v] = !0 = true
当 dp[v] 是有效距离值（非-1）时：
dp[v] ≠ -1
~dp[v] ≠ 0（通常是非零值）
!~dp[v] = !(非零值) = false
 *
 *
 *
 *
 */
#include <iostream>
#include <vector>
#include <deque>
#include <bitset>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1001000
using namespace std;

vector<int> g[N];
int deg[N], s, t, dp[N];
bitset<N> vis;

void bfs() {
    memset(dp, -1, sizeof(dp));
    deque<int> q; q.push_front(t); dp[t] = 0;
    while (!q.empty()) {
        const int u = q.front(); q.pop_front();
        if (u == s) return;
        if (vis[u]) continue; vis[u] = true;
        for (int v : g[u]) if (!--deg[v]) {//v的入度变为0
            //未访问过或者找到了更优路径
            if (!~dp[v] || dp[u] < dp[v]) dp[v] = dp[u], q.push_front(v);//0边权，加到队首
        } else if (!~dp[v]) {
            dp[v] = dp[u] + 1; q.push_back(v);//1边权，加到队尾
        }
    }
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        g[v].push_back(u); ++deg[u];//构建反向图（从v到u）
    }
    cin >> s >> t; bfs();
    cout << dp[s] << '\n';
    return 0;
}
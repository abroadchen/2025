//
// Created by Psy.C on 2025/12/6.
//
/*
 *
*N = 105：最大节点数
inf = 0x3f3f3f：无穷大值
g[N]：邻接表表示图
dis[N]：存储距离
dp[N]：存储最短路径数量
 *
*初始化所有距离为无穷大，路径数为0
起点距离设为0，路径数设为1
对于每个节点u的邻居v：
如果发现更短路径：更新距离和路径数
如果找到同样长度的最短路径：累加路径数
 *
*len：从1到n的最短距离
tot：从1到n的最短路径总数
 *
*对于每个中间节点i（2到n-1）：
从节点i运行BFS
检查是否满足：从1到i的最短距离 + 从i到n的最短距离 = 原来的最短距离
如果满足，计算经过节点i的概率并更新最大值
 */
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 105, inf = 0x3f3f3f;
int n, m;
vector<int> g[N];
ll dis[N], dp[N];

void bfs(const int s) {
    for (int i = 1; i <= n; ++i) { dis[i] = inf; dp[i] = 0; }
    dis[s] = 0, dp[s] = 1;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        const int u = q.front(); q.pop();
        for (int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                dp[v] = dp[u];
                q.push(v);
            } else if (dis[v] == dis[u] + 1) {
                dp[v] += dp[u];
            }
        }
    }
}

int main() {
    fast;
    cin >> n >> m;
    int u, v;
    while (m--) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bfs(1);
    const ll len = dis[n], tot = dp[n];
    double ans = 1.;
    for (int i = 2; i <= n - 1; ++i) {
        bfs(i);
        if (dis[1] + dis[n] == len)
            ans = max(ans,
                (2.*static_cast<double>(dp[1]*dp[n]))/(1.*
                    static_cast<double>(tot)));
    }
    cout << fixed << setprecision(12) << ans << '\n';
    return 0;
}
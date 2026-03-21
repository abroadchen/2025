//
// Created by Psy.C on 2026/3/21.
//
/**
vis[N]: 访问标记数组
d[N]: 距离数组
n: 节点数
g[N][N]: 邻接矩阵，存储边权重（0或1）
k: 目标边权重（0或1）

时间复杂度
建图：O(m)
BFS：O(n²)，因为使用邻接矩阵
总体：O(n²)
空间复杂度
O(n²)，主要是邻接矩阵的空间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 405;

int vis[N], d[N], n, g[N][N], k;
int bfs(int u) {
    queue<int> q; q.push(u);
    vis[u] = 1; d[u] = 0;//标记起点，距离为0
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int i = 1; i <= n; ++i) {
            int w = g[v][i];//获取边(v,i)的权重
            if (!vis[i] && w == k) {
                vis[i] = 1;
                q.push(i);
                d[i] = d[v] + 1;//更新距离
            }
        }
    }
    return d[n];//返回到终点的距离
}

int m;
int main() {
    fast;
    cin >> n >> m;//节点数和边数
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        g[a][b] = 1; g[b][a] = 1;//建立无向边（权重为1）
    }
    //如果起点到终点有边(k=1)，则寻找权重为0的路径；否则(k=0)寻找权重为1的路径
    k = g[1][n] ? 0 : 1;
    int ans = bfs(1);
    if (vis[n]) cout << ans;//如果能到达终点，输出距离
    else cout << "-1\n";
    return 0;
}
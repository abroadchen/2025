//
// Created by Psy.C on 2025/11/19.
//
/*
*执行叶子节点剥离算法：
当队列非空时，取出队首节点u
遍历u的所有邻居节点v
将v的度数减1（相当于删除节点u）
如果v的度数变为1，则将v加入队列
这个过程会不断删除叶子节点，直到只剩环或核心结构
 *
*遍历所有节点，找到度数大于等于2的节点（核心节点/环上的节点）
将这些节点的距离设为0，标记为已访问
将这些节点加入队列，作为BFS的起始点
 *
*执行广度优先搜索（BFS）：
当队列非空时，取出队首节点u
遍历u的所有邻居节点v
如果v已被访问则跳过
如果发现更短路径（dis[v] > dis[u] + 1），则更新距离并加入队列
 *输出每个节点到核心结构的最短距离
 *
 *
 */
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;
ll n;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n;
    vector<ll> d(n + 1, 0);
    vector<vector<ll>> g(n + 1);
    for (ll i = 0, u, v; i < n; ++i) {
        cin>>u>>v;
        g[u].push_back(v); g[v].push_back(u);
        d[u]++, d[v]++;//增加两个节点的度数
    }
    queue<ll> q;//将度数为1的节点（叶子节点）加入队列
    for (ll i = 1; i <= n; ++i) if (d[i] == 1) q.push(i);
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (auto v : g[u]) {
            d[v]--;
            if (d[v] == 1) q.push(v);
        }
    }
    vector<ll> dis(n + 1, 1e9), vis(n + 1, 0);
    for (ll i = 1; i <= n; ++i) if (d[i] >= 2) {
        dis[i] = 0;
        vis[i] = 1;
        q.push(i);
    }
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (auto v : g[u]) {
            if (vis[v]) continue;
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    for (ll i = 1; i <= n; ++i) cout << dis[i] << " ";
    return 0;
}
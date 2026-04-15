//
// Created by Psy.C on 2026/4/15.
//
/**
vis：访问标记数组，记录DFS过程中访问过的节点
num：每个节点的权值数组
ans：统计满足条件的节点数量
g：邻接表，存储树的边信息，每条边包含目标节点和权重

参数u：当前访问的节点
参数sum：从根节点到当前节点路径上的累积和
核心逻辑：
标记当前节点为已访问
如果路径和sum不超过当前节点的限制值num[u]，则计数器ans加1
否则直接返回（剪枝）
遍历当前节点的所有邻居，继续DFS搜索
新的路径和为max(0, sum+边权重)，确保不小于0

输入处理：读入n个节点和它们的权值
建图：构建无向树，读入n-1条边
DFS遍历：从节点1开始，以初始路径和为0进行深度优先搜索
结果计算：输出无法到达的节点数（总节点数减去可达节点数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define il pair<int, ll>
using namespace std;
constexpr int N = 1e5+5;
bool vis[N];
ll num[N];
int ans;
vector<il> g[N];
void dfs(int u, ll sum) {
    vis[u] = true;
    if (sum <= num[u]) ans++; else return;
    for (auto &[fst, snd] : g[u]) {
        if (vis[fst]) continue;
        dfs(fst, max(0ll, sum+snd));
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> num[i];
    for (int i = 1, v; i <= n-1; ++i) {
        ll w; cin >> v >> w;
        g[v].emplace_back(i+1, w);
        g[i+1].emplace_back(v, w);
    }
    dfs(1, 0ll);
    cout << n - ans << '\n';
    return 0;
}
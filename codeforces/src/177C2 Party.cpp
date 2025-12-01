//
// Created by Psy.C on 2025/11/30.
//
/*
*g: 图的邻接表表示
vis: 访问标记数组，记录节点属于哪个DFS调用
f: 标记数组，标记某些特殊节点
root: 当前访问的节点
idx: 当前DFS调用的索引标识
ok: 引用布尔值，标记当前组件是否有效
 *
 *如果当前节点已被标记为特殊节点，则将有效性标记设为false
 *标记当前节点属于第idx次DFS调用
 *初始化计数器为1（包括当前节点）
 *遍历当前节点的所有邻居（使用范围for循环）
*如果边的类型为false（特殊边）且邻居节点不属于当前DFS调用
则将该邻居节点标记为特殊节点
*如果边的类型为false（特殊边）且邻居节点属于当前DFS调用
说明在同一组件内存在特殊边，将有效性标记设为false
*如果边的类型为true（普通边）且邻居节点未被访问
递归访问该邻居节点，并将返回的节点数加到计数器中
 *
 *读取节点数n和第一类边的数量k
 *循环读取k条第一类边（普通边）
 *读取边的两个端点，并转换为0-based索引
 *在邻接表中添加双向边，标记为类型1（普通边）
 *
 *读取第二类边的数量m
 *循环读取m条第二类边（特殊边）
 *读取边的两个端点，并转换为0-based索引
 *在邻接表中添加双向边，标记为类型0（特殊边）
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define vi vector<int>
#define vb vector<bool>
#define vvp vector<vector<pair<int, bool>>>
using namespace std;

int dfs(vvp& g, vi& vis, vb& f, const int root, const int idx, bool& ok) {
    if (f[root]) ok = false;
    vis[root] = idx;
    int cnt = 1;
    for (const auto x : g[root]) {
        if (!x.second && vis[x.first] != idx) f[x.first] = true;
        else if (!x.second && vis[x.first] == idx) ok = false;
        else if (x.second && vis[x.first] == -1) cnt += dfs(g, vis, f, x.first, idx, ok);
    }
    return cnt;//返回连通分量的节点数
}

int main() {
    fast;
    int n, m, k; cin >> n >> k;
    vvp g(n);
    for (int i = 0, u, v; i < k; ++i) {
        cin >> u >> v; --u; --v;
        g[u].emplace_back(v,1); g[v].emplace_back(u,1);
    }
    cin >> m;
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v; --u; --v;
        g[u].emplace_back(v,0); g[v].emplace_back(u,0);
    }
    int res = 0;
    vi vis(n, -1);
    for (int i = 0; i < n; ++i) {
        if (vis[i] == -1) {
            vb f(n, false); bool ok = true;//特殊节点标记数组 有效性标记ok
            int t = dfs(g, vis, f, i, i, ok);//连通分量的大小t 同时更新有效性标记ok
            if (ok) res = max(res, t);//如果当前连通分量有效，则更新最大结果
        }
    }
    cout << res << '\n';
    return 0;
}
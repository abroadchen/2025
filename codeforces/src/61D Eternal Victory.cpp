//
// Created by Psy.C on 2025/10/28.
//
/*
 *定义边结构体Edge，包含目标节点to和权重wt
 *定义图的邻接表表示，g[i]存储从节点i出发的所有边
 *定义访问标记数组，用于DFS过程中标记已访问的节点
 *md(最大距离)初始化为0，ans(总权重)初始化为0
 *n(节点数)、u(起点)、v(终点)、wt(权重)
 *
 *定义深度优先搜索函数，参数为当前节点n和当前距离d
 *标记当前节点n为已访问
 *更新最大距离，保留从起始节点到当前节点的最大距离
*遍历当前节点n的所有邻接边：
使用结构化绑定获取目标节点v和权重wt
如果目标节点未被访问，则递归调用DFS，距离更新为d + wt
 *
 *重新分配图的大小为n+1，索引0不使用，节点编号从1到n
 *重新分配访问数组大小并初始化为false
 *
 *计算遍历整棵树并回到起点的最短路径长度，减去最远节点的距离
 */
#include <ios>
#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;
struct Edge { int to, wt; };
vector<vector<Edge>> g;
vector<bool> visited;
ll md(0), ans(0);
int n, u, v, wt;

void dfs(int n, ll d) {
    visited[n] = true;
    md = max(md, d);
    for (auto [v, wt] : g[n]) { if (!visited[v]) dfs(v, d + wt); }
}

void solve() {
    cin >> n;
    g.assign(n + 1,{});
    visited.assign(n + 1, false);
    for (int i = 1; i < n; ++i) {
        cin >> u >> v >> wt;
        g[u].push_back({v, wt});
        g[v].push_back({u, wt});
        ans += wt;
    }
    dfs(1, 0);
    cout << 2 * ans - md << "\n";
}


int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
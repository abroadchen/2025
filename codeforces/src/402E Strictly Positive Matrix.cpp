//
// Created by Psy.C on 2026/1/31.
//
/**
* dfn[N]：节点的时间戳（DFS序）
low[N]：节点能到达的最小时间戳
tim：当前时间戳
scc：强连通分量数量
id[N]：节点所属的强连通分量编号
*stk：Tarjan算法使用的栈
vis[N]：节点是否在栈中的标记
g[N]：邻接表表示的图
 *
*初始化节点u的时间戳和low值
将u压入栈，标记为在栈中
*遍历u的所有邻接点v
如果v未被访问过：递归调用tarjan，更新low[u]
如果v在栈中：更新low[u]
*如果dfn[u] == low[u]，说明找到了一个强连通分量
弹出栈中节点直到u，将它们标记为同一个强连通分量
 */
#include <iostream>
#include <vector>
#include <stack>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2020
using namespace std;

int dfn[N], low[N], tim, scc, id[N];
stack<int> stk;
bool vis[N];
vector<int> g[N];
void tarjan(const int u) {
    dfn[u] = low[u] = ++tim;
    stk.push(u); vis[u] = true;
    for (const auto v : g[u]) {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        scc++;
        int v;
        do {
            v = stk.top(); stk.pop(); vis[v] = false;
            id[v] = scc;
        } while (v != u);
    }
}


int main() {
    fast;
    int n; cin >> n;//图的节点数
    for (int i = 1; i <= n; ++i) for (int j = 1, a; j <= n; ++j) {
        cin >> a;
        if (a && i != j) g[i].push_back(j);
    }
    tarjan(1);
    for (int i = 1; i <= n; ++i) if (id[i] != 1) {//不在第一个强连通分量中
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    return 0;
}
//
// Created by Psy.C on 2026/9/23.
//
/**
若 x 达到 1（含精度容差 eps=1e-8），则 x 减 1（归 0），并且交换 u, v（改变该边的"方向"标记）。
输出 1 边号 u v x：1 表示某类操作，u v 是端点，x 是 [0,1) 内的实数
从根 u 出发，对每条非父边 (u,v)：
x += 2/g[u].size()：在模 2 的圆上均匀分配角度（把"圆"按度数切分）。
x 对 2 取模。
输出该边 (u,v) 及当前 x。
递归进入子树 dfs(v, u, x+1)（进入时 x 加 1，作为子树的偏移）。
这是经典的"树的边着色 / 环形排序"欧拉回路近似构造：保证每条边被访问两次（往返）时在圆上形成一个闭合的「回路区间」
读入树（存邻接表，带边号）。
输出边数 n-1（即答案的操作数）。
从节点 1、父节点 -1、初始 x=0 开始 DFS
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-8
#define ii pair<int, int>
using namespace std;
constexpr int N = 105;

inline void out(int id, int u, int v, double x) {
    if (x + eps >= 1) { x -= 1; swap(u, v); }
    printf("1 %d %d %d %.12lf\n", id, u, v, x);
}

vector<ii> g[N];
void dfs(int u, int fa, double x) {
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i].first;
        if (v == fa) continue;
        x += 2./g[u].size();
        if (x + eps >= 2) x -= 2;
        out(g[u][i].second, u, v, x);
        dfs(v, u, x+1);
    }
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, u, v; i <= n-1; ++i) {
        cin >> u >> v;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }
    cout << n-1 << '\n';
    dfs(1, -1, 0);
    return 0;
}
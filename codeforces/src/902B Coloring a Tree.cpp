//
// Created by Psy.C on 2026/10/10.
//
/**
g[] 存树的无向邻接表，cl[] 存每个点的颜色，ans 累计答案。
从根向下遍历整棵树，同时维护一个 c（从父节点传递下来的颜色）。
每走到一个节点，如果它的颜色 cl[fr] 和父节点传递来的颜色 c 不一样，就说明颜色在这里发生了"切换"，ans++，并把 c 更新成这个节点的新颜色。
这样 ans 统计的是：从根出发深度优先遍历时，颜色发生变化的次数
读入 n。
循环 i 从 1 到 n-1，读入 u，并以 v = i+1 建边——这样建出来的一定是树：节点 1..n，每步把新节点 i+1 连到读入的 u，天然无环。
再读入每个节点的颜色 cl[i]。
从节点 1、初始颜色 c=0 开始 DFS，输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 1e4+10;

bool vis[N];
int cl[N], ans;
vector<int> g[N];
void dfs(int fr, int c) {
    vis[fr] = true;
    if (cl[fr] != c) {
        ans++;
        c = cl[fr];
    }
    for (auto y : g[fr]) { if (y != fr && !vis[y]) dfs(y, c); }
}

signed main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v = i+1; cin >> u;
        g[u].push_back(v); g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) cin >> cl[i];
    dfs(1, 0);
    cout << ans;
    return 0;
}
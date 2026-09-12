//
// Created by Psy.C on 2026/9/12.
//
/**
并查集合并已连接节点，只保留生成树的边（vc 邻接表存生成树）。
冗余边跳过（x==y continue）
从 1 出发 DFS。
每次进入一个节点 push 一次，返回父节点时再 push 一次父节点，形成欧拉 DFS 序（每条边经过两次）
p = 每段最多容纳的节点数（(2*n+k-1)/k 上取整，保证总长 2n 范围内切 k 段够放）。
把欧拉序列按每 p 个切一段，存到 c[0..k-1]
每段输出长度 + 节点的序列。空段填节点 1 保证非空
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+100;

int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

vector<int> ans, vc[N];
void dfs(int o, int u) {
    ans.push_back(u);
    for (int v : vc[u]) {
        if (v == o) continue;
        dfs(u, v);
        ans.push_back(u);
    }
}

vector<int> c[N];
int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        int x = find(u), y = find(v);
        if (x == y) continue;
        fa[x] = y;
        vc[u].push_back(v); vc[v].push_back(u);
    }
    dfs(0, 1);
    int p = (2*n+k-1)/k;
    for (int i = 0; i < ans.size(); ++i)
        c[i/p].push_back(ans[i]);
    for (int i = 0; i < k; ++i) {
        if (c[i].empty()) c[i].push_back(1);//空段补一个节点
        cout << c[i].size();
        for (int v : c[i]) cout << ' ' << v;
        cout << '\n';
    }
    return 0;
}
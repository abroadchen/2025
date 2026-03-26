//
// Created by Psy.C on 2026/3/26.
//
/**
ans[N]：存储每个节点的颜色（'a', 'b', 'c'）
G[N]：邻接表存储图
vis[N]：DFS访问标记
如果节点u已被标记为'b'，返回
将节点u标记为'a'
遍历u的所有邻居，对未访问的节点递归DFS

lk[u][v] = 1：邻接矩阵标记边
G[u].push_back(v)：邻接表添加边
deg[u]++：度数统计
如果节点度数等于n-1，说明该节点与所有其他节点相连
将这样的节点标记为'b'
找到第一个不是'b'的节点，开始DFS
将连通分量中的节点标记为'a'
将未被标记的节点标记为'c'
如果两个节点颜色相同，它们之间必须有边
如果发现同色节点间没有边，标记flag=0

时间复杂度：O(n²) 空间复杂度：O(n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 505;

char ans[N];
vector<int> G[N];
int vis[N];
void dfs(int u) {
    if (ans[u] == 'b') return;
    ans[u] = 'a';
    for (int i : G[u]) {
        int v = i;
        if (!vis[v]) {
            vis[v] = 1;
            dfs(v);
        }
    }
}

int n, m, lk[N][N], deg[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        lk[u][v] = 1; lk[v][u] = 1;
        G[u].push_back(v); G[v].push_back(u);
        deg[u]++; deg[v]++;
    }
    for (int i = 1; i <= n; ++i)
        if (deg[i] == n-1) ans[i] = 'b';
    for (int i = 1; i <= n; ++i)
        if (ans[i] != 'b') { dfs(i); break; }
    for (int i = 1; i <= n; ++i)
        if (ans[i] != 'a' && ans[i] != 'b') ans[i] = 'c';
    int flag = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            if (ans[i] == ans[j]) {
                if (!lk[i][j]) flag = 0;
            }
        }
    if (flag) cout << "Yes\n" << ans+1 << '\n';
    else cout << "No\n";
    return 0;
}
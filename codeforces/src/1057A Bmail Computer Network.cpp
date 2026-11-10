//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
vis[N]：访问标记数组，记录节点是否已访问。
v：一维 vector，按 DFS 访问顺序记录节点（后续用于反向输出）。
g[N]：邻接表，g[u] 存 u 的所有邻居
标记 u 已访问，并把 u 压入 v（记录访问序）
对 i = 2..n 各读一个 x，即每条边由子节点 i 指向父节点 x，把 x 加入 g[i]。因此每个节点最多 1 条出边，图实际上是一棵有向父链/树，终点是节点 1（或 1 到 n 的路径）
从节点 n 出发做 DFS。
注意题目建的是从 i 到 x 的"父链"，也就是从子到父——所以 g[n] 存 n 的父亲，DFS(n) 会沿着父链往回走到祖先方向，v 里记录的就是这条从 n 向上回溯访问到的节点序列
逆序输出 v：把 DFS 访问序反过来打印，节点间用空格分隔
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 2e5+5;

bool vis[N];
vector<int> v, g[N];
void dfs(int u) {
    vis[u] = 1; v.push_back(u);
    rep(i,g[u].size()) if (!vis[i]) dfs(g[u][i]);
}


int n;
int main() {
    fast;
    cin >> n;
    for (int i = 2, x; i <= n; i++) {
        cin >> x; g[i].push_back(x);
    }
    dfs(n);
    for (int i = v.size()-1; i >= 0; i--) cout << v[i] << ' ';
    return 0;
}
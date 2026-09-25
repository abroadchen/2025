//
// Created by Psy.C on 2026/9/24.
//
/**
f[u][i]：倍增表，f[u][i] = u 的 2^i 级祖先。
dep[u]：u 的深度（根为 1，深度从 1 开始）。
fa[u]：u 的父节点。
v[u]：邻接表
fa 既当"当前 DFS 的父节点"传参，又存每个节点的父节点，二合一
读入 n-1 条边，第 i 条边连接 i+1 和它的父 k。
注意树是无向的（双向 push 进邻接表），但 fa[i+1]=k 显式记录了父关系。
输入给的是「节点 i+1 的父节点是 k」的形式（k < i+1，构成一棵有向根的树），所以根可为 1
f[u][0] = 父节点（倍增第 0 级）。
dep[u] = dep[fa[u]] + 1，根 dep[1] = dep[0]+1 = 1（fa[1] 为 0，初始 dep[0]=0）。
递归子节点（跳过父节点避免回环）
f[j][i] = f[j][i-1] 的 2^{i-1} 级祖先 = j 的 2^i 级祖先
升深度：把较深的 a 提升到与 b 同深度（用倍增跳）。
若提升后 a==b，则 b 就是 LCA。
一起上升：从高到低尝试，若 f[a][i] != f[b][i] 则同时跳，最后父节点即 LCA
距离 = u 到 LCA + v 到 LCA（或直接 dep[u]+dep[v]-2*dep[lca]，等价）
三人在 a、b、c 三点，选择一人待命点，另外两人从自己的点走向待命点（走最短路径）‍，两人会先在某处汇合（LCA 附近），然后共同走一段"重合路径"。题目求的是重合路径上经过的顶点数的最大值。

关键观察：两人路径的重合部分长度 = (两人各自到第三点的距离 之和 − 两人之间距离) / 2。

a1 = (dist(a,c) + dist(b,c) - dist(a,b))/2
让 c 作为待命汇合点，a 和 b 都走向 c。
a→c 与 b→c 两条路径重合部分长度 = (ac + bc − ab) / 2。
a2 = (dist(a,b) + dist(c,b) - dist(a,c))/2
b 为待命点，a、c 走向 b。
a3 = (dist(b,a) + dist(c,a) - dist(b,c))/2
a 为待命点，b、c 走向 a。
最终取三者最大，再 +1（因为长度算的是"边数"，题目问的是"顶点数"，顶点数 = 边数 + 1）。


树上任意两条从一个点到同一点（汇合点）的路径，其重合段就是两条路径的公共前缀。设 z = LCA(a,c)、y = LCA(b,c)。两者公共段 = 从 c 往上走到某个分叉点的部分。利用树上距离恒等式：

重合段边数 = (dist(a,c) + dist(b,c) - dist(a,b)) / 2
因为三条路径长度满足 dist(a,b) = dist(a,c) + dist(b,c) - 2*重合段，移项即得。这公式对三个"距离相关"的组合都成立，枚举谁是汇合点即可
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+10;

int f[N][20], dep[N], fa[N];
vector<int> v[N];
void dfs(int u) {
    f[u][0] = fa[u], dep[u] = dep[fa[u]] + 1;
    for (int i = 0; i < v[u].size(); ++i)
        if (v[u][i] != fa[u]) dfs(v[u][i]);
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    int x = a;
    for (int i = log2(dep[a]-dep[b]); i >= 0; --i)
        if ((1<<i) <= dep[a] - dep[b]) a = f[a][i];
    if (a == b) return a;
    for (int i = log2(dep[a]); i >= 0; --i)
        if (f[a][i] != f[b][i]) a = f[a][i], b = f[b][i];
    return f[a][0];
}
int dist(int u, int v) {
    int ans = lca(u, v);
    ans = dep[u] - dep[ans] + dep[v] - dep[ans];
    return ans;
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1, k; i < n; ++i) {
        cin >> k; fa[i+1] = k;
        v[k].push_back(i+1); v[i+1].push_back(k);
    }
    dfs(1);
    for (int i = 1; i < 20; ++i)
        for (int j = 1; j <= n; ++j)
            f[j][i] = f[f[j][i-1]][i-1];
    while (m--) {
        int a, b, c; cin >> a >> b >> c;
        int a1 = (dist(a, c) + dist(b, c) - dist(a, b))/2,
        a2 = (dist(a, b) + dist(c, b) - dist(a, c))/2,
        a3 = (dist(b, a) + dist(c, a) - dist(b, c))/2;
        cout << max(a1, max(a2, a3))+1 << '\n';
    }
    return 0;
}
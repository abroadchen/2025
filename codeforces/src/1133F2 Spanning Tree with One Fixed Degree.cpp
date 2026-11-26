//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
fa[i] 既当并查集父指针，又会在后面被复用为 0/1 来标记
交换保证 u ≤ v，方便判断 u==1 表示该 DFS 边与根 1 相连。
第一阶段故意先不看含 1 的边，只对 u != 1 的边做并查集合并，得到一个"去掉根 1 后其余节点的生成森林"。
cnt 统计根 1 的度（邻边数）
1 的度必须 ≥ d（否则不够连 d 条边）。
去掉 1 后形成的连通块数 ≤ d（否则即使把 d 根边都连上也连不通整棵树）。这里 cnt 是"去掉1后的祖先个数"，需 ≤ d
第一轮选边（必需的根边）： 对每条以 1 为端点的边，如果另一端 v 所属连通块还没被选过（fa[find(v)] 非 0）、
且该邻点还没被 vis 标记，就必须选这条边连接该连通块。选完后把 fa[find(v)] = 0（标记该块已被 1 连上），并置 vis[v]=1。
这样每个"非1"连通块至少连一条到 1 的边，保证整棵树连通
继续找尚未使用的、以 1 为端点的边，输出它们直到 根 1 的度恰好达到 d（cnt == d）。这一阶段可多选边把度凑到 d
重建并查集：把 vis 标记过的顶点（已直接连到 1 的邻点）gaaan 加入 1 的集合；其他顶点各自为根。
补边：按边序尝试，若 find(u)!=find(v)（不成环）且 u != 1（避免再动根边度），则合并并输出，直到凑满 n-1 条边（生成树）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+10;
struct edge { int u, v, c; } e[N];
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int n, m, d, cnt;
bool vis[N];
int main() {
    fast;
    cin >> n >> m >> d;
    rep(i,n) fa[i] = i;
    rep(i,m) {
        cin >> e[i].u >> e[i].v;
        if (e[i].u > e[i].v) swap(e[i].u, e[i].v);
        if (find(e[i].u) != find(e[i].v) && e[i].u != 1)
            fa[find(e[i].u)] = find(e[i].v);
        if (e[i].u == 1) cnt++;//统计与1相连的边数
    }
    if (cnt < d) cout << "NO\n", exit(0);
    cnt = 0;
    for (int i = 2; i <= n; i++) if (fa[i] == i) cnt++;
    if (cnt > d) cout << "NO\n", exit(0);
    cout << "YES\n";
    cnt = 0;
    rep(i,m) if (fa[find(e[i].v)] && !vis[e[i].v] && e[i].u == 1)
        cnt++, cout << "1 " << e[i].v << '\n', fa[find(e[i].v)] = 0, vis[e[i].v] = 1;

    for (int i = 1; i <= m && cnt < d; i++)
        if (e[i].u == 1 && !vis[e[i].v])
            vis[e[i].v] = 1, cout << "1 " << e[i].v << '\n', cnt++;
    rep(i,n) fa[i] = vis[i] ? 1 : i;
    rep(i,m) {
        int u = e[i].u, v = e[i].v;
        if (find(u) != find(v) && u != 1)
            fa[find(u)] = find(v), cout << u << ' ' << v << '\n', cnt++;
        if (cnt == n-1) exit(0);
    }
    return 0;
}
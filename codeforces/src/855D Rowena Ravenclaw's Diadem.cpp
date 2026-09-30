//
// Created by Psy.C on 2026/9/30.
//
/**
每个节点：f[i][0] = 父亲，s[i] = 节点值。u==-1 && v==-1 表示这个节点是树的根（无父亲），放入根列表 vt。得到一棵多叉森林
s[i] 在输入时是节点自身值，DFS 时被累加成"从根到该节点的路径和"（树上前缀和）。这是判断路径性质的依据
先判是否同一棵树（根相同，即 f[..][19] 相同，越界后都指向根自身）。
深度对齐 + 倍增上跳找 LCA。
若不在同一棵树，返回 -1
a0(x,y)：x、y 到根的路径和相等。
a1(x,y)：s[x]-s[y] == d[x]-d[y]，即从 y 到 x 的这段路径上所有"节点值"（因为 s 是前缀和，s[x]-s[y] 是 y 到 x 路径上各节点值之和；d[x]-d[y] 是节点个数；二者相等 ⟺ 该路径上每个节点值都等于 1，x≠y）——判断"路径上每个节点值为 1"之类的条件。
具体语义依赖原题（比如每个节点值 0/1，判断路径上是否全为 1 等）。代码确定的行为是：用 s 前缀和之差与深度差比较来判定路径上节点值全为 1
前提：u != v 且 a != -1（同一棵树）。
t==1：要求 a==u（u 是 v 的祖先）且 s[v]==s[u]（a0）。
t!=1（即 t==2）：要求 a0(u,a)（s[u]==s[a]）且 a1(v,a)（v 到 LCA 路径上节点值全为 1）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

int f[N][20], d[N], s[N];
vector<int> son[N];
void dfs(int o) {
    for (int i = 1; i < 20; ++i)
        f[o][i] = f[f[o][i-1]][i-1];
    for (int to : son[o])
        d[to] = d[o] + 1, s[to] += s[o], dfs(to);
}

int lca(int x, int y) {
    if (f[x][19]^f[y][19]) return -1;
    if (d[x] > d[y]) swap(x, y);
    for (int i = 19; i >= 0; --i)
        if (d[x] <= d[f[y][i]]) y = f[y][i];
    if (x == y) return x;
    for (int i = 19; i >= 0; --i)
        if (f[x][i]^f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}

bool a0(int x, int y) { return s[x] == s[y]; }
bool a1(int x, int y) {
    return s[x]-s[y] == d[x]-d[y] && x^y;
}

vector<int> vt;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, u, v; i <= n; ++i) {
        cin >> u >> v;
        if (u == -1 && v == -1) vt.push_back(i), f[i][0] = i;
        else f[i][0] = u, s[i] = v, son[u].push_back(i);
    }
    for (int rt : vt) dfs(rt);
    int q, t, u, v, a; cin >> q;
    while (q--) {
        cin >> t >> u >> v; a = lca(u, v);
        if (u^v && a != -1) {
            if (t == 1)
                cout << (a==u && a0(v, a) ? "YES" : "NO") << '\n';
            else
                cout << (a0(u, a) && a1(v, a) ? "YES" : "NO") << '\n';
        } else cout << "NO\n";
    }
    return 0;
}
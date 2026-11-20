//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
vis：访问标记。
son：i 是否为非叶子（即有没有被 DFS 访问到的孩子）。
G：邻接表。
fa：DFS 树上的父节点。
dep：深度。
x1[i]、x2[i]：对叶子 i，记录两条不在 DFS 树上的"回边"指向的祖先/节点（用于构造环）
vis[u]=1，遍历邻居：
v 未访问 → 作为树边：设 fa[v]=u, dep[v]=dep[u]+1, 标记 son[u]=1（u 有孩子），递归 dfs(v)。
当 u 是叶子（!son[u]，自己这一支到底）时：
遍历邻居 v，找已经访问过且不是父节点的点（即回边/横叉边指向的点），记入 x1[u]、x2[u]。
因为是无向图连通且 u 是叶子，通常能找到至少两条这样的"非父"回边（从而可以构造两个不同的环）；取前两个就好。
这样每个"叶子"拿到两个可作环捷径的点 x1、x2（都在它上方/祖先方向），环由"叶子 ↔ 祖先"的两条路径组合而成
输出从 u 到 v 这条树路径上的所有点（按深度从深到浅）。
先保证 v 更深，输出 v，然后不断 v = fa[v] 向上走到 u，最后输出 u。因为 DFS 树路径唯一，这就是连通 u、v 的简单路径

读入 n(m) 条边建图。
t = ceil(n/k)——路径的下界长度。
从 1 号点 DFS（dep[1]=1）
找到深度最大的点 p，即从根出发的最长树路径的终点
若最长深度 ≥ t：直接输出 PATH（根到 p 的路径），点数 = dep[p]，符合要求。任务完成
对每个前缀（k 个）‍叶子 i（!son[i]）：

环 1：i → x1[i] 的树路径，长度 L1 = dep[i]-dep[x1[i]]+1。
若 L1 % 3 != 0：直接用这个环（长度不是 3 的倍数），输出它，out(x1[i], i)。
环 2：i → x2[i]，长度 L2 = dep[i]-dep[x2[i]]+1。
若 L2 % 3 != 0：用这个环。
若两个都恰好是 3 的倍数：改用跨两个祖先的环：
先让 x1 是较浅的（dep[x1] > dep[x2] 则交换）。
输出环：i → x2 → x1 → i 的复合（长度 = dep[x2]-dep[x1]+2）。
可以证明这个长度必然不是 3 的倍数（因为 x1、x2 深度差在 3 的倍数+1 之类的情况下，+2 会打破整除）。
关键：out(x1[i], x2[i]) 输出 x2→x1 的树路径，前面手动补 i 构成环 i - x2 - ... - x1 - i。

所有叶子互不相交（DFS 树性质），各环节点集合不同，故 k 个环彼此独立，合法
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
using namespace std;

constexpr int N = 2.5e5+5, inf = 1e9;

bool vis[N], son[N];
vector<int> G[N];
int fa[N], dep[N], x1[N], x2[N];
void dfs(int u) {
    vis[u] = 1;
    for (auto v : G[u]) {
        if (vis[v]) continue;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        son[u] = 1;
        dfs(v);
    }
    if (!son[u]) for (auto v : G[u]) if (vis[v] && v != fa[u]) {
        if (x1[u] && x2[u]) break;
        if (x1[u]) x2[u] = v;
        else x1[u] = v;
    }
}
void out(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    cout << v << ' ';
    for (v = fa[v]; v != u; v = fa[v]) cout << v << ' ';
    cout << u << '\n';
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, k, t;
int main() {
    fast;
    n = rd(), m = rd(), k = rd(); t = ceil(1.0*n/k);
    for (int i = 1, u, v; i <= m; i++) {
        u = rd(), v = rd();
        G[u].push_back(v); G[v].push_back(u);
    }
    dep[1] = 1, dfs(1);
    int p = 0;
    rep(i,n) if (dep[i] > dep[p]) p = i;
    if (dep[p] >= t) {
        cout << "PATH\n";
        cout << dep[p] << '\n';
        out(1,p);
    } else {
        cout << "CYCLES\n";
        rep(i,n) if (!son[i] && k) {
            k--;
            if ((dep[i]-dep[x1[i]]+1)%3 != 0) {
                cout << dep[i]-dep[x1[i]]+1 << '\n';
                out(x1[i],i);
            } else if ((dep[i]-dep[x2[i]]+1)%3 != 0) {
                cout << dep[i]-dep[x2[i]]+1 << '\n';
                out(x2[i],i);
            } else {
                if (dep[x1[i]] > dep[x2[i]]) swap(x1[i],x2[i]);
                cout << dep[x2[i]]-dep[x1[i]]+2 << '\n';
                cout << i << ' ';
                out(x1[i],x2[i]);
            }
        }
    }
    return 0;
}
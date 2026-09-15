//
// Created by Psy.C on 2026/9/15.
//
/**
sz[u] = 以 u 为根的子树的叶子总数（叶子自身 sz=1）。
leaf = 整棵树叶子总数。
若 leaf 为奇数 → 无法平均分组 → 直接 NO
anc[u] = 节点 u 属于根 1 的哪个直接孩子子树（rt）。用于后面判断某一叶子所在的"根孩子子树"
s 是一个 bitset，代表"已经可以拼出的叶子数量集合"（背包）。
对根 1 的每个孩子子树 v：
若该子树不含 a/b/c/d 中任何一个（即它是"自由子树"），就把它的叶子数 sz[v] 作为一个可选物品：s |= s << sz[v]，更新可达的叶子总数集合。
含 a/b/c/d 的那几棵子树被单独保留，用于 check。
这里的思路：把 a,b,c,d 各"占用"了一整棵根孩子子树，剩下的自由子树的叶子数可以自由组合，看能否凑出所需的补充叶子数
leaf/2 = 每组平均……（配对理解为两两一组，总共有 leaf/2 组）。
lim = leaf/2 - 1 - sz[anc[c]]：总共需要的组数减去 1（一个组给 c 用）再减去 c 那棵根孩子子树的叶子数，得到还需要从别处凑出的叶子数。
用背包 bitset f 从 s 出发，再沿 a、b 各自的祖先链，把 a、b 所在路径上兄弟子树的叶子数作为可选物品加入背包（f |= f << sz[v]，其中 v 是 fa[a]/fa[b] 的非当前孩子）。
最后判断 f[lim]：能否用这些可选子树凑出恰好 lim 片叶子。
含义：c 那一组里，除 c 本身外还要塞进 lim 片其它叶子；能不能凑出这些叶子，取决于自由子树 + a/b 沿线兄弟子树的叶子数能否拼出 lim
需要同时满足两个方向的 check：(a,c)**这组** 能凑出来，且 (c,b,d)` 那组也能凑出来
尝试两种配对方案（c、d 与谁同组）之一可行即可
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5010;

vector<int> G[N];
int leaf, sz[N];
void dfs(int u) {
    if (G[u].empty()) { ++leaf; sz[u] = 1; }
    for (int v : G[u]) { dfs(v); sz[u] += sz[v]; }
}

int anc[N];
void dfs2(int u, int rt) {
    anc[u] = rt;
    for (int v : G[u]) dfs2(v, rt);
}

bitset<N> s;
int fa[N];
bool check(int a, int c, int b) {
    int lim = leaf/2-1-sz[anc[c]];
    if (lim < 0) return 0;
    auto f = s;
    for (; fa[a] != 1; a = fa[a])
        for (int v : G[fa[a]])
            if (v != a) f |= f<<sz[v];
    for (; fa[b] != 1; b = fa[b])
        for (int v : G[fa[b]])
            if (v != b) f |= f<<sz[v];
    return f[lim];
}

bool isok(int a, int c, int b, int d) {
    return check(a, c, b) && check(c, b, d);
}

int main() {
    fast;
    int n; cin >> n;
    int a, b, c, d; cin >> a >> b >> c >> d;
    for (int i = 2; i <= n; ++i) {
        cin >> fa[i];
        G[fa[i]].emplace_back(i);
    }
    dfs(1);
    if (leaf&1) return puts("NO"), 0;
    s[0] = 1;
    for (int v : G[1]) {
        dfs2(v, v);
        if (v != a && v != b && v != c && v != d)
            s |= s<<sz[v];
    }
    if (isok(a, c, b, d) || isok(a, d, b, c)) puts("YES"); else puts("NO");
    return 0;
}
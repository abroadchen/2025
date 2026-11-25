//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
fa[] 并查集，n*2 是因为最多可能产生 n-1 个新节点（树最多 2n 节点）。
v[u] 存节点 u 的儿子（最多 2 个）。
find 带路径压缩
初始 tot = n（前 n 个是原始点）。
每次读入两个待合并点 x,y，先找到它们所在的连通块根。
若根不同，则新建一个节点 ++tot，把 x 和 y 两个根都设为它的儿子，并把它们的并查集父指针指向 tot。
这样每次合并都"向上"建一个父节点，最终连成一棵以最后一个 tot 为根的重构树（Kruskal 重构树思想）
从根 tot 开始 DFS。
叶子节点（没有儿子的，即最初的原始点 1..n）直接输出。
内部节点（合并产生的新节点）先递归左儿子、再递归右儿子

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 3e5+5;

int n, fa[N];
void init() { rep(i,n*2) fa[i] = i; }
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

vector<int> v[N];
void dfs(int u) {
    if (v[u].empty()) { cout << u << ' '; return; }
    dfs(v[u][0]); dfs(v[u][1]);
}

int tot, x, y;
int main() {
    fast;
    cin >> n; init(); tot = n;
    rep(i,n-1) {
        cin >> x >> y; x = find(x); y = find(y);
        if (x != y) v[++tot].push_back(x), v[tot].push_back(y), fa[x] = fa[y] = tot;
    }
    dfs(tot);
    return 0;
}
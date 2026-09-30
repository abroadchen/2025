//
// Created by Psy.C on 2026/9/30.
//
/**
sz[u]：子树大小。
dep[u]：深度（根为 1）。
Fa[u]：父节点
cnt[x]：该并查集分量内含多少个树节点。
ans[x]：该分量的某些统计值（与边长/路径数相关）。
now：全局答案维护量，合并时先减去两个旧分量的贡献，把 y 并入 x（y 的统计并入 x），再加回新总贡献。
ans[x] += ... - sz[y]^2 - (n-sz[y])^2：把 y 这棵树内部及"对侧"部分的平方贡献并入 x，用于从全局总数里扣除。
这种"先减后加"是并查集动态维护和的经典写法（带撤销式增量更新）
初始化把每个节点当独立分量，ans[x] = 所有孩子子树大小的平方 + 父侧部分大小的平方。
每次询问给两个端点 x,y，通过不断把深度较大的那个点所在分量向它的父节点合并（merge(Fa[x], x)），直到两个端点汇到同一个分量——这一步实际上在"打通"两端点间的整条路径，把所有边对应的分量连通起来。
now 累加被"覆盖/连通"的统计，答案 = 总三元组数 n(n-1)(n-2) 减去 now
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e5+5;

int sz[N], dep[N], Fa[N];
vector<int> g[N];
void dfs(int u) {
    sz[u] = 1, dep[u] = dep[Fa[u]]+1;
    for (int v : g[u])
        if (v^Fa[u])
            Fa[v] = u, dfs(v), sz[u] += sz[v];
}

int fa[N];
int find(int x) {
    return fa[x]^x ? fa[x] = find(fa[x]) : x;
}

int now, cnt[N], ans[N], n;
void merge(int x, int y) {
    now -= cnt[x]*(ans[x]-n+cnt[x])+cnt[y]*(ans[y]-n+cnt[y]);
    ans[x] += ans[y]-sz[y]*sz[y]-(n-sz[y])*(n-sz[y]);
    cnt[x] += cnt[y], fa[y] = x, now += cnt[x]*(ans[x]-n+cnt[x]);
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int m;
signed main() {
    fast;
    n = read();
    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        g[x].push_back(y); g[y].push_back(x);
    }
    dfs(1); m = read();
    for (int x = 1; x <= n; ++x) {
        fa[x] = x, cnt[x] = 1;
        for (int y : g[x])
            if (y^Fa[x]) ans[x] += sz[y]*sz[y];
        ans[x] += (n-sz[x])*(n-sz[x]);
        now += cnt[x]*(ans[x]-n+cnt[x]);
    }
    cout << n*(n-1)*(n-2)-now << '\n';
    while (m--) {
        int x = find(read()), y = find(read());
        while (x^y) {
            if (dep[x] < dep[y]) swap(x, y);
            merge(find(Fa[x]), x), x = find(Fa[x]);
        }
        cout << n*(n-1)*(n-2)-now << '\n';
    }
    return 0;
}
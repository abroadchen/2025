//
// Created by Psy.C on 2026/9/14.
//
/**
判断整个图是否连通（所有边是否都在同一个连通块）
读取 n 个点、m 条边。
用并查集合并所有边。
自环（l[i]==r[i]，起点=终点）单独计数 cnt。
非自环边，给两端点度数各加 1
检查所有边是否属于同一个连通块。只要有一条边在不同连通块 → 输出 0 并退出。说明要求图连通
第一项：(cnt-1)*cnt/2

从 cnt 个自环中任取 2 个的组合数 C(cnt,2)。代表"两个自环顶点 + 连接它们的边"构成的三边闭合结构数量。

第二项：cnt*(m-cnt)

每个自环可与任意一条非自环边组合 → 构成含自环的三边结构。

第三项：Σ deg[i]*(deg[i]-1)/2

对每个点 i，从它的 deg[i] 条邻边中任取 2 条，构成以 i 为中心的"星形"三条边结构，即 C(deg[i],2)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2e6+10;

int fa[N];
inline int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}
inline void uni(int u, int v) {
    int x = find(u), y = find(v);
    if (x != y) fa[x] = y;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int l[N], r[N], cnt, deg[N], ans;
signed main() {
    fast;
    int n = rd(), m = rd();
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) {
        l[i] = rd(), r[i] = rd();
        uni(l[i], r[i]);
        if (l[i] == r[i]) cnt++;
        else {
            deg[l[i]]++; deg[r[i]]++;
        }
    }
    int x = find(l[1]);
    for (int i = 2; i <= m; ++i)
        if (find(l[i]) != x)
            return puts("0"), 0;
    ans += (cnt-1)*cnt/2;
    ans += cnt*(m-cnt);
    for (int i = 1; i <= n; ++i)
        ans += deg[i]*(deg[i]-1)/2;
    cout << ans << '\n';
    return 0;
}
//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
e 是边表，按边权 w 升序排序（Kruskal 用）。
fa 是并查集，带路径压缩
iota 把并查集初始化为 fa[i]=i。
f[a[i]]=1 标记出特殊点
逐条处理升序边（经典 Kruskal）：

两端在不同集合则考虑合并。
关键语句：若合并双方 f[x] 和 f[y] 都为真（即两个集合里都有特殊点），说明"用当前边连接了两个都含特殊点的集合"，此时把最大边权更新为 e[i].w。由于边按升序扫，最后一次这样合并的边权就是最小可行方案中的最大边 mx。
然后合并 fa[x]=y，特殊点标记用 | 合并。
这样就求出了"让所有特殊点两两连通，方案中最大边能达到的最小值"
每个特殊点都输出同一个 mx。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

struct node {
    int x, y, w;
    bool operator<(node o) const { return w < o.w; }
} e[N];

int n, m, k, a[N], f[N], mx;
int main() {
    fast;
    cin >> n >> m >> k, iota(fa+1, fa+n+1, 1);
    rep(i,k) cin >> a[i], f[a[i]] = 1;
    for (int i = 1, x, y, w; i <= m; i++) {
        cin >> x >> y >> w; e[i] = {x, y, w};
    }
    sort(e+1, e+m+1);
    rep(i,m) {
        int x = find(e[i].x), y = find(e[i].y);
        if (x != y) {
            (f[x] && f[y]) && ((mx = e[i].w));
            fa[x] = y, f[y] |= f[x];
        }
    }
    rep(i,k) cout << mx << ' ';
    return 0;
}
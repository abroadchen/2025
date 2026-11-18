//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
边结构体存 x、y、权值 c，按 c 排序（用于 Kruskal）。
e[N<<1] 边数组容量约 2N（n 条虚拟边 + m 条普通边）。
并查集 find 标准路径压缩
经典 Kruskal：按边权升序遍历所有边，若两端不在同一集合则合并，累加权值，直到选出 n-1 条边（tot <= n-1 提前停）。
返回 MST 总权值
读 n 个点的权值 a[i]，初始化并查集（f[i]=i）。
找出全局最小权值的点 p，其权值为 mn。
对每个不同于 p 的点 i，加入一条边：(p, i, a[i]+mn)。
关键洞察：任意两点 i、j 之间存在隐式边 a[i]+a[j]。在 MST 里，这种边可以通过"i—p—j"替代，总代价 a[i]+mn+a[j]+mn？不对——这里是把 p 作为枢纽。
实际上：由于 a[p]=mn 是全局最小，任意两点的隐式边 a[i]+a[j] ≥ a[i]+mn 和 a[j]+mn，所以最优方案里，跨越虚拟边的连接都经过最小点 p：边 (p,i, a[i]+mn)。这样把原本 O(n²) 的点对边压缩成 O(n) 条从 p 出发的边。
即任何两点如果要靠"a 值和"相连，走 p 中转代价 ≤ 直接连，因此直接连的边不会进最优森林，可安全省略
读入 m 条普通边，加入边集。
边集排序，跑 Kruskal，输出结果。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define int long long
using namespace std;

constexpr int N = 2e5+5, inf = 0x3f3f3f3f3f3f3f3f;

struct edge {
    int x, y, c;
    bool operator<(const edge& o) const { return c < o.c; }
} e[N<<1];

int f[N];
int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

int sz, n;
int krusk() {
    int ans = 0, tot = 0;
    for (int i = 1, x, y; i <= sz && tot <= n-1; i++) {
        x = e[i].x, y = e[i].y; x = find(x); y = find(y);
        if (x == y) continue;
        f[x] = y; tot++; ans += e[i].c;
    }
    return ans;
}

int m, a[N], p;
signed main() {
    fast;
    cin >> n >> m;
    int mn = inf;
    rep(i,n) {
        cin >> a[i]; f[i] = i;
        if (a[i] < mn) mn = a[i], p = i;
    }
    rep(i,n) {
        if (i == p) continue;
        e[++sz].c = a[i] + mn; e[sz].x = p; e[sz].y = i;
    }
    int t1, t2, t3;
    rep(i,m) {
        cin >> t1 >> t2 >> t3;
        e[++sz].c = t3; e[sz].x = t1; e[sz].y = t2;
    }
    sort(e+1, e+sz+1);
    cout << krusk() << '\n';
    return 0;
}
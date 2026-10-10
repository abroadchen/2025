//
// Created by Psy.C on 2026/10/10.
//
/**
无向图，n 点 m 边，邻接表存
每次以连通块内某点 s 为根做 DFS：

建立 DFS 生成树：记录父 anc[0][y]、深度 dep[y]，以及树上这条边两端 {min,max}。
当遇到已访问的非父邻居 y 且 dep[y] < dep[x]-1（即它是横跨的回边/返祖边，不是简单的树边回访），压入 bk 作为一条非树边。
作用：找出图中所有"不在生成树里"的边（即构成环的边），后续用来处理点对连通/环的信息
anc[i][j]：j 向上 2^i 步的祖先（LCA 倍增）。
mn/mx[i][j]：从 j 沿 2^i 步路径上所有点的最小 / 最大编号（用于快速求一条路径上点的编号范围）
标准 LCA 模板，同时维护整条路径上的最小、最大顶点编号
每条非树边 (x,y) 对应树上 x→y 路径，[a,b] = 该路径上点的编号范围。存到 buc[a]（每个起点 a 一个桶）。

含义：一条回边跨越的路径区间 [a,b]——若一个询问区间 [l,r] 完全包含某条回边的路径 min..max，则这些点能通过该回边构成环（即该区间内存在"环/非树边"）
从右往左扫：cur 记录"起点 ≥ i 的所有回边里，最小的 b"。lim[i] = 从 i 向右，最近能"被一条回边闭合到的最远起点"的最优（实际表示：以 ≥i 为起点的回边能覆盖的最左 b，取最小）。
lim 再前缀和成 lim[i]=lim[i-1]+lim[i]，供后面
O
(
log
⁡
n
)
O(logn)/常数计算
输出一个用 lim 前缀和与等差数列求和公式拼出来的计数结果，是经典"矩形面积 / 区间内满足条件的点对数"求和公式在离线处理下的
O
(
log
⁡
n
)
O(logn) 回答
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define vi vt<int>
#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define per(i,a,b) for (int i=a; i>=b; --i)
#define ii pair<int, int>
using namespace std;
template<typename T>
using vt = vector<T>;
template<typename T>
T chkmin(T& x, T y) { return x > y ? (x = y, y) : x; }
template<typename T>
T chkmax(T& x, T y) { return x < y ? (x = y, y) : x; }

signed main() {
    fast;
    int n, m; cin >> n >> m;
    vt<vi> g(n+1);
    rep(i,1,m) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y); g[y].emplace_back(x);
    }
    vt<vi> anc(20, vi(n+1, 0)), mn = anc, mx = anc;
    vi dep(n+1, 0);
    vt<ii> bk;//回边列表
    auto dfs = [&](auto&& self, int x, int s) -> void {
        for (auto& y : g[x]) {
            if (y^anc[0][x]) {//y 不是父节点
                if (!dep[y] && y != s) {//未访问（且不是起点 s，避免把回边当树边）
                    anc[0][y] = x, mn[0][y] = min(x, y);
                    mx[0][y] = max(x, y), dep[y] = dep[x] + 1;
                    self(self, y, s);
                }
                //y 已访问且是"回边"（y 是 x 的祖先且非父）
                else if (dep[y] < dep[x] - 1) bk.emplace_back(x, y);
            }
        }
    };
    rep(i,1,n) if (!dep[i]) {
        anc[0][i] = mn[0][i] = mx[0][i] = i;
        dfs(dfs, i, i);
    }
    rep(i,1,19) rep(j,1,n) {
        anc[i][j] = anc[i-1][anc[i-1][j]];
        mn[i][j] = min(mn[i-1][j], mn[i-1][anc[i-1][j]]);
        mx[i][j] = max(mx[i-1][j], mx[i-1][anc[i-1][j]]);
    }
    auto query = [&](int x, int y) -> ii {
        int mnn = min(x, y), mxx = max(x, y);
        if (dep[x] < dep[y]) swap(x, y);
        int d = dep[x] - dep[y];
        rep(i,0,19) if (d&(1<<i)) {
            chkmin(mnn, mn[i][x]), chkmax(mxx, mx[i][x]);
            x = anc[i][x];
        }
        if (x == y) return {mnn, mxx};
        per(i,19,0) if (anc[i][x] != anc[i][y]) {
            chkmin(mnn, min(mn[i][x], mn[i][y]));
            chkmax(mxx, max(mx[i][x], mx[i][y]));
            x = anc[i][x], y = anc[i][y];
        }
        chkmin(mnn, min(mn[0][x], mn[0][y]));
        chkmax(mxx, max(mx[0][x], mx[0][y]));
        return {min(mnn, anc[0][x]), max(mxx, anc[0][x])};
    };
    vt<vi> buc(n+1);
    vi lim(n+1, 0);
    for (auto& [x, y] : bk) {
        auto [a, b] = query(x, y);//回边两端在树上的路径 min/max
        buc[a].emplace_back(b);//按 a 分桶
    }
    int cur = n + 1;
    per(i,n,1) {
        for (auto& x : buc[i]) chkmin(cur, x);
        lim[i] = cur;
    }
    vi t = lim;
    rep(i,1,n) lim[i] += lim[i-1];
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        int L = l, R = r, p = r + 1;
        while (L <= R) {
            int mid = (L + R) >> 1;
            if (t[mid] <= r) L = mid + 1;
            else R = (p=mid) - 1;
        }
        cout << lim[p-1] - lim[l-1] + (r-p+1)*(r+1) - r*(r+1)/2 + l*(l-1)/2 << '\n';
    }
    return 0;
}
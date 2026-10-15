//
// Created by Psy.C on 2026/10/15.
//
/**
读入 n 个点、m 条边，每条边形如 (u, v, a, b, c, d)，其容量是 w 的线性区间：

下界 = a*w + b*L
上界 = c*w + d*L
w 是待定的某个整数参数（范围 [0, L]，L = 1e8），L 是一个大的缩放常数（相当于把 b,d 的系数放大 L 倍，做整数化/整形处理，避免浮点）。

gap(w) 返回：在该 w 下，带上下界可行流的最小总流量（即把每条边的下界先强制流掉之后的最小补给量）。

目标是找 w 使得这个"可行性代价"最小。这套做法常见于 最小析（minimum cut / 某种参数化可行流问题）‍ 或者 二分图/图的某种带参数容量可行流。gap(w) 返回 0 就表示在该 w 下存在满足所有上下界的可行流
hd, d, cr：链式前向星的表头、层次、当前弧。

deg：上下界可行流"不平衡度"数组（deg[u] -= l; deg[v] += l）。

add_l(u, v, l, r)：添加一条下界 l、上界 r 的边。做法是
这是上下界可行流的标准建图：把下界 l 作为"强制流量"记录到点的净需求 deg 里，原边只保留 r-l 的自由容量
设超级源 s = n-1、超级汇 t = n（把原图 1..n 之外接两个虚点）。
对每个点：若 deg[i] > 0（净需求为正，即必须多流出），连 s→i 容量 deg[i]；若 deg[i] < 0，连 i→t 容量 -deg[i]。
跑经典 Dinic，最大流 mf。
返回 sum - mf：其中 sum = 所有正 deg 之和（即要满足的全部下界需求）。如果 mf == sum，说明所有下界需求都被满足，返回 0 → 该 w 下存在可行流；否则返回差额（下界无法全部满足的最小缺口）。
这就是上下界网络流判可行的模板：最小可行流 = 全部下界需求 sum 减去实际能灌进去的最大流 mf
对每条边，用当前 w 算出其上下界（都是 w 的线性函数，系数 L 放大整数化）。
放进上界/下界建图，跑可行流判定，返回缺口。
gap(w) 输出越小越"可行"；若输出 0，说明该 w 完全可行。这其实是一个关于 w 的代价函数，我们要找它的最小零点/最优 w。
在 [0, L] 里做三分搜索，收敛到代价函数 gap(w) 的极小值点附近（假设函数是凸的/单谷的）。
因为 gap 是"缺口的整数阶"，可以假定它随 w 变化是凸的——这是这类参数化可行流问题的常见性质（如果 gap==0 可行区间是一段，则函数是下凸/类凸）
三分钟后停在 [l, r]（长度 ≤ 4），然后线性扫这个小区间找最小 gap
res.first = 最小 gap 值，res.second = 对应的 w。
如果最小 gap 都不是 0，说明没有任何 w 能造出可行流，直接输出 0 结束
从 pl+1 开始二分，找最右边仍有 gap == 0（可行）‍ 的 w，记为 pr
找最左边仍有 gap == 0 的 w，记为 pl。
于是 [pl, pr] 就是所有使可行流存在的 w 的完整区间
输出 (pr - pl) / L：可行 w 区间的长度占 L 的比例（6 位小数）。L = 1e8 是 w 的取值上界，除以它把整型区间归一化成比例。
因为建图时把 b*w、d*w 的系数乘了 L（1ll*b*L），所以最终归一化要除以 L 才能还原成"每个单位 w 对应多少真实容量"。这也是为什么把比例输出成 1.*(pr-pl)/L
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define li pair<ll, int>
using namespace std;

constexpr int N = 1e3+1e2, M = 2e3+2e2, L = 1e8;
constexpr ll inf = 1e18;

struct Flow {
#define rz(x,y,z) x.resize(y+5,z)
    struct edge { int to, nxt; ll w; };
    int n{}, tot{}, s{}, t{};
    vector<int> hd,d, cr;
    vector<ll> deg;
    vector<edge> e;
    Flow() = default;
    Flow(int _n) : n(_n), tot(-1) {
        rz(hd, n, -1); rz(d,n,0); rz(deg,n,0), e.clear();
    }
    void add_e(int u, int v, ll w) { e.emplace_back(edge(v, hd[u], w)), hd[u]=++tot; }
    void add_f(int u, int v, ll w) { add_e(u, v, w); add_e(v, u, 0); }
    void add_l(int u, int v, ll l, ll r) { add_f(u, v, r-l); deg[u] -= l; deg[v] += l; }
    bool bfs() {
        ranges::fill(d, 0);
        queue<int> q; q.push(s); d[s] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = hd[u]; ~i; i = e[i].nxt) {
                int v = e[i].to;
                if (!e[i].w || d[v]) continue;
                d[v] = d[u] + 1, q.push(v);
            }
        }
        return d[t];
    }
    ll dfs(int u, ll in) {
        if (u == t) return in;
        ll out = 0;
        for (int &i = cr[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            if (e[i].w && d[v] == d[u] + 1) {
                ll res = dfs(v, min(in, e[i].w));
                in -= res, out += res;
                e[i].w -= res, e[i^1].w += res;
            }
            if (!in) break;
        }
        if (!out) d[u] = 0;
        return out;
    }
    ll dinic() {
        ll sum = 0, mf = 0; s = n-1, t = n;
        for (int i = 1; i <= n; i++) {
            if (deg[i] > 0) add_f(s, i, deg[i]), sum += deg[i];
            if (deg[i] < 0) add_f(i, t, -deg[i]);
        }
        while (bfs()) cr = hd, mf += dfs(s, inf);
        return sum - mf;
    }
};

struct E { int u, v, a, b, c, d; } e[M];

int n, m;
ll gap(int w) {
    Flow G(n+2);
    for (int i = 1; i <= m; i++) {
        auto [u, v, a, b, c, d] = e[i];
        G.add_l(u, v, 1ll*a*w+1ll*b*L, 1ll*c*w+1ll*d*L);
    }
    return G.dinic();
}

void solve() {
    cin >> n >> m;
    for (int i = 1, u, v, a, b, c, d; i <= m; i++)
        cin >> u >> v >> a >> b >> c >> d, e[i] = {u, v, a, b, c, d};
    int l = 0, r = L, pl, pr;
    while (r - l >= 5) {
        int m1 = l+(r-l)/3, m2 = r-(r-l)/3;
        if (gap(m1) <= gap(m2)) r = m2;
        else l = m1;
    }
    li res = {inf, L};
    for (int i = l; i <= r; i++) res = min(res, {gap(i), i});
    if (res.first) return cout << 0 << '\n', void();
    pl = pr = res.second, l = pl+1, r = L;
    while (l <= r) {
        int md = (l+r)>>1;
        if (gap(md) == res.first) l = md+1, pr = md;
        else r = md-1;
    }
    l = 0, r = pl-1;
    while (l <= r) {
        int md = (l+r)>>1;
        if (gap(md) == res.first) r = md-1, pl = md;
        else l = md+1;
    }
    cout << fixed << setprecision(6) << 1.*(pr-pl)/L << '\n';
}

int main() {
    fast;
    int T = 1;
    while (T--) solve();
    return 0;
}
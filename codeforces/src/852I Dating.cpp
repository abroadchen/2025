//
// Created by Psy.C on 2026/9/29.
//
/**
每个节点有两种属性：g[i]（组别/颜色，0/1）和 f[i]（离散化后的 int 值）。
若干次查询：给定树上两个点，求 路径 (a,b) 上满足"g 属性不同 且 f 相等"的点对数 之类（ret 统计的就是 g=0 与 g=1 且 f 相同的配对对数）。
树上路径查询用 DFS 序转成序列区间，用莫队离线处理
cnt[gi][fi]：当前莫队区间内，组别 gi、f 值 fi 的节点个数。
ret：满足"一组 g=0、另一组 g=1 且 f 相同"的配对数之和
莫队滑动窗口时把序列位置 x（对应节点 id[x]）‍加入或移除。
op[id[x]]：该节点的"当前极性"（进入区间为 +1，离开为 -1），翻转时取反。
加入/移除时：
先 ret += 极性 × cnt[对方组][同 f]：即"这个点与当前区间里、g 与自己不同且 f 相同的点"的配对数增减。
更新自身组的计数 cnt[g][f] += 极性。
翻转极性 op[id[x]] = -op[id[x]]。
因为每个节点不管
g
g 是 0 还是 1，只与 另一个组 配对，所以答案就是异组同 f 的配对数
标准的括号序（欧拉序）‍：每个节点出现两次，in[u] 第一次（进入），out[u] 第二次（离开）。
同时建好 LCA 倍增表 pa[u][i]（pa[u][i]：u 向上走
2
i
2
i
  步的祖先）和深度 dep[]
标准 LCAbinary lifting：先对齐深度，再同时跳，最后返回共同祖先
树上路径转成括号序区间的标准手法：
若一个点 a 是另一个点 b 的祖先：路径上的节点对应区间 [in[a], in[b]]（奥妙：路径上的其它点只出现一次，祖liǎng者在此区间内也算正确）。
否则：区间取 [out[深者], in[浅者]]（需保证 L < R，用 in 比较调换），此时路径上"除了 lca 之外的每个点恰好出现一次"，而 lca 不会出现在区间内，需要单独补上。
每个查询记录了 lca 和对应的左右端点 L,R
莫队核心：按 L 分块、R 单调排序，左指针 l、右指针 r 滑动，update 维护 ret。

lca 的补偿：当路径是"非祖先-祖先"型时，lca 没进区间。lca 与区间里"与自己组别不同且 f 相同"的点配对数为 cnt[g[lca]^1][f[lca]]，所以答案 = ret + cnt[g[lca]^1][f[lca]]【前提：lca 不在区间两端（id[L]/id[R] 恰是区间边界时它可能已在区间内），故先判 lca != id[L] && lca != id[R]，此时才补】。

f[] 在 main 开头用离散化（lower_bound）压缩到小范围，cnt[2][N] 第二维才能开得下
按查询原顺序输出每个答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+7, B = 500;

struct node {
    int L, R, lca, id;
    bool operator<(const node &o) const {
        if (L/B == o.L/B) return R < o.R;
        return L < o.L;
    }
} qs[N];

ll ret;
int op[N], id[N], cnt[2][N], g[N], f[N];
inline void update(int x) {
    ret += op[id[x]]*cnt[g[id[x]]^1][f[id[x]]];
    cnt[g[id[x]]][f[id[x]]] += op[id[x]];
    op[id[x]] = -op[id[x]];
}

int dep[N], pa[N][20], idx, in[N], out[N];
vector<int> G[N];
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1; pa[u][0] = fa;
    for (int i = 1; i < 20; ++i)
        pa[u][i] = pa[pa[u][i-1]][i-1];
    id[++idx] = u; in[u] = idx;
    for (auto& v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
    id[++idx] = u; out[u] = idx;
}

int get(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 19; ~i; --i)
        if ((dep[u]-dep[v])>>i&1) u = pa[u][i];
    if (u == v) return u;
    for (int i = 19; ~i; --i)
        if (pa[u][i] != pa[v][i])
            u = pa[u][i], v = pa[v][i];
    return pa[u][0];
}

vector<int> vv;
ll ans[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> g[i], op[i] = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> f[i]; vv.push_back(f[i]);
    }
    for (int i = 1, a, b; i < n; ++i) {
        cin >> a >> b;
        G[a].push_back(b); G[b].push_back(a);
    }
    ranges::sort(vv);
    vv.erase(ranges::unique(vv).begin(), vv.end());
    for (int i = 1; i <= n; ++i)
        f[i] = lower_bound(vv.begin(), vv.end(), f[i]) - vv.begin();
    dfs(1, 0);
    int q; cin >> q;
    for (int i = 1; i <= q; ++i) {
        int a, b, lca; cin >> a >> b; lca = get(a, b);
        if (lca == a || lca == b) {
            if (a == lca) qs[i] = {.L = in[a], .R = in[b], .lca = a, .id = i};
            else qs[i] = {.L = in[b], .R = in[a], .lca = b, .id = i};
        } else {
            if (in[a] < in[b]) qs[i] = {.L = out[a], .R = in[b], .lca = lca, .id = i};
            else qs[i] = {.L = out[b], .R = in[a], .lca = lca, .id = i};
        }
    }
    int l = 1, r = 0; ret = 0;
    sort(qs+1, qs+1+q);
    for (int o = 1; o <= q; ++o) {
        int L = qs[o].L, R = qs[o].R, lca = qs[o].lca, who = qs[o].id;
        while (r < R) update(++r);
        while (l > L) update(--l);
        while (r > R) update(r--);
        while (l < L) update(l++);
        if (lca != id[L] && lca != id[R])
            ans[who] = ret + cnt[g[lca]^1][f[lca]];
        else ans[who] = ret;
    }
    for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
    return 0;
}
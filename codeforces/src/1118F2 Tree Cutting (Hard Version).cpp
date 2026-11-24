//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
L[u]..R[u] 是子树
u
u 的欧拉序区间。
check(u,v)：判断 u 是否为 v 的祖先（v 在 u 的子树区间内）
根为 dfs2(1,0)，每个节点两种状态 0/1，子节点可任选状态（f0+f1）或强制为 1（f1），按乘法原理累乘并取模。
这是一类"给树上每个点染色 0/1，某些约束点固定颜色"的方案计数 DP
读入点权 a[i]，下标分组 v[i]（放同色节点）；DFS 建序
对每个颜色 i，把它所有节点通过 fa/区间判断向上归并到同一祖先路径，用 b[] 标记归属（类似并查集实现"同一颜色的点必须落在同一条根路径上"）。
若发现同一点被两种颜色标记（b[p] 冲突）→ 无解输出 0
把所有点映射到 id（有颜色的用颜色号、无色的新建编号），在新图 G 上重新建边（去掉自环/同色内部边）。
在新树上跑 DP dfs2(1,0)，输出 f1[1]（根取状态 1 的方案数）对 mod 取模

u 之前已经是状态 1：那 v 可以任意选（状态 0 或 1 都行）
→ 贡献 f1[u] * (f0[v] + f1[v])
u 原本是状态 0，v 取状态 1：因为某些约束要求 v=1 时，u 也必须从 0 变 1（或反之，视题意）
→ 贡献 f0[u] * f1[v]
即：u 保持 1（v 任意）的方案 ＋ u 从 0 升级为 1（v 必须 1）的方案，二者相加就是合并后 u 取状态 1 的方案数
只有一种来源：
u 保持状态 0：那 v 可以任意取（0 或 1）
→ f0[u] * (f0[v] + f1[v])
注意：没有 f1[u] 变回 0 的情形 —— 因为一旦 u 取过 1，就不能再"降"回 0（状态 1 是"升级/固定"的，不能回退）。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 3e5+5, mod = 998244353;

int L[N], R[N], tim, fa[N];
vector<int> g[N];
void dfs(int u) {
    L[u] = ++tim;
    for (auto v : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u;
        dfs(v);
    }
    R[u] = tim;//退出时记录子树最大时间戳
}
bool check(int u, int v) { return L[u] <= L[v] && L[v] <= R[u]; }

int m;
ll f0[N], f1[N];
vector<int> G[N];
void dfs2(int u, int f) {
    if (u <= m) f1[u] = 1; else f0[u] = 1;
    for (auto v : G[u]) {
        if (v == f) continue;
        dfs2(v,u);
        f1[u] = (f1[u]*(f0[v]+f1[v])+f0[u]*f1[v])%mod;
        f0[u] = f0[u]*(f0[v]+f1[v])%mod;
    }
}

int n, a[N], b[N], idx, id[N];
vector<int> v[N];
void solve(int x, int y) {
    cin >> n >> m;
    rep(i,n) {
        cin >> a[i];
        if (a[i]) v[a[i]].push_back(i);
    }
    rep(i,n-1) {
        int x, y; cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    dfs(1);
    rep(i,m) {
        int p = v[i][0];
        if (b[p] && b[p] != i) { cout << "0\n"; return; }
        b[p] = i;
        for (auto q : v[i]) {
            while (!check(p,q)) {
                p = fa[p];
                if (b[p] && b[p] != i) { cout << "0\n"; return; }
                b[p] = i;
            }
            while (b[q] != i) {
                if (b[q]) { cout << "0\n"; return; }
                b[q] = i, q = fa[q];
            }
        }
    }
    idx = m;
    rep(i,n) {
        if (!b[i]) id[i] = ++idx;
        else id[i] = b[i];
    }
    rep(u,n) for (auto v : g[u])
        if (id[u] != id[v]) G[id[u]].push_back(id[v]);
    dfs2(1,0);
    cout << f1[1] << '\n';
}

int main() {
    fast;
    int T = 1, x = -1;
    rep(i,T) solve(x,i);
    return 0;
}
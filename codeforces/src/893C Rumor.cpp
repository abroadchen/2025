//
// Created by Psy.C on 2026/10/9.
//
/**
fa[i] 是每个点的父节点，初始 fa[i]=i（每个点自成一个集合）。
find(u)：找
u
u 所在集合的根，带路径压缩（递归把路径上所有点直接连到根），保证接近
O
(
α
(
n
)
)
O(α(n))
合并两个集合（
u
,
v
u,v 所在连通块），若已在同一集合则跳过。
关键：合并时把两个根中的较小代价记录到新根 u 上（c[u] = min(c[u], c[v])）。
即：一个连通块内所有点的总"代价"由块内最小的 c 值代表。
c[v] 那行其实多余，因为 fa[v]=u 后 v 不再是根，它的 c[v] 不再被 find(v)==v 时读取。
fa[v] = u：常规按某种方式合并（这里固定把 v 挂到 u）
读入
n
n 个点各自的代价 c[i]。
初始每个点独立。
读入
m
m 条边
(
a
,
b
)
(a,b)，把它们所在连通块合并，同时每个连通块的代价 = 块内最小 c
遍历每个点，若它是自己所在集合的根（find(i)==i），说明它代表一个连通块，把该块的代价 c[i]（= 块内最小值）累加进 ans。
最终 ans = 所有连通块的最小代价之和
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+10;

int n;
ll fa[N];
void init() { for (int i = 1; i <= n; ++i) fa[i] = i; }
int find(ll u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
ll c[N];
void uni(ll u, ll v) {
    u = find(u); v = find(v);
    if (u == v) return;
    c[u] = min(c[u], c[v]);
    c[v] = min(c[v], c[u]);
    fa[v] = u;
}

int m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> c[i]; init();
    for (int i = 1; i <= m; ++i) {
        ll a, b; cin >> a >> b; uni(a, b);
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        if (find(i) == i) ans += c[i];
    cout << ans << '\n';
    return 0;
}
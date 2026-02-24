//
// Created by Psy.C on 2026/2/24.
//
/**
N = 200001：节点数量上限
M = 21：倍增数组的层数（log₂(N)）
nxt：下一条边的索引
to：到达的节点
cnt：边的计数器
head[i]：节点i的第一条边的索引
a[i][j]：节点i的第2^j级祖先
dep[i]：节点i的深度

计算每个节点的2^j级祖先
利用已经计算好的2^(j-1)级祖先
确保x的深度不小于y
将x向上跳到与y同一深度：
通过二进制分解深度差
逐位调整x的位置
如果x==y，说明y就是LCA
同时向上跳跃寻找LCA：
当祖先不同时继续向上跳
直到找到最近的公共祖先
返回LCA（此时x和y的父节点就是LCA）

递归实现扩展欧几里得：
返回满足ax + by = gcd(a,b)的一组解
求解线性同余方程的函数：
c = t2 - t1：常数项
g = gcd(d1, d2)：最大公约数
如果c不能被gcd整除，则无解
使用扩展欧几里得求特解并标准化
调整到最小非负解：
确保两个变量都非负
返回最小正解

求解模线性方程的辅助函数：
处理边界情况
如果区间跨越了a的倍数边界，直接返回解
递归求解模线性方程

处理带有额外约束的方程求解：
检查奇偶性条件

处理四个点的路径问题
计算所有可能的LCA并按深度排序
检查特殊情况：是否存在解
计算相关距离参数
调整距离参数到合适的范围
计算最小答案并返回



 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+1, M = 21;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;//不可达状态
struct node { int nxt, to; } e[N<<1];
int cnt, head[N];
void add(const int x, const int y) {
    e[++cnt] = {head[x], y};
    head[x] = cnt;
}

int a[N][M], dep[N];
void dfs(const int u, const int fa) {
    a[u][0] = fa;//记录直接父节点
    dep[u] = dep[fa]+1;
    for (int i = head[u]; i; i = e[i].nxt) {
        if (const int to = e[i].to; to != fa)
            dfs(to, u);
    }
}

int n;
void init() {
    for (int j = 1; (1<<j) <= n; ++j)
        for (int i = 1; i <= n; ++i)
            a[i][j] = a[a[i][j-1]][j-1];
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = M-2; i >= 0; --i)
        if ((dep[x]-dep[y])&(1<<i)) x = a[x][i];
    if (x == y) return x;
    for (int i = M-2; i >= 0; --i)
        if (a[x][i] != a[y][i]) x = a[x][i], y = a[y][i];
    return a[x][0];
}

int get(const int x, const int y) {
    return dep[x] + dep[y] - 2*dep[lca(x, y)];
}

pair<ll, ll> dfs2(const ll a, const ll b) {
    if (!a) return {0, b < 0 ? -1 : 1};
    auto [fst, snd] = dfs2(b%a, a);
    return {snd-fst*(b/a), fst};
}

ll f(ll d1, ll d2, const ll t1, const ll t2) {
    ll c = t2 - t1, g = __gcd(d1, d2);
    if (c%g) return inf;
    auto [fst, snd] = dfs2(d1, -d2);
    fst *= c/g, snd *= c/g;
    d1/=g, d2/=g;
    if (fst < 0 || snd < 0) {
        const ll s = max((-fst-1)/d2+1, (-snd-1)/d1+1);
        fst += s*d2, snd += s*d1;
    }
    const ll s = min(fst/d2, snd/d1);
    return (fst-s*d2)*d1*g+t1;
}

ll dfs3(const ll l, const ll r, const ll a, const ll b) {
    if (l > r || !a) return inf;
    if ((l-1)/a != r/a) return (l+a-1)/a;
    const ll res = dfs3((a-r%a)%a, (a-l%a)%a, b%a, a);
    if (res == inf) return inf;
    return (res*b+l+a-1)/a;
}

ll f(const ll d1, const ll d2, const ll t1, const ll t2, const ll d) {
    if ((d+t1+t2)&1) return inf;
    ll x;
    if (ll l = ((t2-t1-d)%d2+d2)%d2, r = ((t2-t1+d)%d2+d2)%d2; !l || 2*d == d2 || l > r) x = 0;
    else x = dfs3(l, r, d1%d2, d2);
    if (x == inf) return inf;
    const ll y = (x * d1 + t1 - t2 + d) / d2;
    return (x*d1+y*d2+t1+t2+d)/2;
}

ll out(const int u, const int v, const int x, const int y) {
    int l[] = {0, lca(u, x), lca(u, y), lca(v, x), lca(v, y)};
    sort(l + 1, l + 5, [](const int a, const int b) {
        return dep[a] < dep[b];
    });
    if (l[3] == l[4] && dep[l[3]] < max(dep[lca(x, y)], dep[lca(u, v)]))
        return -1;
    const int d1 = get(u, v)*2, d2 = get(x, y)*2, d = get(l[3], l[4]);
    int u1 = get(u, l[3]), u2 = get(u, l[4]);
    if (u1 < u2) u2 = d1 - u2; else u1 = d1 - u1;
    int x1 = get(x, l[3]), x2 = get(x, l[4]);
    if (x1 < x2) x2 = d2 - x2; else x1 = d2 - x1;
    const ll ans = min(min(f(d1, d2, u1, x1), f(d1, d2, u2, x2)),
        min(f(d1, d2, u1, x2, d), f(d1, d2, u2, x1, d)));
    if (ans == inf) return -1;
    return ans;
}

int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        add(x, y), add(y, x);
    }
    dfs(1, 0); init();
    int q; cin >> q;
    while (q--) {
        int u, v, x, y; cin >> u >> v >> x >> y;
        cout << out(u, v, x, y) << '\n';
    }
    return 0;
}
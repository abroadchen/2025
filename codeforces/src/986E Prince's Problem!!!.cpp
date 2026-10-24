//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
N：树的节点上限；M=3200（约 sqrt(1e7)）；mod 为模数。
st[]：筛法标记质数；p[]：质数表；cnt：质数个数
欧拉线性筛，O(n) 筛出 M 以内的质数。break 是核心：保证每个合数只被其最小质因子筛一次，从而 O(n) 复杂度
邻接表存树的双向边。无向边存两次。idx 从 1 开始
计算子树大小 sz、父节点 fa、深度 dep、重儿子 son（子树最大的子节点）。这是树链剖分的基础。
轻重链剖分：重儿子和父节点在同一链（同 top），轻儿子独立成链。dfn 使每个节点的子树在 DFS 序上是连续区间 [dfn[u], dfn[u]+sz[u]-1]——这是后面树状数组做树上区间加/查的关键
用树链剖分求 LCA：不断把链顶较深的节点上跳到父链，直到同一链，返回深度小的。O(log n)
树状数组实现：
add(x,v) 单点加；sum(x) 前缀和。
add(l,r,v) 差分区间加（在 l 处 +v，r+1 处 -v），配合单点前缀和 sum(x) 实现区间加、点查询。
clear 将加过的位置回退清零，用于每个质因子处理完后清空树状数组复用。
声明两个 BIT：t1、t2，分别统计质因子指数贡献和出现次数贡献
qu：一次问询记录。q 是某个质因子的指数要求（阈值），u 是节点编号，t 是容斥系数（+1/-1），id 是原始询问编号。按 q 排序用于双指针
快速幂。默认 b = mod-2（费马小定理求逆元）‍：ksm(a) 返回 a^{-1} mod p
a[i]：节点权值。
ver[k]：对第 k 个质因子，收集所有节点的 (指数, 节点号)。
Q[k]：对第 k 个质因子，收集所有询问的容斥项。
mp：把"超过 M 的大质因子"映射到质数表索引
筛 M 内的质数；读入 n 和树边建邻接表；剖分树；tot 记录初始小质数个数（≤M 的）
对每个节点权值 a[i]，用 ≤M 的质数试除分解。质因数指数存入 ver[j]。
若试除后剩余 x>1 且 >M，则为大质因子，用 mp 映射到新索引（暴力分解的数没法再用小质数筛，需单独处理）
对每个询问 (u,v,x) 求 LCA，然后分解 x 的质因子。
对每个质因子 p（指数 cn），利用树路径的四点容斥差分：
路径 u→v 上的贡献 = u 贡献 + v 贡献 − lca 贡献 − fa(lca) 贡献（t 为 ±1）。
这样树的点权前缀和就能算出路径上该质因子的总指数。经典技巧。
若 x 分解后剩大质因子，检查是否在 mp（即是否出现在某节点中），有则同样加入容斥项，没有则忽略（因为路径上没有该因子，贡献为 1）
这是最核心、最难的循环，对每个质因子 p[k] 独立处理：
先所有含该因子的节点，对其整棵子树做区间加（t1 加该节点上该因子的指数）。
将 ver[k]（按指数从小到大）和 Q[k]（按阈值 q 从小到大）排序。
双指针从大到小：对每个询问项（按 q 从大到小），凡是指数 > q 的节点，把它们从 t1 中"降一级"——减去该节点指数（使 t1 对之后的查询只加"能被完全吸收的部分"），并在 t2 中 +1 标记（表示该节点在路径上只贡献一个"完整因子 p^q"的量，供指数封顶处理）。
对当前询问项 u，取 res = t1 在该节点的子树前缀和（未封顶的指数贡献），cn = t2 在该节点的累计（完整 p^q 的个数）。
最终该质因子对答案的贡献：路径上 p 的总指数 = res + cn*q(封顶后每个"够大的节点"贡献一个完整的 p^q)。再乘以 p^总指数 或 inv^(总指数)（t 为 -1 时用逆元做除法），乘入 ans[id]。
处理完用 clear 将 t1、t2 清零，进入下一个质因子。
设计精髓：把"路径上质因子指数贡献"拆成两部分——不足 q 的部分按实际指数累加（t1），超过/等于 q 的部分统一按 q 封顶（t2）。这样既保证 gcd 取 min 的正确性（指数截断到 q），又通过四点容斥 + 子树区间加 + 树状数组把整个问题压到 O((n+q) · 质因子数 · log n)
*/
#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5, M = 3200, mod = 1e9+7;

bool st[M];
int p[N+M], cnt;
inline void init(int n) {
    st[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) p[++cnt] = i;
        for (int j = 1; p[j]*i <= n; j++) {
            st[i*p[j]] = 1;
            if (i%p[j] == 0) break;
        }
    }
}

int e[N<<1], nxt[N<<1], head[N], idx(1);
inline void add(int a, int b) {
    e[idx] = b, nxt[idx] = head[a], head[a] = idx++;
}


int sz[N], son[N], fa[N], dep[N];
void dfs(int u) {
    sz[u] = 1, son[u] = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = e[i];
        if (v^fa[u]) {
            fa[v] = u, dep[v] = dep[u] + 1;
            dfs(v), sz[u] += sz[v];
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    }
}

int dfn[N], tim, top[N];
void dfs2(int u, int tp) {
    dfn[u] = ++tim, top[u] = tp;
    if (son[u]) dfs2(son[u], tp);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = e[i];
        if (v^fa[u] && v^son[u]) dfs2(v, v);
    }
}

inline int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

int n;
struct BIT {
    int t[N];
    void add(int x, int v) {
        for (int i = x; i <= n+1; i += i&-i) t[i] += v;
    }
    int sum(int x) {
        int res = 0;
        for (int i = x; i; i -= i&-i) res += t[i];
        return res;
    }
    void add(int l, int r, int v) { add(l, v), add(r+1, -v); }
    void clear(int x) {
        for (int i = x; i <= n; i += i&-i) {
            if (t[i]) t[i] = 0;
            else break;
        }
    }
    void clear(int l, int r) { clear(l), clear(r+1); }
} t1, t2;
struct qu {
    int q, u, t, id;
    bool operator<(const qu &o) const { return q < o.q; }
};

inline int ksm(int a, int b=mod-2) {
    int res = 1;
    while (b) {
        if (b&1) res=1ll*res*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return res;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int a[N], q, ans[N];
vector<ii> ver[N+M];
vector<qu> Q[N+M];
unordered_map<int, int> mp;
int main() {
    init(M-1), n = rd();
    for (int i = 1, u, v; i < n; i++)
        u = rd(), v = rd(), add(u, v), add(v, u);
    dep[1] = 1, dfs(1), dfs2(1, 1);
    int tot = cnt;
    for (int i = 1; i <= n; i++) {
        a[i] = rd();
        int x = a[i];
        for (int j = 1; p[j] <= x && j <= tot; j++) {
            if (x%p[j] == 0) {
                int cn = 0;
                while (x%p[j] == 0) x/=p[j], cn++;
                ver[j].emplace_back(cn, i);
                if (x == 1) break;
            }
        }
        if (x != 1) {
            if (!mp.contains(x)) mp[x] = ++cnt, p[cnt] = x;
            ver[mp[x]].emplace_back(1, i);
        }
    }
    q = rd();
    for (int i = 1; i <= q; i++) {
        int u = rd(), v = rd(), lca = LCA(u, v), x = rd(); ans[i] = 1;
        for (int j = 1; p[j] <= x && j <= tot; j++) {
            if (x%p[j] == 0) {
                int cn = 0;
                while (x%p[j] == 0) x/=p[j], cn++;
                Q[j].push_back({cn, u, 1, i});
                Q[j].push_back({cn, v, 1, i});
                Q[j].push_back({cn, lca, -1, i});
                if (fa[lca]) Q[j].push_back({cn, fa[lca], -1, i});
                if (x == 1) break;
            }
        }
        if (x != 1) {
            if (!mp.contains(x)) continue;
            int j = mp[x], cn = 1;
            Q[j].push_back({cn, u, 1, i});
            Q[j].push_back({cn, v, 1, i});
            Q[j].push_back({cn, lca, -1, i});
            if (fa[lca]) Q[j].push_back({cn, fa[lca], -1, i});
        }
    }
    for (int k = 1; k <= cnt; k++) {
        int inv = ksm(p[k]);
        if (ver[k].empty() || Q[k].empty()) continue;
        ranges::sort(ver[k]); sort(Q[k].begin(), Q[k].end());
        for (auto &[fst, snd] : ver[k]) {
            int u = snd;
            t1.add(dfn[u], dfn[u]+sz[u]-1, fst);
        }
        int j = ver[k].size()-1;
        for (int i = Q[k].size()-1; i >= 0; i--) {
            while (j >= 0&Q[k][i].q < ver[k][j].first) {
                int u = ver[k][j].second;
                t1.add(dfn[u], dfn[u]+sz[u]-1, -ver[k][j].first);
                t2.add(dfn[u], dfn[u]+sz[u]-1, 1);
                j--;
            }
            qu u = Q[k][i];
            int res = t1.sum(dfn[u.u]), cn = t2.sum(dfn[u.u]);
            if (u.t == 1) ans[u.id] = 1ll*ans[u.id]*ksm(p[k],res+cn*u.q)%mod;
            else ans[u.id] = 1ll*ans[u.id]*ksm(inv,res+cn*u.q)%mod;
        }
        for (auto &val: ver[k] | views::values) {
            int u = val;
            t1.clear(dfn[u], dfn[u]+sz[u]-1);
            t2.clear(dfn[u], dfn[u]+sz[u]-1);
        }
    }
    for (int i = 1; i <= q; i++) write(ans[i]), putchar('\n');
    return 0;
}
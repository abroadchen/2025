//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
前向星存无向边
dep[x]：深度；dfn[x]：DFS 访问序（时间戳）；id[tim]：时间戳对应的节点（反向映射）。
f[x][0] = fa 用于后续倍增 LCA
build：叶子节点存 dfn[l]（注意 build 用 l，即数组下标的 dfn == 下标本身，因为 id[tim]=x 且 dfn 是 1..n 的一个排列，所以任意 id[i] 满足 dfn[id[i]]=i，于是这里 dfn[l]=l）。
qmx / qmn：查询区间 [L,R] 内 dfn 的最大值/最小值。因为 dfn 是排列，区间 [L,R] 的 mn/mx 就是该 dfn 区间内编号最小/最大的节点
lg = log2(n)，预处理 f[j][i] 2^i 祖先
节点区间按 dfn 编号后，[l,r] 是一个 dfn 区间（对应 DFS 序上的一段）。
L/R：这段区间里 dfn 最小/最大的节点（dfs 序两端）。
去掉端点后取剩下的次小/次大，得到 x/y。
计算 lca(L,y) 与 lca(x,R)，比较深度，输出 R 或 L 及 深度-1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; ++i)
using namespace std;

constexpr int N = 1e5+5, inf = 1e9;

int to[N<<1], head[N], tot, nxt[N<<1];
void add(int u, int v) {
    to[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
}

int dep[N], dfn[N], tim, id[N], f[N][20];
void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1, dfn[x] = ++tim, id[tim] = x, f[x][0] = fa;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y == fa) continue;
        dfs(y, x);
    }
}

int mn[N<<2], mx[N<<2];
#define ls u<<1
#define rs (u<<1|1)
#define mid ((l+r)>>1)
void push_up(int u) {
    mn[u] = min(mn[ls], mn[rs]);
    mx[u] = max(mx[ls], mx[rs]);
}
void build(int u, int l, int r) {
    if (l == r) return mn[u] = mx[u] = dfn[l], void();
    build(ls, l, mid), build(rs, mid+1, r);
    push_up(u);
}
int qmx(int u, int l, int r, int L, int R) {
    if (l > R || r < L) return 0;
    if (L <= l && r <= R) return mx[u];
    int ans = 0;
    if (L <= mid) ans = max(ans, qmx(ls, l, mid, L, R));
    if (R > mid) ans = max(ans, qmx(rs, mid+1, r, L, R));
    return ans;
}
int qmn(int u, int l, int r, int L, int R) {
    if (l > R || r < L) return inf;
    if (L <= l && r <= R) return mn[u];
    int ans = inf;
    if (L <= mid) ans = min(ans, qmn(ls, l, mid, L, R));
    if (R > mid) ans = min(ans, qmn(rs, mid+1, r, L, R));
    return ans;
}

int lg;
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = lg; ~i; --i)
        if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    if (x == y) return x;
    for (int i = lg; ~i; --i)
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, q;
int main() {
    fast;
    n = rd(), q = rd(), lg = log2(n);
    for (int i = 2; i <= n; ++i) { int v = rd(); add(i, v); add(v, i); }
    dfs(1, 0); build(1, 1, n);
    rep(i,lg) rep(j,n) f[j][i] = f[f[j][i-1]][i-1];
    while (q--) {
        int l = rd(), r = rd();
        int L = qmn(1,1,n,l,r), R = qmx(1,1,n,l,r);
        L = id[L], R = id[R];
        int x = min(qmn(1,1,n,l,L-1), qmn(1,1,n,L+1,r));
        int y = max(qmx(1,1,n,l,R-1), qmx(1,1,n,R+1,r));
        x = id[x], y = id[y];
        int t1 = lca(L, y), t2 = lca(x, R);
        if (dep[t1] > dep[t2]) cout << R << ' ' << dep[t1]-1 << '\n';
        else cout << L << ' ' << dep[t2]-1 << '\n';
    }
    return 0;
}
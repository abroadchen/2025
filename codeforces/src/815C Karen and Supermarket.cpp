//
// Created by Psy.C on 2026/9/22.
//
/**
int sz[N];            // sz[u]：以 u 为根的子树大小（节点数）
int f[N][N][2];       // f[u][j][k]：子树 u 中选 j 件，k 表示 u 是否用优惠券
int w[N];             // 原价
int c[N];             // 折扣价（优惠券价）
f[u][j][0]：在 u 的子树内选 j 件商品，其中 u 不用优惠券 时的最小花费
f[u][j][1]：在 u 的子树内选 j 件商品，其中 u 用优惠券 时的最小花费
数组版邻接表（链式前向星），e.head[u] 指向 u 的第一条边，add(u,v) 加一条 u→v 的边

初始边界（每个节点 u）：

f[u][0][0] = 0：不买任何东西，花费 0
f[u][1][0] = w[u]：只买 u 自己，不用券 → 原价
f[u][1][1] = c[u]：只买 u 自己，用券 → 折扣价
其它初始为 0x3f3f3f3f（无穷大）
注意 f[u][1][1] 能成立，因为用 u 的券只要求父节点被买，而这里 u 是根/自身，买它自己用券是允许的。

合并子节点（树上背包经典合并）：

这是分组背包式的树形合并。对每个儿子 v，把 v 的子树结果并进 u：

当 u 不用券（f[u][...][0]）时：

儿子 v 无论是用券还是不用券都可以（因为买 v 只需要 v 的父节点 u 被买，而 u 被买了——不管 u 用没用券，"u 被买"这个前提已满足）
所以取 f[u][j][0] + f[v][k][0]（v 用不用券其实都行，代码里这里只加了 v 的 [0] 分支？）
等等，这里有个细节：代码只写 f[u][j+k][0] = min(..., f[u][j][0]+f[v][k][0])，没有加 f[v][k][1]。

为什么？因为当 u 不用券时，子节点 v 也不允许用券（用 v 的券必须先买 v 的父节点 u 并用过 u 的券？）……
实际上代码这么写的原因：题目要求"用 i 的券必须先买父节点且父节点用券"。原版 Karen and Supermarket 里，用券条件是"父节点被购买（用券购买）"。所以如果 u 不用券，v 就不能用券（因为 v 用券要求父节点 u 用券）。因此 u 不用券时，v 只能不用券 → f[v][k][0]。✓

当 u 用券（f[u][...][1]）时：

v 可以用券（因为父节点 u 已用券），也可以不用券
所以取 min(f[v][k][0], f[v][k][1])，即代码里两个分支 ✓
倒序循环 j = sz[u] 递减：这是01背包式的倒序，防止当前合并重复使用同一个儿子（避免重复选择）。

这就是标准的树上分组背包（树形背包）+ 依赖限制。
每个节点给出原价 w 和 折扣额，c[i] = w[i] - 折扣额 为用券后的折扣价。输入的父节点 u 表示 i 挂在 u 之下。
注意这里 c[1] = w[1] - rd()，说明根节点也有折扣
对整个树（根 1），从 i = n 往下找第一个"能用 ≤m 预算买 i 件"的数量，这就是答案（最多可买件数）。

f[1][i][0]：根不用券买 i 件的最小花费
f[1][i][1]：根用券买 i 件的最小花费
任一 ≤ m 即可行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5005;

struct node {
    int cnt, to[N]{}, nxt[N]{}, head[N]{};
    node() { cnt = 0; }
    void add(int u, int v) {
        to[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
    }
} e;

int sz[N], f[N][N][2], w[N], c[N];
inline void dfs(int u) {
    sz[u] = 1; f[u][0][0] = 0; f[u][1][0] = w[u], f[u][1][1] = c[u];
    for (int i = e.head[u]; i; i = e.nxt[i]) {
        int v = e.to[i]; dfs(v);
        for (int j = sz[u]; j >= 0; --j)
            for (int k = sz[v]; k >= 0; --k) {
                f[u][j+k][0] = min(f[u][j+k][0], f[u][j][0]+f[v][k][0]);
                f[u][j+k][1] = min({f[u][j+k][1], f[u][j][1]+f[v][k][0], f[u][j][1]+f[v][k][1]});
            }
        sz[u] += sz[v];
    }
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

inline void out(int x, char ch) { write(x); putchar(ch); }

int n, m;
inline void init() {
    n = rd(), m = rd();
    memset(f, 0x3f, sizeof f);
    w[1] = rd(), c[1] = w[1] - rd();
    for (int i = 2; i <= n; ++i) {
        w[i] = rd(); c[i] = w[i] - rd();
        int u = rd();
        e.add(u, i);
    }
}
inline void solve() {
    dfs(1);
    for (int i = n; i >= 0; --i)
        if (f[1][i][0] <= m || f[1][i][1] <= m) {
            out(i, '\n');
            break;
        }
}

int main() {
    fast;
    int t = 1;
    while (t--) { init(); solve(); }
    return 0;
}
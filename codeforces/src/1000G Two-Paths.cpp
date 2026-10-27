//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
链式前向星存无向加权树，每条边存 (to, c)，双向各存一条
后序遍历，先算子树再算父。
f[x] = a[x]：从 x 出发、只在 x 自己的子树内能获得的最大收益（先把自身点权计入）。
对每个孩子 v：走边 (x,v) 到 v 的代价是 2c（过去再回来，或单向下探的成本），若 f[v]-2c > 0 就"值得去"，累加入 f[x]；否则 max(...,0)=0（不去）。
g[v]：换根的核心。f[x] 是所有子分支贡献之和，把 v 那一支扣掉 (-max(f[v]-2c,0)) 就是"去掉 v 分支后 x 这边的收益"，记为 g[v]（即 v 的父亲方向能带给 v 的收益）
C[x] = 连接 x 与其父亲的边权 c（用于路径累加时扣边代价）。
sum[x][i]：倍增表，表示从 x 向上跳 2^i 步这段路径上 (g[节点]-C[节点]) 的累加和。也就是"祖先方向贡献的路径和"。sum[x][0]=g[x]-C[x]（x 本身在换根框架下的净贡献减掉接父边的代价）。
h[v]：从 v 出发沿祖先方向累积的收益——由"父的 h"+"父这边换根收益 f"+"减去 v 分支"再减边代价 2c 递推，且不取负则截断为 0（max(...,0)）。
同时构建 fa[][i]（倍增祖先）与 sum[][i]（倍增路径和），为 O(log) 查询做准备。
至此我们有了：

f[x]：从 x 在子树内走的收益。
h[x]：从 x 往上走（祖先方向）的累计收益。
sum 倍增表：任意一条祖先方向路径的上行收益之和
jump：二进制拆分向上跳。
get：返回从 u 向上跳 d 步这段路径的 sum 累加和（祖先方向收益）。
LCA：标准倍增求法
这是整个问题的核心答案公式，按 u、v 相对 LCA t 的位置分成三种情况：

u == v：答案 = h[u] + f[u]（从 u 出发，既能往祖先方向又能往子树方向，两方向收益相加）。
v 是 u 的祖先（v == t）：路径就是 v → … → u 一条竖线。用 get(u, dep[u]-dep[t]-1) 取 u 到 t 下方那段的祖先方向收益，再加上 t 到 v 方向的调整、以及 f[u]（u 的子树收益），并扣除接边代价 C[x]（x 是 u 路径上第一个点）。
u、v 分属 LCA 两侧：路径跨越 t。思想是 总收益 = t 为中心，左(u)方向 + 右(v)方向 + t 自身的收益。公式把 h[t]+f[t] 作基点，分别减去/加上两分支的换根调整项 —max(f[x]-2C[x],0)、—C[x]、—C[y]，再加上两段 get(...) 祖先方向路径和，最后加 f[u]+f[v]。
本质是：用换根 DP 的 f/g/h 把"每个点在不同朝向下的子树收益"都算出来，再用倍增把"沿路径的贡献"累加成 O(log n) 的答案
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

constexpr int N = 6e5+5;

struct edge { int nxt, to, c; } e[N<<1];

int cnt, head[N];
void add(int u, int v, int c) {
    e[++cnt] = {head[u], v, c}, head[u] = cnt;
}

ll f[N], g[N];
int a[N];
void dfs(int x, int ff) {
    for (int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == ff) continue;
        dfs(v, x);
    }
    f[x] = a[x];
    for (int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].to, c = e[i].c;
        if (v == ff) continue;
        f[x] += max(f[v]-c-c, 0ll);
    }
    for (int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].to, c = e[i].c;
        if (v == ff) continue;
        g[v] = f[x] - max(f[v]-c-c, 0ll);
    }
}

int dep[N], fa[N][20], C[N], lg[N];
ll sum[N][20], h[N];
void dfs2(int x, int ff) {
    dep[x] = dep[ff] + 1, fa[x][0] = ff, sum[x][0] = g[x] - C[x];
    for (int i = 1; i <= lg[dep[x]]; ++i)
        fa[x][i] = fa[fa[x][i-1]][i-1], sum[x][i] = sum[x][i-1] + sum[fa[x][i-1]][i-1];
    for (int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].to, c = e[i].c;
        if (v == ff) continue;
        h[v] = max(h[x]+f[x]-max(f[v]-c-c, 0ll)-c-c, 0ll);
        C[v] = c;
        dfs2(v, x);
    }
}
int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = lg[dep[x]]; i >= 0; --i)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (int i = lg[dep[x]]; i >= 0; --i)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
int jump(int u, int d) {
    for (int i = lg[d]; i >= 0; --i)
        if (d>>i&1) u = fa[u][i];
    return u;
}
ll get(int u, int d) {
    ll ans = 0;
    for (int i = lg[d]; i >= 0; --i)
        if (d>>i&1) ans += sum[u][i], u = fa[u][i];
    return ans;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, q;
int main() {
    read(n); read(q);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1, u, v, c; i < n; ++i)
        read(u), read(v), read(c), add(u, v, c), add(v, u, c);
    dfs(1, 0); dep[0] = -1, lg[1] = 0;
    for (int i = 2; i <= n; ++i) lg[i] = lg[i>>1]+1;
    dfs2(1, 0);
    while (q--) {
        int u, v; read(u); read(v);
        if (dep[u] < dep[v]) swap(u, v);
        ll ans = 0;
        int t = LCA(u, v);
        if (u == v) ans = h[u] + f[u];
        else if (v == t) {
            int x = jump(u, dep[u]-dep[t]-1);
            ans = h[t]+f[t]-max(f[x]-C[x]-C[x], 0ll) + get(u, dep[u]-dep[t]-1) + f[u] - C[x];
        } else {
            int x = jump(u, dep[u]-dep[t]-1), y = jump(v, dep[v]-dep[t]-1);
            ans = h[t]+f[t]-max(f[x]-C[x]-C[x], 0ll) - max(f[y]-C[y]-C[y], 0ll) - C[x] - C[y];
            ans += get(u, dep[u]-dep[t]-1) + get(v, dep[v]-dep[t]-1) + f[u] + f[v];
        }
        write(ans), putchar('\n');
    }
    return 0;
}
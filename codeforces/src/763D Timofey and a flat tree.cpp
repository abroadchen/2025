//
// Created by Psy.C on 2026/9/6.
//
/**
初始状态 DP (dfs)
采用后序遍历（从叶子到根），为每个节点计算两个核心属性：
sz[u]：以u为根的子树规模（包括u本身）。
ha[u]：节点u的哈希值，反映了其子树结构
累加子树哈希：ha[u] = mo(ha[u] + ha[v])将所有子节点的哈希值相加。
乘以子树规模：ha[u] * sz[u]放大了子树的影响力。
加权求和：pri[sz[u]]是一个预处理的权重（i*i % mod），加入到哈希中，使得不同规模的子树产生差异化的哈希

Rerooting 预处理 (dfs1)
模拟换根操作，即把树的根从u移动到v时，u和v的哈希值如何变化。它记录了四个状态值：
I[v][0]：原来的父节点u的哈希值（换根前）。
I[v][1]：原来的子节点v的哈希值（换根前）。
I[v][2]：换根后新的父节点u的哈希值。
I[v][3]：换根后新的子节点v的哈希值。

最终答案搜索 (dfs2)
对所有节点的四个状态值进行离散化（坐标压缩），然后使用滑动窗口技巧维护一个计数器，找到出现次数最多的节点
add(pos) / del(pos)：维护一个频率数组sum[pos]，以及一个计数器no记录当前非零频率的种类数。
lower_bound：由于所有状态值已经被排序并去重（坐标压缩），这里通过二分查找获取离散化后的下标。
最终，变量ans即为满足条件的最佳节点编号
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5+5, mod = 1e9+7;

struct edge {
    int v, nxt;
    edge(int v=0, int nxt=0) : v(v), nxt(nxt) {}
} e[N<<1];

int num, head[N];
void adde(int u, int v) {
    e[++num] = {v, head[u]}, head[u] = num;
}

//确保数值始终保持在 [0, mod-1] 范围内
int mo(const int x) { return x >= mod ? x - mod : x; }

int sz[N], ha[N], pri[N];
void dfs(int u, int fa) {
    sz[u] = 1; ha[u] = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        ha[u] = mo(ha[u] + ha[v]);
    }
    ha[u] = mo(1ll*ha[u]*sz[u]%mod + pri[sz[u]]);
}

//计算模意义下的指数运算。这里主要用于计算模逆元（a^(mod-2) % mod）
int pw(int a, int x) {
    int res = 1;
    while (x) {
        if (x&1) res = 1ll*res*a%mod;
        a = 1ll*a*a%mod;
        x >>= 1;
    }
    return res;
}

int I[N][4];
void dfs1(int u, int fa) {
    int hu = ha[u], su = sz[u];
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        I[v][0] = ha[u]; I[v][1] = ha[v];//记录原始状态
        //移除 v 对 u 的贡献
        //更新 u 的子树规模
        //重新计算 u 的哈希值
        //将 v 的子树挂在 u 上作为父节点
        ha[u] = mo(mod-ha[v]+1ll*mo(mod-pri[sz[u]]+ha[u])*pw(sz[u], mod-2)%mod);
        sz[u] -= sz[v];
        ha[u] = mo(1ll*ha[u]*sz[u]%mod + pri[sz[u]]);
        ha[v] = 1ll*mo(mod-pri[sz[v]]+ha[v])*pw(sz[v], mod-2)%mod;
        sz[v] += sz[u];
        ha[v] = mo(1ll*mo(ha[v]+ha[u])*sz[v]%mod + pri[sz[v]]);
        I[v][2] = ha[u]; I[v][3] = ha[v];//记录新状态
        dfs1(v, u);
        ha[u] = hu, sz[u] = su;//恢复现场
    }
}

int no, sum[N*5];
void add(int pos) { no += !(sum[pos]++); }
void del(int pos) { no -= !(--sum[pos]); }

int ox[N*5], cnt, mx, ans;
void dfs2(int u, int fa) {
    if (fa) {
        //移除父节点的旧状态
        del(lower_bound(ox, ox+cnt, I[u][0]) - ox);
        del(lower_bound(ox, ox+cnt, I[u][1]) - ox);
        //添加父节点的新状态
        add(lower_bound(ox, ox+cnt, I[u][2]) - ox);
        add(lower_bound(ox, ox+cnt, I[u][3]) - ox);
    }
    //检查当前不同状态的数量是否最多
    if (no > mx) mx = no, ans = u;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        dfs2(v, u);
    }
    if (fa) {
        //回溯恢复现场
        add(lower_bound(ox, ox+cnt, I[u][0]) - ox);
        add(lower_bound(ox, ox+cnt, I[u][1]) - ox);
        del(lower_bound(ox, ox+cnt, I[u][2]) - ox);
        del(lower_bound(ox, ox+cnt, I[u][3]) - ox);
    }
}

template<class T>
void rd(T& x) {
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

int cp[N];
int main() {
    int n; rd(n);
    for (int i = 1; i <= n; ++i) pri[i] = 1ll*i*i%mod;
    for (int i = 1, u, v; i < n; ++i) {
        rd(u), rd(v);
        adde(u, v); adde(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) ox[cnt++] = cp[i] = ha[i];
    dfs1(1, 0);
    for (int i = 1; i <= n; ++i)
        for (int t = 0; t < 4; ++t)
            ox[cnt++] = I[i][t];
    sort(ox, ox+cnt);
    cnt = unique(ox, ox+cnt) - ox;
    for (int i = 1; i <= n; ++i)
        add(lower_bound(ox, ox+cnt, cp[i]) - ox);
    dfs2(1, 0);
    write(ans), putchar('\n');
    return 0;
}
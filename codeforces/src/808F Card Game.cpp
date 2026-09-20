//
// Created by Psy.C on 2026/9/20.
//
/**
vis[j] = 1 表示 j 是合数；vis[j] = 0 表示 j 不是合数（是素数或 0/1）
tot = 等级 ≤ x 的卡数量，存入数组 b[1..tot]。
MF::build() 建网络流图，MF::dinic() 求最大流。
判断 sm - 最大流 >= m：sm 是所有候选卡价格总和（在 build 里算），减去最大流 = 最多能凑出多少个组合的价值。若 ≥ m，则可行
(1) 奇偶正确性

要让两个数之和为素数，除 2 以外素数都是奇数，所以一奇一偶之和才可能是素数（奇+偶=奇）。
于是建图时：奇数值卡（c&1 且 c>1，排除 1 单独处理）向偶数值卡（-c&1）连边，条件是 !vis[c_i+c_j]（和不是合数，即和为素数）。
容量 inf：表示这两张卡可以配对。
(2) 数值=1 的特判

数值 1 很特殊：1 + 偶数 = 奇数，且 1 不是素数也不是合数，1+x 要为素数需 x+1 为素数。
数值 1 的卡单独处理：ps 指向价格最大的一张 1 卡，让这张 1 卡连向所有"1+偶数 为素数"的偶数卡。
之所以只连价格最大的那张：数值 1 的卡里只需一个代表去和偶数配对（因为 1+1=2 也是素数，但题目可能限制），这里只连一张来优化。
(3) 源点/汇点连接（割 = 价值损失）‍

奇数卡连向源 S（容量=价格 p），偶数卡连向汇 T（容量=价格 p）。
sm 累加所有参与连线的卡的价格总和。
因为这是"最小割"模型：为了让两边平衡，割掉的边容量 = 被牺牲/放弃的卡价格。sm - 最大流 = 最大能保留的组合数（对应最少放弃的价格）。
标准 Dinic 最大流算法：bfs 建层次图，dfs 多路增广，cur[] 当前弧优化。
返回最大流 = 最小割容量。
模型本质： 这是一个"二部图最大权匹配/最小割"——选出尽量多的"和为素数"的卡对，同时保留卡价格。sm - 最大流 就是不割掉（保留）的边权重，用于判断能否凑 m 对。
二分最小可行等级 x：check(x) 为真则记录 rs=mid 并往左搜（找更小等级），否则往右。
若 rs 从未更新（> n），说明等级取满也凑不出 m 个组合 → 输出 -1。
否则输出最小可行等级 rs
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 105, M = 2e5+5, inf = 2e5+5;
struct node { int p, c, l; } a[N], b[N];

int ps, sm, tot, vis[M];
namespace MF {
    struct edge { int to, w, nxt; } e[N<<1];
    int head[N], id;
    void Add(int u, int v, int w) {
        e[++id] = {.to = v, .w = w, .nxt = head[u]}, head[u] = id;
    }
    void add(int u, int v, int w) { Add(u, v, w); Add(v, u, 0); }
    int S, T;
    void build() {
        ps = sm = 0; id = 1; S = tot+1, T = tot+2, memset(head, 0, sizeof head);
        for (int i = 1; i <= tot; ++i)
            if ((b[i].c&1) && b[i].c > 1)
                for (int j = 1; j <= tot; ++j)
                    if ((~b[j].c&1) && !vis[b[i].c+b[j].c]) add(i, j, inf);
        for (int i = 1; i <= tot; ++i)
            if (b[i].c == 1 && b[i].p > b[ps].p) ps = i;
        for (int i = 1; i <= tot; ++i)
            if ((~b[i].c&1) && !vis[b[i].c+1]) add(ps, i, inf);
        for (int i = 1; i <= tot; ++i)
            if (b[i].c > 1 || i == ps)
                sm += b[i].p, b[i].c&1 ? add(S, i, b[i].p) : add(i, T, b[i].p);
    }
    int dep[N];
    int bfs() {
        queue<int> q; q.push(S), memset(dep, 0, sizeof dep), dep[S] = 1;
        for (int u; !q.empty();) {
            u = q.front(); q.pop();
            for (int i = head[u], v; i; i = e[i].nxt)
                if (!dep[v=e[i].to] && e[i].w) {
                    dep[v] = dep[u] + 1;
                    q.push(v);
                    if (v == T) return 1;
                }
        }
        return 0;
    }
    int cur[N];
    int dfs(int u, int sum) {
        if (u == T) return sum;
        int v, res = 0, tmp;
        for (int& i = cur[u]; i&&sum; i = e[i].nxt)
            if (dep[v=e[i].to] == dep[u]+1 || !e[i].w)
                tmp = dfs(v, min(sum, e[i].w)), sum -= tmp, res += tmp, e[i].w -= tmp, e[i^1].w += tmp;
        return res;
    }
    int dinic() {
        int res = 0;
        while (bfs())
            memcpy(cur, head, sizeof head), res += dfs(S, inf);
        return res;
    }
};

int n, m;
int check(int x) {
    tot = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i].l <= x) b[++tot] = a[i];
    MF::build();
    return sm - MF::dinic() >= m;
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

int rs;
int main() {
    n = rd(), m = rd(), rs = n+1;
    for (int i = 1; i <= n; ++i) a[i] = {.p = rd(), .c = rd(), .l = rd()};
    for (int i = 2; i <= M-5; ++i)
        for (int j = i*2; j <= M-5; j += i) vis[j] = 1;
    for (int l = 1, r = n, mid; l <= r; )
        check((mid = (l+r)>>1)) ? r = (rs = mid)-1 : l = mid+1;
    write(rs > n ? -1 : rs), putchar('\n');
    return 0;
}
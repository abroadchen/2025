//
// Created by Psy.C on 2026/9/27.
//
/**
用链式前向星存无向图（每条边存两次，正向和反向），head[x] 指向点 x 的第一条出边，nxt 串起同点的边
经典线性基：把任意整数 x 表示成基的异或组合。逐位从高位到低位：
若 x 的第 i 位为 1，且基的第 i 位 p[i] 为空，就存入并结束；
否则 x ^= p[i] 消去该位，继续。
线性基的集合可以线性组合出原集合能异或出的所有值。这里 p[0..30] 处理 31 位以内的整数
从点 1 出发做 DFS，记录到每个点的一条简单路径的异或和 dis[x]。
当走到某条边 (x,y,w) 时：
若 y 还没被访问，就标记并递归 dfs(y, val ^ w)，把它作为生成树边（val^w 是到 y 的新异或距离）；
若 y 已经被访问过（说明这条边形成环），就把这个环的异或值 val ^ w ^ dis[y] 插入线性基 insert(...)。
核心思想：任意一条从 1 到 n 的路径的异或和，都可以表示成「生成树上 1→n 的异或距离 dis[n]」异或上「若干条环的异或值」。这些环的异或值全都收集进线性基，线性基能组合出所有可能的环异或组合。
读入 n、m 和随后 m 条边 (a, b, c)（自己写的快速读入 rd()）。
建图后从 1 开始 DFS，得到 dis 和线性基。
用线性基对最终答案做贪心最大化：从高位到低位，若 dis[n] ^ p[i] 比当前 dis[n] 更大，就异或上 p[i]，逐步把答案二进制高位尽量顶到 1。
输出最终 dis[n]，即最大异或和路径
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

struct edge { int to, nxt, w; } e[N<<1];
int cnt(1), head[N];
void add(int x, int y, int z) {
    e[++cnt].to = y; e[cnt].w = z; e[cnt].nxt = head[x]; head[x] = cnt;
    e[++cnt].to = x; e[cnt].w = z; e[cnt].nxt = head[y]; head[y] = cnt;
}

int p[70];
void insert(int x) {
    for (int i = 30; i >= 0; --i) {
        if ((x>>i)&1) {
            if (!p[i]) { p[i] = x; return; }
            x ^= p[i];
        }
    }
}

int dis[N], vis[N];
void dfs(int x, int val) {
    dis[x] = val;
    for (int i = head[x]; i; i = e[i].nxt) {
        int y = e[i].to;
        if (!vis[y]) {
            vis[y] = 1;
            dfs(y, val^e[i].w);
        }
        else insert(val^e[i].w^dis[e[i].to]);
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    fast;
    int n = rd(), m = rd();
    for (int i = 1, a, b, c; i <= m; ++i) {
        a = rd(), b = rd(), c = rd();
        add(a, b, c);
    }
    vis[1] = 1; dfs(1, 0);
    for (int i = 30; i >= 0; --i)
        if ((dis[n]^p[i]) < dis[n])
            dis[n] ^= p[i];
    cout << dis[n] << '\n';
    return 0;
}
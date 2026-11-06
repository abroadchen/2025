//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
链式前向星建树（无向边，加两次）
沿树往下（避开父亲）‍深度优先搜索，找到第一个遇到的目标节点（mx[y] 为标记的 A 集点）就立即返回，否则递归并向上传递。mx[] 是全局标记数组
题目给两个集合 A、B（大小 k1、k2），需通过询问判定它们之间的最近距离关系
先问 B b[1]，得到最近的 B 集合节点 x。
若 x 恰是 A 集合成员 → 直接输出 C x（答案就是它）。
否则从 x 出发 dfs 找最近的 A 节点 y（dfs 首次命中）。
问 A y，返回最近 A 节点 x。
若该节点在 B 集合（my[x]）→ 答案 y；否则 -1（无解/不可达）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 10010;
struct node { int x, y, n; } d[N<<1];

int k, h[N];
void add(int x, int y) {
    d[++k].x = x; d[k].y = y; d[k].n = h[x]; h[x] = k;
}

int mx[N];
int dfs(int x, int fa) {
    int g, y, z;
    for (g = h[x]; g; g = d[g].n) {
        y = d[g].y;
        if (y == fa) continue;
        if (mx[y]) return y;//若 y 是 A 集合节点（mx[y]=1）返回它
        z = dfs(y, x);
        if (z) return z;
    }
    return 0;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int my[N];
void init() {
    memset(h, 0, sizeof(h));
    memset(d, 0, sizeof(d));
    memset(mx, 0, sizeof(mx));
    memset(my, 0, sizeof(my));
    k = 0;
}

int T, n, u, v, k1, k2, a[N], b[N], x, y;
int main() {
    fast;
    T = rd();
    while (T--) {
        n = rd(); init();
        rep(i,n-1) u = rd(), v = rd(), add(u, v), add(v, u);
        k1 = rd();
        rep(i,k1) mx[a[i]=rd()] = 1;
        k2 = rd();
        rep(i,k2) my[b[i]=rd()] = 1;
        cout << "B " << b[1] << endl;
        cin >> x;
        if (x == -1) break;
        if (mx[x]) cout << "C " << x << endl;
        else {
            y = dfs(x, 0);
            cout << "A " << y << endl;
            cin >> x;
            if (x == -1) break;
            cout << "C " << (my[x]?y:-1) << endl;
        }
    }
    return 0;
}
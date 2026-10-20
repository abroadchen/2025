//
// Created by Psy.C on 2026/10/20.
//
/**
经典线段树点更新：在位置 y 写入值 z，并沿途把路径上每个节点 mx 都更新成 max(原, z)。
因为是"取 max"型，mx 表示该区间内所有已插入位置对应的最大值。
注意：这里没有做路径复制（版本分离）‍——tr[x].l/tr[x].r 直接原地修改，所以实际上这是一个可复用多棵根但共享节点的"前缀树"式写法，rt[] 数组里每个成员是对应某一棵树的根，节点会被多棵树共享
查询 [1, k]（即前 k 个位置）内的最大值。
从左到右递归求前缀 max，等同于 rmq 前 k 个位置的最大值。
结合 add 在位置 y 存值，query(..., z-1) 就是在查"所有已插入、且位置 < z 的节点的最大值"
每一轮 i：
query(1, N-5, rt[x], z-1)：从"根为 rt[x]"的树上，查所有已插入中位置 ≤ z-1 的最大 dp 值。
dp[i] = 该值 + 1：这是在"延续"此前以某种条件（与 x、z 关联）结尾的最长链，长度 +1。
add(1, N-5, rt[y], z, dp[i])：把 dp[i] 以位置 z 插入到"根为 rt[y]"的树上（用于后续以 y 为起点/终点的查询）。
s = max(s, dp[i])：全局最长长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

struct node { int l, r, mx; } tr[N*20];

int cnt;
void add(int l, int r, int &x, int y, int z) {
    if (!x) x = ++cnt;
    tr[x].mx = max(tr[x].mx, z);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (mid >= y) add(l, mid, tr[x].l, y, z);
    else add(mid+1, r, tr[x].r, y, z);
}
int query(int l, int r, int x, int k) {
    if (l == r) return tr[x].mx;
    int mid = (l + r) >> 1;
    if (k <= mid) return query(l, mid, tr[x].l, k);
    return max(tr[tr[x].l].mx, query(mid+1, r, tr[x].r, k));
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, m, x, y, z, s, dp[N], rt[N];
int main() {
    fast;
    read(n); read(m);
    for (int i = 1; i <= m; ++i) {
        read(x), read(y), read(z);
        dp[i] = query(1, N-5, rt[x], z-1) + 1;
        add(1, N-5, rt[y], z, dp[i]);
        s = max(s, dp[i]);
    }
    cout << s << '\n';
    return 0;
}
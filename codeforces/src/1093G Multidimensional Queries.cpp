//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
k 最多到 5（因为 2^k ≤ 32）。
tr[x][s]：线段树节点 x，在符号掩码 s 下的最优值
对每个符号掩码 s，父节点取左右儿子中的较大值（因为查询关心区间内最大的带符号和）
到达叶子（单个位置）时，根据当前 t[] 重算该点的所有 2^k 组合值：
s 的第 i 位 = 1 → 加 t[i]；
= 0 → 减 t[i]。
对每个 s，tr[leaf][s] = 该点向量按 s 的带符号和。
更新后沿路径 push_up 向上维护
区间完全覆盖时，把该节点每个 tr[x][s] 与全局累加器 t[s] 取 max，存回 t[s]。
t[s] 因此在一次查询结束时 = 整个查询区间内，符号掩码 s 的最大带符号和
初始化：所有 tr 和 t 置为 -inf。
建树：读入每个位置的 k 维向量，update 到线段树。
操作 1（单点改）‍：读入位置 p 的新 k 维向量，update(p)。
操作 2（区间查询）‍：
memset(t, -inf) 清空累加器；
query(1,n,l,r,1) 得到区间内各 s 的最大带符号和（存在 t[s]）；
枚举 s，t[s] + t[mask ^ s]（两个互补掩码），取最大值作为答案。
物理意义（此类经典题的直觉）：把每个点看作 k 维向量，tr[s] 是在"第 i 维取正/负"这个投影方向上的最大投影值；互补 s 与 mask^s 是两个相反方向的投影，两者和最大对应"区间内一对向量在相反方向上的跨度最大"
*/
#include <bits/stdc++.h>
#define rep(i,n) for(int i=1;i<=n;i++)
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 2e5+5, inf = 2e9;

int k, tr[N<<2][32];
void push_up(int x) {
    for (int s = 0; s <= (1<<k)-1; s++)
        tr[x][s] = max(tr[x<<1][s], tr[x<<1|1][s]);
}

int t[32];
void update(int l, int r, int p, int x) {
    if (l == r) {
        memset(tr[x], 0, sizeof tr[x]);
        for (int s = 0; s <= (1<<k)-1; s++) rep(i,k) {
            if ((s>>(i-1))&1) tr[x][s] += t[i];
            else tr[x][s] -= t[i];
        }
        return;
    }
    if (p <= mid) update(l,mid,p,x<<1);
    else update(mid+1,r,p,x<<1|1);
    push_up(x);
}
void query(int l, int r, int L, int R, int x) {
    if (L <= l && r <= R) {
        for (int s = 0; s <= (1<<k)-1; s++)
            t[s] = max(t[s], tr[x][s]);
        return;
    }
    if (L <= mid) query(l,mid,L,R,x<<1);
    if (R > mid) query(mid+1,r,L,R,x<<1|1);
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

int n, q;
int main() {
    n = rd(), k = rd();
    rep(i,n<<2) for (int j = 0; j <= (1<<k)-1; j++) tr[i][j] = t[j] = -inf;
    rep(i,n) {
        rep(j,k) t[j] = rd();
        update(1,n,i,1);
    }
    q = rd();
    while (q--) {
        int op = rd();
        if (op == 1) {
            int p = rd();
            rep(i,k) t[i] = rd();
            update(1,n,p,1);
        } else {
            int l = rd(), r = rd();
            memset(t,-0x3f, (1<<k)*sizeof(int));
            query(1,n,l,r,1);
            int res = 0;
            for (int s = 0; s <= (1<<k)-1; s++)
                res = max(res, t[s]+t[((1<<k)-1)^s]);
            write(res), putchar('\n');
        }
    }
    return 0;
}
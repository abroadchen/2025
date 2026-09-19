//
// Created by Psy.C on 2026/9/19.
//
/**
把一个 n 长的数组复制 nn/n = nn/n 次得到长度为 nn 的周期序列，然后做：

操作1：把区间 [l,r] 赋值为 x（整体覆盖成常数）。
操作2：查询区间 [l,r] 的最小值。
由于 nn 可能很大（n*倍数），不能直接开完整线段树，所以用动态开点 + 懒标记。

先看几个关键量：

n：基础周期长度，f[0][1..n] 是原始数组。
nn = rd()*n：总长度（nn/n 倍复制周期）。
线段树维护区间为 [1, nn]。

标准 ST 表 RMQ（区间最小值）。
f[len][j] 记录以 j 开头的 2^len 长度的最小值
lg[i]：对数下取整表。
ST 建表。
pre[i]：min(f[0][1..i]) 原数组前缀最小值。
suc[i]：min(f[0][i..n]) 原数组后缀最小值。
mn：整个周期数组的最小值。
这些是为"覆盖整个周期"时能快速回答区间最小值：当查询区间横跨多个完整周期时，不必逐点查。
若区间长度 ≥ n，必然完整覆盖某个周期，其最小值 = 整个周期最小值 mn。
否则定位首尾周期：
同一周期：ST 查询周期内 [l-L, r-L]。
跨周期：最小值 = 首周期右端后缀最小值 ∪ 末周期左端前缀最小值。
关键：不操作（未被 update 覆盖）的区间，其值就是原始周期数组的对应值，可用上面的 RMQ 快速得到，无需真的开点
首次访问某节点时开点，并把该节点值设为基于原始周期数组的区间最小（用上面的 query，这是"未赋值时的缺省值"）
tag：懒标记（区间赋值）。
push_up(rot, w) = 节点和标记都设为 w（赋值）。
push_down：把标记下推到两个儿子（必要时动态开儿子点）
标准线段树区间赋值：
全包含 → 打标记 push_up（整段变 w）。
否则下推标记、递归两儿子、再 min 合并
区间最小值查询，动态开点 + 下推标记，标准拆分合并

读入基础周期 n 个元素，build。
总长 nn = 周期倍数 * n。
a[0].w = inf 作为空儿子哨兵（min 时安全）。
依次处理 q 个操作
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5, inf = 2e9;
struct node { int w, ch[2]; } a[N<<6];

int lg[N], f[20][N];
int st_query(int l, int r) {
    int len = lg[r-l+1];
    return min(f[len][l], f[len][r-(1<<len)+1]);
}

int n, pre[N], suc[N], mn;
void build() {
    lg[1] = 0;
    for (int i = 2; i <= n; ++i) lg[i] = lg[i>>1]+1;
    for (int i = 1; 1<<i <= n; ++i)
        for (int j = 1; j+(1<<i)-1 <= n; ++j)
            f[i][j] = min(f[i-1][j], f[i-1][j+(1<<(i-1))]);
    pre[1] = f[0][1];
    for (int i = 2; i <= n; ++i) pre[i] = min(pre[i-1], f[0][i]);
    suc[n] = f[0][n];
    for (int i = n-1; i >= 1; --i) suc[i] = min(suc[i+1], f[0][i]);
    mn = pre[n];
}
int query(int l, int r) {
    if (r-l+1 >= n) return mn;
    int bl = (l-1)/n+1, br = (r-1)/n+1;
    if (bl == br) {
        int L = (bl-1)*n;
        return st_query(l-L, r-L);
    }
    int L = (bl-1)*n, R = (br-1)*n;
    return min(suc[l-L], pre[r-R]);
}

int cnt;
void get(int& rot, int lt, int rt) {
    rot = ++cnt;
    a[rot].w = query(lt, rt);
}

int tag[N<<6];
void push_up(int rot, int w) { a[rot].w = tag[rot] = w; }
void push_down(int rot) {
    if (tag[rot]) {
        int t = tag[rot]; tag[rot] = 0;
        if (!a[rot].ch[0]) a[rot].ch[0] = ++cnt;
        if (!a[rot].ch[1]) a[rot].ch[1] = ++cnt;
        push_up(a[rot].ch[0], t);
        push_up(a[rot].ch[1], t);
    }
}
void update(int& rot, int lt, int rt, int lq, int rq, int w) {
    if (!rot) get(rot, lt, rt);
    if (lt > rq || rt < lq) return;
    if (lt >= lq && rt <= rq) { push_up(rot, w); return; }
    push_down(rot);
    int mid = (lt+rt)>>1;
    update(a[rot].ch[0], lt, mid, lq, rq, w);
    update(a[rot].ch[1], mid+1, rt, lq, rq, w);
    a[rot].w = min(a[a[rot].ch[0]].w, a[a[rot].ch[1]].w);
}

int query(int& rot, int lt, int rt, int lq, int rq) {
    if (!rot) get(rot, lt, rt);
    if (lt >= lq && rt <= rq) return a[rot].w;
    int mid = (lt+rt)>>1;
    push_down(rot);
    if (rq <= mid) return query(a[rot].ch[0], lt, mid, lq, rq);
    if (lq > mid) return query(a[rot].ch[1], mid+1, rt, lq, rq);
    return min(query(a[rot].ch[0], lt, mid, lq, mid),
               query(a[rot].ch[1], mid+1, rt, mid+1, rq));
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int nn, q, rt;
int main() {
    n = rd(), nn = rd()*n;
    for (int i = 1; i <= n; ++i) f[0][i] = rd(); build();
    q = rd(); a[0].w = inf;
    for (int i = 1; i <= q; ++i) {
        int opt = rd(), l = rd(), r = rd(), x;
        if (opt == 1) x = rd(), update(rt, 1, nn, l, r, x);
        else printf("%d\n", query(rt, 1, nn, l, r));
    }
    return 0;
}
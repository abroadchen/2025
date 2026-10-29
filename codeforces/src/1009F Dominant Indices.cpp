//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
用链式前向星存无向图：每条边存两方向，cnt 计数。
head[u] 指向 u 的第一条边（头插法），nxt 是同一顶点的下一条边下标。
to[N<<1] 因为无向边每条会 add 两次，故数组开两倍。
init() 置 head 为 -1（表示空链表），cnt=0
mx[p]：节点 p 对应区间内出现次数最大值。
ls/rs[p]：左、右孩子指针（动态开点，不预先建满整棵树，用到才分配节点）。
节点总数：每个叶子（深度）至少一个点，线段树合并下总体约 O(n log n) 级别，开 N*25（约 2500 万）足够
在权值区间 [l,r] 中把深度 k 的计数 +1（mx[叶子]++）。
路径上若节点 p==0（未创建），&p 引用新分配 ++tot。
递归到 k 所在半边，最后 push_up 用两个孩子 mx 取 max 回溯
优先往mx 较大的孩子递归；走到叶子即返回该深度。
注意：l==r 时返回 l；若 p 为空返回 0。这里 mx[ls]>=mx[rs] 说明平局时取左（较小深度）
把树 y 合并进树 x，返回合并后的根。
任一方为空则返回另一方（x+y 即非空者）。
到达叶子则计数相加 mx[x]+=mx[y]（保留 x 为宿主）。
否则分别递归合并左右孩子，再 push_up。
复杂度 O(两树重叠节点数)，总复杂度 O(n log n)
进入节点 x：先算 dep[x]=dep[parent]+1（父深度+1，根为 1）。
遍历每条边，跳过父节点 f。
递归后立即合并子树的线段树到 rt[x]（自底向上的合并）。
所有孩子处理完，再把自身深度 dep[x] 插入到 x 的树中（update），使 rt[x] 覆盖整个子树。
最后 query 得子树内频数最大的深度，减去 dep[x] 存入 a[x]。
顺序注意：update(自身) 在合并所有孩子之后执行，因此 query 能看到整个子树（含自身）的深度分布。rt[x] 最终 = 子树所有深度（含 x 与所有后代）的频数分布
初始化图 → 读入 n → 读 n-1 条无向边（建图）。
从根 1（父为 0）开始 dfs，自底向上合并并求 a[i]。
逐行输出每个节点的 a[i]。
*/
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 1e6+5;

int head[N], nxt[N<<1], to[N<<1], cnt;
void add(int u, int v) {
    to[cnt] = v; nxt[cnt] = head[u]; head[u] = cnt++;
}
void init() { memset(head, -1, sizeof(head)); cnt = 0; }

int mx[N*25], ls[N*25], rs[N*25];
void push_up(int p) { mx[p] = max(mx[ls[p]], mx[rs[p]]); }

int tot;
void update(int &p, int l, int r, int k) {
    if (!p) p = ++tot;
    if (l == r) { mx[p]++; return; }
    if (k <= mid) update(ls[p], l, mid, k);
    else update(rs[p], mid+1, r, k);
    push_up(p);
}

int query(int p, int l, int r) {
    if (!p) return 0;
    if (l == r) return l;
    if (mx[ls[p]] >= mx[rs[p]]) return query(ls[p], l, mid);
    return query(rs[p], mid+1, r);
}

int merge(int x, int y, int l, int r) {
    if (!x || !y) return x + y;
    if (l == r) { mx[x] += mx[y]; return x; }
    ls[x] = merge(ls[x], ls[y], l, mid);
    rs[x] = merge(rs[x], rs[y], mid+1, r);
    push_up(x);
    return x;
}

int dep[N], rt[N], n, a[N];
void dfs(int x, int f) {
    dep[x] = dep[f] + 1;
    for (int i = head[x]; ~i; i = nxt[i]) {
        int y = to[i];
        if (y^f) {
            dfs(y, x);
            rt[x] = merge(rt[x], rt[y], 1, n);
        }
    }
    update(rt[x], 1, n, dep[x]);
    a[x] = query(rt[x], 1, n) - dep[x];
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


int main() {
    init(); n = rd();
    for (int i = 1; i < n; i++) {
        int u = rd(), v = rd();
        add(u, v); add(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) write(a[i]), putchar('\n');
    return 0;
}
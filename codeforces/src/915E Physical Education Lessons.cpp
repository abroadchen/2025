//
// Created by Psy.C on 2026/10/13.
//
/**
读入 m 个操作，每个是 [l, r] 区间、赋值为 k（0 或 1，覆盖/取消）。把 r 先 +1 转成左闭右开 [l, r)，便于按单位段统计长度。收集所有端点 s[] → 排序去重得到离散化坐标（坐标很大的直觉处理方式）
左端第一个坐标前的长度 s[1]-1 与最后一个坐标后的长度 n - s[sz] + 1 是永远不会被任何操作覆盖的固定的总长度基线 ans（因为所有区间都落在 [s[1], s[sz]] 内）。线段树只建在相邻坐标组成的 sz-1 个小区间上
sum：当前节点区间内被覆盖的长度。
val：该区间总的长度（固定值）。
tag：懒标记，-1 表示无待下传标记，1 表示整体覆盖，0 表示整体取消覆盖。
build 时叶子节点 sum = val = s[l+1]-s[l]（该单位段的实际长度），内部节点 val = 左+右，sum 初始等于 val（默认全被覆盖，预留基准）
区间被完全覆盖时直接设 tag：k==1（覆盖）令 sum=0；k==0（取消覆盖）令 sum=val。
否则下传标记、递归更新子树、再 push_up 合并
懒标记下传：把标记传给左右子树，并按标记含义更新其 sum
对每个操作，把 [l, r) 映射成离散化下标 [x, y] 后区间赋值；根节点 tr[1].sum 就是被覆盖的线段内长度，加上固定基线 ans（两端永远不会被覆盖的部分）即为当前整体被覆盖总长度，输出
 */
#include <bits/stdc++.h>
#define lc (cur<<1)
#define rc (cur<<1|1)
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 6e5+5;

struct node { int l, r, k; } a[N>>1];
struct sgt { int sum, val, tag; } tr[N<<2];

inline void push_up(int cur) { tr[cur].sum = tr[lc].sum + tr[rc].sum; }
inline void push_down(int cur, int l, int r) {
    if (tr[cur].tag == -1) return;
    tr[lc].tag = tr[rc].tag = tr[cur].tag;
    if (tr[cur].tag == 1) tr[lc].sum = tr[rc].sum = 0;//覆盖 → 子段 sum=0
    else tr[lc].sum = tr[lc].val, tr[rc].sum = tr[rc].val;//取消 → 子段恢复全长
    tr[cur].tag = -1;
}

int s[N];
inline void build(int cur, int l, int r) {
    tr[cur].tag = -1;
    if (l == r) return tr[cur].sum = tr[cur].val = s[l+1] - s[l], void();
    build(lc, l, mid); build(rc, mid+1, r);
    push_up(cur); tr[cur].val = tr[lc].val + tr[rc].val;
}
inline void update(int cur, int l, int r, int L, int R, int k) {
    if (l >= L && r <= R) {
        tr[cur].tag = k;
        if (k == 1) tr[cur].sum = 0;//覆盖 → 该段 sum 归 0
        else tr[cur].sum = tr[cur].val;//取消覆盖 → 恢复全长
        return;
    }
    push_down(cur, l, r);
    if (mid >= L) update(lc, l, mid, L, R, k);
    if (R > mid) update(rc, mid+1, r, L, R, k);
    push_up(cur);//合并左右子树的 sum
}

int sz;
inline int id(int x) { return lower_bound(s+1, s+1+sz, x) - s; }

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

int n, m, ans;
int main() {
    rd(n), rd(m);
    for (int i = 1; i <= m; ++i) {
        rd(a[i].l), rd(a[i].r), rd(a[i].k); ++a[i].r;
        s[++sz] = a[i].l, s[++sz] = a[i].r;
    }
    sort(s+1, s+1+sz);
    sz = unique(s+1, s+1+sz) - s - 1;
    ans = s[1] - 1 + n - s[sz] + 1; build(1, 1, sz-1);
    for (int i = 1; i <= m; ++i) {
        int x = id(a[i].l), y = id(a[i].r)-1;
        update(1, 1, sz-1, x, y, a[i].k);
        write(tr[1].sum+ans), putchar('\n');
    }
    return 0;
}
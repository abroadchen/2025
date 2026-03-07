//
// Created by Psy.C on 2026/3/7.
//
/**
mx: 18：最大值字段，占用18位
l: 23：左子节点索引，占用23位
r: 23：右子节点索引，占用23位
tr[N*40]：线段树数组
lson：左子节点索引
rson：右子节点索引
lmx：左子树的最大值
rmx：右子树的最大值

对每个元素按权值从大到小处理
计算该元素可以影响的有效区间：[max(1, pos-m+1), min(pos, n-m+1)]
更新可持久化线段树

解密查询参数（异或上一次答案）
使用upper_bound找到权值≥x的元素个数
查询对应版本线段树中区间[l,r]的最大值
输出m减去查询结果
 */
#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ii pair<int, int>
constexpr int N = 2e5+5;
struct node { ull mx: 18, l: 23, r: 23; } tr[N*40];

#define lson tr[o].l
#define rson tr[o].r
#define lmx (l == mid ? int(lson) : int(tr[lson].mx))
#define rmx (mid+1 == r ? int(rson) : int(tr[rson].mx))
int tot;///线段树节点总数
int update(int p, int l, int r, int L, int R) {
    if (l == r) return p + 1;
    int o = ++tot; tr[o] = tr[p];//复制旧版本
    if (L <= l && r <= R) return ++tr[o].mx, o;//更新最大值并返回
    int mid = (l+r)>>1, tag = tr[o].mx - max(lmx, rmx);
    if (L <= mid) lson = update(tr[p].l, l, mid, L, R);
    if (R > mid) rson = update(tr[p].r, mid+1, r, L, R);
    tr[o].mx = max(lmx, rmx); tr[o].mx += tag;
    return o;
}
int query(int o, int l, int r, int L, int R) {
    if (l == r) return o;
    if (L <= l && r <= R) return tr[o].mx;
    int mid = (l+r)>>1, tag = tr[o].mx - max(lmx, rmx), res = 0;
    if (L <= mid) res = max(res, query(lson, l, mid, L, R));
    if (R > mid) res = max(res, query(rson, mid+1, r, L, R));
    return res + tag;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
///n（数组长度）和m（区间长度）
int n, m, rt[N];
ii a[N];
int main() {
    n = rd(), m = rd();
    for (int i = 1; i <= n; ++i)
        a[i].first = -rd(), a[i].second = i;//存储负值（降序排序用），和原位置
    sort(&a[1], &a[n+1]);
    for (int i = 1; i <= n; ++i) {
        int l = max(1, a[i].second-m+1), r = min(a[i].second, n-m+1);
        rt[i] = update(rt[i-1], 1, n-m+1, l, r);
    }
    int q = rd(), ans = 0;
    while (q--) {
        int l = rd(), r = rd(), x = rd(); x ^= ans;
        int id = upper_bound(&a[1], &a[n+1], make_pair(-x, 1e9)) - a - 1;
        printf("%d\n", ans = m - query(rt[id], 1, n-m+1, l, r));
    }
    return 0;
}
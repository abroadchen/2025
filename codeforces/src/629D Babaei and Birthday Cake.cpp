//
// Created by Psy.C on 2026/3/29.
//
/**
n: 圆柱体数量
id[N]: 记录原编号对应的新排序位置 原编号i在排序后的位置
r,h: 读入的半径和高度
a[N]: 存储每个圆柱体的底面积×高

对第一个元素单独处理
对后续元素：查询前面所有更小体积的最大值，然后更新当前状态
f+a[i]表示选择当前圆柱体并叠加之前的最优解
a[i]表示只选择当前圆柱体

O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ld long double
#define pi acos(-1.)
using namespace std;
constexpr int N = 1e5+5, inf = 0x3f3f3f3f3f3f3f3f;

struct sgt {
#define mid ((l+r)>>1)
#define lc rt<<1
#define rc (rt<<1|1)
    ld f[N<<2];
    void build(int rt, int l, int r) {
        f[rt] = -inf;
        if (l == r) return;
        build(lc, l, mid); build(rc, mid+1, r);
    }
    void update(int rt, int l, int r, int pos, ld val) {//在位置pos更新最大值
        if (l == r) {
            f[rt] = max(f[rt], val);
            return;
        }
        if (pos <= mid) update(lc, l, mid, pos, val);
        else update(rc, mid+1, r, pos, val);
        f[rt] = max(f[lc], f[rc]);//维护区间最大值
    }
    ld query(int rt, int l, int r, int L, int R) {//查询[L,R]范围内的最大值
        if (L <= l && r <= R) return f[rt];
        ld res = -inf;
        if (L <= mid) res = query(lc, l, mid, L, R);
        if (mid < R) res = max(res, query(rc, mid+1, r, L, R));
        return res;
    }
#undef mid
#undef lc
#undef rc
} t;

struct node {
    ld val; int id;//圆柱体的体积值和编号
    bool operator<(const node &o) const {
        return val != o.val ? val < o.val : id > o.id;
    }
} b[N];

int n, id[N];
ld r, h, a[N];
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> r >> h;
        a[i] = b[i].val = r*r*h;
        b[i].id = i;
    }
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; ++i) id[b[i].id] = i;
    t.build(1, 1, n);
    t.update(1, 1, n, id[1], a[1]);
    for (int i = 2; i <= n; ++i) {
        ld f = id[i] > 1 ? t.query(1, 1, n, 1, id[i]-1) : -inf;
        t.update(1, 1, n, id[i], max(f+a[i], a[i]));
    }
    printf("%.7Lf\n", t.query(1, 1, n, 1, n)*pi);
    return 0;
}
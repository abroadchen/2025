//
// Created by Psy.C on 2026/9/19.
//
/**
单个叶子代表一个"区间端点"（位置 0..n）。
merge（operator+）把左右儿子的多种候选 min 信息合并。
支持区间加（update2，打懒标记 tg，影响 mn）。
支持单点修改（update，把某个位置置为 inf 后重新 push_up）。
整体作用：在 a[]、b[] 中动态找"最小的 a[i]+b[j] 配对"并支持撤销
va = node{x=左.ma, y=右.mb}：左区间 a 最小 × 右区间 b 最小 的配对，是最常见候选。
vc：交叉配对（右区间 a 最小 × 左区间 b 最小）相关。
vb：维护某种"带条件的配对"，随 mn（区间被选/被屏蔽的程度）动态变化。
都比较依赖全局 a[]、b[]，所以合并时用全局数组比较 a[x.x]+b[x.y]
va 记录"左的a最小、右的b最小"这一类同向配对的最优。
vc 记录交叉配对（右a × 左b）的最优
每次从根节点 t[1] 取全局最优候选配对 (x,y)：
若 va 更优 → 取 va，p=1（正方向）；
否则取 vb，p=-1（反方向，通常用于撤销/反悔上一轮被选的位置）。
ans += a[x]+b[y] 累加答案。
然后把 a[x]、b[y] 置 inf（这两个位置被"占用/消去"），单点更新叶子。
对区间 [min(x,y), max(x,y)-1] 做区间加 p（±1）——这是对这段区间的"被覆盖/可再选"状态做调整，配合 mn 支持"配对后该区间能否继续拆出更优解"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e5+5, inf = 0x3f3f3f3f;
struct node { int x, y; };
struct tree {
    //区间内 a 最小的下标、b 最小的下标
    //与 mn 相关的"次优/边界"候选下标
    //区间额外加的次数/代价（被打懒标记 tg）
    int ma, mb, la, lb, mn, tg;
    node va, vb, vc;//三种候选配对 同向/条件/交叉
} t[N<<2];
int a[N], b[N];
inline bool operator<(node x, node y) {
    return a[x.x] + b[x.y] < a[y.x] + b[y.y];
}
inline tree operator+(tree x, tree y) {
    tree z{}; z.tg = 0;
    if (a[x.ma] < a[y.ma]) z.ma = x.ma; else z.ma = y.ma;
    if (b[x.mb] < b[y.mb]) z.mb = x.mb; else z.mb = y.mb;
    z.mn = min(x.mn, y.mn);
    z.va = min(node{.x = x.ma, .y = y.mb}, min(x.va, y.va));
    z.vc = min(node{.x = y.ma, .y = x.mb}, min(x.vc, y.vc));
    z.vb = min(x.vb, y.vb);
    if (x.mn > y.mn) {
        z.vb = min(z.vb, min(node{.x = y.la, .y = x.mb}, x.vc));
        z.la = (a[x.ma] < a[y.la] ? x.ma : y.la), z.lb = y.lb;
    } else if (y.mn > x.mn) {
        z.vb = min(z.vb, min(node{.x = y.ma, .y = x.lb}, y.vc));
        z.la = x.la, z.lb = (b[y.mb] < b[x.lb] ? y.mb : x.lb);
    } else {
        z.la = x.la, z.lb = y.lb;
        z.vb = min(z.vb, node{.x = y.la, .y = x.lb});
    }
    return z;
}

#define ls (x<<1)
#define rs (x<<1|1)
inline void push_up(int x) { t[x] = t[ls] + t[rs]; }
inline void push_down(int x) {
    if (!t[x].tg) return;
    t[ls].tg += t[x].tg, t[ls].mn += t[x].tg;
    t[rs].tg += t[x].tg, t[rs].mn += t[x].tg;
    t[x].tg = 0;
}
inline void build(int x, int l, int r) {
    if (l == r) return t[x] = {.ma = l, .mb = l, .la = l, .lb = 0, .mn = 0, .tg = 0,
        .va = {.x = l, .y = l}, .vb = {.x = 0, .y = 0}, .vc = {.x = l, .y = l}}, void();
    int mid = (l + r) >> 1;
    build(ls, l, mid); build(rs, mid+1, r);
    push_up(x);
}
inline void update(int x, int l, int r, int p) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    push_down(x);
    if (p <= mid) update(ls, l, mid, p);
    else update(rs, mid+1, r, p);
    push_up(x);
}
inline void update2(int x, int l, int r, int L, int R, int p) {
    if (l > R || L > r) return;
    if (L <= l && r <= R) { t[x].tg += p, t[x].mn += p; return; }
    int mid = (l + r) >> 1;
    push_down(x);
    update2(ls, l, mid, L, R, p);
    update2(rs, mid+1, r, L, R, p);
    push_up(x);
}

ll ans;
int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    a[0] = b[0] = inf; build(1, 0, n);
    while (k--) {
        int x, y, p;
        if (t[1].va < t[1].vb) x = t[1].va.x, y = t[1].va.y, p = 1;
        else x = t[1].vb.x, y = t[1].vb.y, p = -1;
        ans += a[x] + b[y]; a[x] = b[y] = inf;
        update(1, 0, n, x), update(1, 0, n, y);
        update2(1, 0, n, min(x, y), max(x, y)-1, p);
    }
    cout << ans << '\n';
    return 0;
}
//
// Created by Psy.C on 2026/9/15.
//
/**
mx：子树内最大值
cmx：子树内次大值
tg：懒标记（区间全部被改成某值）
初始化 mx=cmx=-inf, tg=-1
mx = 两孩子 mx 中较大者。
cmx = 两孩子 cmx 中较大者，再与"不等于全局 mx 的那个人孩子 mx"取 max。效果：cmx 是严格小于 mx 的最大值（次大值）
若节点有懒标记 tg，则把拥有全局最大 w 的孩子改写成 tg 值（并下传 tg）。只有 mx==w 的孩子才被覆盖，另一个孩子不动。
这是 chmin（区间取 min）的势能线段树下传：因为操作是"把大于某值的都改成更小值"，只有最大值位置受影响
叶子 mx = l（位置 i）。即初始每个位置 i 的"答案值"为 i 本身

这是区间取 min（chmin：把区间内所有 > v 的元素改成 ≤ w 的值）‍。
三段式加速（segment tree beats）：
若整段 mx < v → 没有元素需要改，直接返回（剪枝）。
若整段覆盖且 cmx < v ≤ mx → 只有最大值需要改，且写成整段统一标记 mx=tg=w（势能收敛，一次性处理整段）。
否则递归下钻。
这里的 w 就是要覆盖成的新值（区间编号），v 是比较阈值。注意代码在覆盖分支里 mx(x)=tg(x)=w，但没更新 cmx——因为被改的是"最大值位置"，改后 cmx 不变，仍正确
单点下降到叶子，途中 pushdown 应用懒标记，返回叶子 mx（即该位置的答案）

右端点从 1 扫到 n 作为扫描线指针。
每遇到右端点 i 有区间 [a[i], i]，就对位置区间 [a[i], i] 做一次 chmin 覆盖，把其中所有"当前存的、编号大于 i 的位置值"改成 i —— 即"从当前覆盖区间开始，位置的值 = 最近覆盖它的区间编号"。因为扫描线按右端点递增，后遇到的区间编号更大，chmin 保证只改掉"更大的旧编号"，保留更小的编号。
到右端点 i 时，回答所有挂在 i 上的查询 (x,i)：查位置 x 当前的答案。
于是语义成立：位置 x 在所有覆盖它的区间中，被哪个（编号）区间覆盖。初始每个位置值 = 自己下标，遇到更小编号区间就 chmin 改小，等价于记录"覆盖 x 的区间里最小的编号（最早/最优）"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 2e5+10, inf = 1e9;
struct node {
    int mx, cmx, tg;
    node() { mx = cmx = -inf; tg = -1; }
} t[N<<2];

#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define mx(x) (t[x].mx)
#define cmx(x) (t[x].cmx)
#define tg(x) (t[x].tg)
#define mid ((l+r)>>1)
inline void push_up(int x) {
    mx(x) = max(mx(ls(x)), mx(rs(x)));
    cmx(x) = max(cmx(ls(x)), cmx(rs(x)));
    if (mx(ls(x)) != mx(x)) cmx(x) = max(cmx(x), mx(ls(x)));
    if (mx(rs(x)) != mx(x)) cmx(x) = max(cmx(x), mx(rs(x)));
}
inline void pushdown(int x) {
    if (tg(x) != -1) {
        int w = max(mx(ls(x)), mx(rs(x)));
        if (mx(ls(x)) == w) mx(ls(x)) = tg(ls(x)) = tg(x);
        if (mx(rs(x)) == w) mx(rs(x)) = tg(rs(x)) = tg(x);
        tg(x) = -1;
    }
}
void build(int l, int r, int x) {
    if (l == r) return mx(x) = l, void();
    build(l, mid, ls(x));
    build(mid+1, r, rs(x));
    push_up(x);
}
void modify(int l, int r, int L, int R, int v, int w, int x) {
    if (mx(x) < v) return;
    if (L <= l && r <= R) {
        if (cmx(x) < v && v <= mx(x)) return mx(x) = tg(x) = w, void();
        modify(l, mid, L, R, v, w, ls(x));
        modify(mid+1, r, L, R, v, w, rs(x));
    }
    pushdown(x);
    if (L <= mid) modify(l, mid, L, R, v, w, ls(x));
    if (R > mid) modify(mid+1, r, L, R, v, w, rs(x));
    push_up(x);
}
int query(int l, int r, int v, int x) {
    if (l == r) return mx(x);
    pushdown(x);
    if (v <= mid) return query(l, mid, v, ls(x));
    return query(mid+1, r, v, rs(x));
}

int a[N], ans[N];
vector<ii> q[N];
int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1, l, r; i <= m; ++i)
        cin >> l >> r, a[r] = l;
    int T; cin >> T;
    for (int i = 1, x, y; i <= T; ++i)
        cin >> x >> y, q[y].emplace_back(x, i);
    build(1, n, 1);
    for (int i = 1; i <= n; ++i) {
        if (a[i]) modify(1, n, 1, a[i], a[i], i, 1);
        for (auto [fst, snd] : q[i])
            ans[snd] = query(1, n, fst, 1);
    }
    for (int i = 1; i <= T; ++i) cout << ans[i] << '\n';
    return 0;
}
//
// Created by Psy.C on 2026/9/5.
//
/**
x：横坐标（或时间戳）。
r：半径（或影响范围）。
f：特征值（或颜色、种类等属性）。
a[N]：存储所有节点/点的信息。
ls 与 rs：分别指向左子树和右子树的根节点编号（由于使用了动态开点，这里是节点索引）。
sum：当前区间内点的个数。
t[N<<5]：线段树数组。N<<5 表示 N * 32，因为每次插入都会创建新的路径，最多会有 log(范围) ≈ 30 倍的节点数
p：当前节点的编号（引用传递，以便创建新节点）。
[l, r]：当前节点负责维护的坐标区间。
pos：需要插入点的具体坐标
动态开点：如果当前节点不存在（p == 0），则分配一个新节点（++tot）。
更新计数：该区间内的点数加一（t[p].sum++）。
递归下钻：如果不是叶子节点，则根据 pos 位于左区间还是右区间，递归调用左子树或右子树
p：当前节点编号。
[l, r]：当前节点维护的坐标范围。
[L, R]：查询的目标区间
完全覆盖：如果 [l, r] 完全被 [L, R] 包含，或者节点不存在（说明该区间为空），直接返回当前节点的计数。
部分覆盖：否则，分别递归查询左子树和右子树（如果查询区间与子区间有交集）。
合并结果：返回左右子树查询结果之和

n：点的总数。
k：属性差值的阈值（即我们只关心 |f_i - f_j| <= k 的点对）。
对于每个点，读取其横坐标 x、半径 r（决定查询区间）以及特征值 f
离线排序：
按照半径 r 从大到小进行稳定排序（stable_sort 保证相同 r 的顺序不变）。
这样做的目的是确保当我们处理某个点时，所有已经插入线段树的点的半径都不小于当前点的半径。这对于保证查询的正确性至关重要

rt[j] 表示特征值为 j 的那棵线段树的根节点（对应的是所有已经处理过且 f 为 j 的点）。
使用 query 在这棵树中查询横坐标范围 [x_i - r_i, x_i + r_i]（即圆形或线段的投影区间）内的点数，将其累加到答案 ans 中
调用 add(rt[a[i].f], 0, inf, a[i].x)，将当前点的横坐标 x 插入到特征值为 f_i 的线段树中。这一步是为了后续处理右侧的点时能被统计到

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
constexpr int N = 2e5+5, inf = 2e9;

struct node { int x, r, f; } a[N];
struct tree { int ls, rs, sum; } t[N<<5];

int tot;
inline void add(int &p, ll l, ll r, int pos) {
    if (!p) p = ++tot;
    ++t[p].sum;
    if (l == r) return;
    if (mid >= pos) add(t[p].ls, l, mid, pos);
    else add(t[p].rs, mid+1, r, pos);
}
inline int query(int p, ll l, ll r, int L, int R) {
    if ((L<=l&&r<=R) || !p) return t[p].sum;
    ll res = 0;
    if (mid >= L) res += query(t[p].ls, l, mid, L, R);
    if (mid < R) res += query(t[p].rs, mid+1, r, L, R);
    return res;
}

int n, k, rt[N];
ll ans;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].r >> a[i].f;
    stable_sort(a+1, a+n+1, [](const node &x, const node &y) {
        return x.r > y.r;
    });
    for (int i = 1; i <= n; ++i) {
        for (int j = max(0, a[i].f-k); j <= a[i].f+k; ++j)
            ans += query(rt[j], 0, inf, a[i].x-a[i].r, a[i].x+a[i].r);
        add(rt[a[i].f], 0, inf, a[i].x);
    }
    cout << ans;
    return 0;
}
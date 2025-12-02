//
// Created by Psy.C on 2025/12/2.
//
/*
*n: 元素个数
col[N]: 颜色数组
pos[N]: 位置数组，pos[i]表示颜色i的位置
*mn1: 最小值
mn2: 次小值
sum1: 最小值的个数
sum2: 次小值的个数
tag: 懒惰标记
 *
*l, r: 当前区间左右端点
x: 当前节点编号
*初始化当前节点：
tag, mn1, sum2设为0
sum1设为区间长度
mn2设为无穷大
 *如果是叶子节点，直接返回
 *递归构建左右子树
 *
 *合并两个节点信息
 *初始化新节点，计算最小值和次小值
 *更新次小值
 *计算最小值和次小值的个数
 *返回合并后的节点
 *
 *下传懒惰标记
 *将标记传递给子节点并清空当前节点标记
 *
*区间修改：
l, r: 当前区间范围
x: 当前节点编号
L, R: 修改区间范围
v: 修改值
 *如果当前区间完全在修改范围内，直接修改并打标记
 *否则下传标记，递归修改子区间，然后合并信息
 *
 *区间查询
 *如果当前区间完全在查询范围内，直接返回
 *否则下传标记，根据查询区间位置递归查询并合并结果
 *
 *读取颜色数组，并记录每种颜色的位置
 *构建线段树
 *初始化答案为0
 *遍历每种颜色
*获取当前颜色左右相邻位置的颜色
计算边界bound
 *在区间[bound, i]上加1
 *如果条件满足，在区间[1, bound]上减1
*查询区间[1, i-1]的信息
如果最小值≤2，累加其个数
如果次小值≤2，累加其个数
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300100
using namespace std;

int n, col[N], pos[N];
struct node { int mn1, mn2, sum1, sum2, tag; } s[N<<2];
struct sgt {
    static void build(const int l, const int r, const int x) {
        s[x].tag = s[x].mn1 = s[x].sum2 = 0;
        s[x].sum1 = r - l + 1; s[x].mn2 = 1e9;
        if (l == r) return;
        const int mid = (l + r) >> 1;
        build(l, mid, x<<1), build(mid + 1, r, x<<1|1);
    }
    static node merge(const node& a, const node& b) {
        node x{}; x.sum1 = x.sum2 = x.tag = 0;
        x.mn1 = min(a.mn1, b.mn1); x.mn2 = min(a.mn2, b.mn2);
        if (a.mn1 > x.mn1) x.mn2 = min(x.mn2, a.mn1);
        if (b.mn1 > x.mn1) x.mn2 = min(x.mn2, b.mn1);
        if (a.mn1 == x.mn1) x.sum1 += a.sum1;
        if (b.mn1 == x.mn1) x.sum1 += b.sum1;
        if (a.mn1 == x.mn2) x.sum2 += a.sum1;
        if (b.mn1 == x.mn2) x.sum2 += b.sum1;
        if (a.mn2 == x.mn2) x.sum2 += a.sum2;
        if (b.mn2 == x.mn2) x.sum2 += b.sum2;
        return x;
    }
    static void pushdown(const int x) {
        const int d = s[x].tag;
        s[x<<1].mn1 += d, s[x<<1].mn2 += d, s[x<<1].tag += d;
        s[x<<1|1].mn1 += d, s[x<<1|1].mn2 += d, s[x<<1|1].tag += d;
        s[x].tag = 0;
    }

    static void modify(const int l, const int r, const int x, const int L, const int R, const int v) {
        if (L <= l && r <= R) {
            s[x].mn1 += v, s[x].mn2 += v, s[x].tag += v;
            return;
        }
        pushdown(x);
        const int mid = (l + r) >> 1;
        if (mid >= L) modify(l, mid, x<<1, L, R, v);
        if (mid < R) modify(mid + 1, r, x<<1|1, L, R, v);
        s[x] = merge(s[x<<1], s[x<<1|1]);
    }

    static node query(const int l, const int r, const int x, const int L, const int R) {
        if (L <= l && r <= R) return s[x];
        pushdown(x);
        const int mid = (l + r) >> 1;
        if (mid >= L && mid < R) return merge(query(l, mid, x<<1, L, R),
            query(mid + 1, r, x<<1|1, L, R));
        if (mid >= L) return query(l, mid, x<<1, L, R);
        return query(mid + 1, r, x<<1|1, L, R);
    }
};

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> col[i];
        pos[col[i]] = i;
    }
    sgt::build(1, n, 1);
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        int l = col[pos[i]-1], r = col[pos[i]+1],
        bound = max(l > i ? 1 : l + 1, r > i ? 1 : r + 1);
        sgt::modify(1, n, 1, bound, i, 1);
        bound = min(l, r);
        if (max(l, r) < i && bound > 0)
            sgt::modify(1, n, 1, 1, bound, -1);
        if (i > 1) {
            const node t = sgt::query(1, n, 1, 1, i - 1);
            if (t.mn1 <= 2) ans += t.sum1;
            if (t.mn2 <= 2) ans += t.sum2;
        }
    }
    cout << ans << '\n';
    return 0;
}
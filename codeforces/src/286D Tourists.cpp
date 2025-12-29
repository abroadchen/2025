//
// Created by Psy.C on 2025/12/28.
//
/*
* N = 100005: 操作数最大值
M = 200005: 数组大小，用于坐标离散化
K = 7500005: 线段树节点数量
inf = 2147483647: 无穷大值
A = 1e9: 大数常量，用于偏移
fa[M], ct[M]: 并查集父节点数组和覆盖时间数组
 *
*并查集路径压缩查找函数
如果x == fa[x]说明x是根节点，直接返回
否则递归查找父节点并压缩路径
*将区间[x, y]覆盖为时间z
x = find(x)找到当前段的根节点
循环直到x > y
ct[x] = z记录覆盖时间
fa[x] = x + 1将当前节点指向下一个节点，实现路径压缩
 *
*l, r: 左右子节点索引
s: 区间和
tg: 懒标记（延迟更新标记）
cnt: 当前分配的节点编号
 *
*tag函数：给节点o打懒标记
如果节点o不存在，则创建新节点
更新懒标记和区间和
*pushdown函数：下推懒标记
如果没有懒标记则返回
计算中点mid = (l + r) / 2
将懒标记传递给左右子树
清除当前节点懒标记
*add函数：区间加法操作
如果当前区间完全在[L,R]内，打懒标记
否则下推懒标记后递归更新左右子树
最后更新当前节点的区间和
*query函数：区间查询
如果节点不存在返回0
如果当前区间完全在[L,R]内，返回区间和
否则下推懒标记后递归查询左右子树
返回左右子树查询结果之和
 *
*m: 查询次数
n: 操作次数
ord[N]: 操作顺序数组
l[N], r[N], t[N]: 左边界、右边界、时间数组
d[M]: 离散化坐标数组
di: 离散化数组实际大小
p[M]: 离散化后的坐标映射
 *
*读入n个操作，每个操作包含区间[l,r]和时间t
--r[i]: 将区间转换为半开区间[l, r)
将l[i]和r[i]+1加入离散化数组
*对离散化数组排序
使用map建立原坐标到离散化坐标的映射
p[mp[d[i]]=mp[d[i-1]]+1] = d[i]建立双向映射
更新di为离散化后坐标数量
*初始化并查集，每个节点的父节点是自己，覆盖时间为无穷大
按时间顺序处理操作，更新为离散化坐标后执行覆盖操作
*遍历每个离散化区间
lp, rp是原坐标的左边界和右边界
在线段树上添加区间[ct[i] - rp + A + 1, ct[i] - lp + A + 1]
这里A是偏移量，防止负数索引
*处理m个查询
对每个查询x，在线段树上查询[1, x + A + 1]区间和
输出查询结果
 *
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 100005, M = 200005, K = 7500005, inf = 2147483647, A = 1e9;
int fa[M], ct[M];
int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void cov(int x, const int y, const int z) {
    for (x = find(x); x <= y; x = find(x)) {
        ct[x] = z;
        fa[x] = x + 1;
    }
}

struct node { int l, r, s, tg; } tr[K];
int cnt;
struct SegmentTree {
    static void tag(int& o, const int l, const int r, const int v) {
        if (!o) o = ++cnt;
        tr[o].tg += v, tr[o].s += (r - l + 1) * v;
    }
    static void pushdown(const int o, const int l, const int r) {
        if (!tr[o].tg) return;
        const int mid = (l + r) >> 1;
        tag(tr[o].l, l, mid, tr[o].tg);
        tag(tr[o].r, mid + 1, r, tr[o].tg);
        tr[o].tg = 0;
    }
    //两个条件可能同时满足
    static void add(int& o, const int l, const int r, const int L, const int R) {
        if (!o) o = ++cnt;
        if (L <= l && r <= R) { tag(o, l, r, 1); return; }
        pushdown(o, l, r);
        const int mid = (l + r) >> 1;
        if (L <= mid) add(tr[o].l, l, mid, L, R);//左子树可能有交集
        if (R > mid) add(tr[o].r, mid + 1, r, L, R);
        tr[o].s = tr[tr[o].l].s + tr[tr[o].r].s;
    }
    //互斥
    static int query(const int o, const int l, const int r, const int L, const int R) {
        if (!o) return 0;
        if (L <= l && r <= R) return tr[o].s;
        pushdown(o, l, r);
        const int mid = (l + r) >> 1;
        if (R <= mid) return query(tr[o].l, l, mid, L, R);//只在左子树
        if (L > mid) return query(tr[o].r, mid + 1, r, L, R);
        return query(tr[o].l, l, mid, L, R) + query(tr[o].r, mid + 1, r, L, R);
    }
};

signed main() {
    fast;
    int m, n, ord[N], l[N], r[N], t[N], d[M], di = 0, p[M];
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) {
        ord[i] = i;
        cin >> l[i] >> r[i] >> t[i]; --r[i];
        d[++di] = l[i];
        d[++di] = r[i] + 1;
    }
    sort(ord + 1, ord + n + 1, [&](const int x, const int y) {
        return t[x] < t[y];
    });
    sort(d + 1, d + di + 1); d[0] = -1;
    map<int, int> mp;
    int tot = 0;
    for (int i = 1; i <= di; ++i) {
        if (d[i] != d[i-1]) {
            mp[d[i]] = ++tot;
            p[tot] = d[i];
        }
    }
    di = tot;
    for (int i = 1; i <= di + 1; ++i) fa[i] = i, ct[i] = inf;
    for (int j = 1; j <= n; ++j) {
        const int i = ord[j], li = mp[l[i]], ri = mp[r[i] + 1];
        cov(li, ri - 1, t[i]);
    }
    int rt;
    for (int i = 1; i <= di; ++i) {
        if (ct[i] == inf) continue;
        const int lp = p[i], rp = p[i + 1] - 1;
        if (rp >= lp && lp >= 0) {
            const int lv = ct[i] - rp + A, rv = ct[i] - lp + A;
            if (lv >= 0 && rv >= 0) {
                SegmentTree::add(rt, 0, A<<1, lv, rv);
            }
        }
    }
    while (m--) {
        int x; cin >> x;
        cout << SegmentTree::query(rt, 1, A<<1, 0, x + A) << '\n';
    }
    return 0;
}
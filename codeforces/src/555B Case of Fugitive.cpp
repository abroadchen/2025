//
// Created by Psy.C on 2026/3/10.
//
/**
n: 区间数量
m: 查询数量
l[N], r[N]: 原始区间数组
ans[N]: 答案数组，记录每个区间分配的查询id
p: 优先队列（最大堆，按右端点降序）

读入n个原始区间[l[i], r[i]]
读入m个查询点，记录其值和原始id
构造新区间：对于相邻的两个区间，计算它们之间的"间隙"
a[i].l = l[i+1] - r[i]: 相邻区间右端点到左端点的距离（负值表示重叠）
a[i].r = r[i+1] - l[i]: 相邻区间右端点到左端点的最大距离
按左端点升序排序区间
按查询值升序排序查询点
扫描线算法：按查询值从小到大处理
将左端点不超过当前查询值的区间加入优先队列
检查队列顶部的区间右端点是否大于等于查询值
如果满足条件，将当前查询分配给该区间
检查是否所有区间都被分配了查询
输出结果

排序：O(n log n + m log m)
扫描过程：O((n + m) log n)
总体：O(n log n + m log m)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
struct node {
    ll l, r, id;
    ///按右端点降序排列（用于优先队列）
    bool operator<(const node &o) const {
        return r > o.r;
    }
} a[N];
struct node2 { ll d, id; } q[N];

int n, m;
ll l[N], r[N], ans[N];
priority_queue<node> p;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> l[i] >> r[i];
    for (int i = 1; i <= m; ++i) cin >> q[i].d, q[i].id = i;
    for (int i = 1; i < n; ++i)
        a[i].l = l[i+1] - r[i], a[i].r = r[i+1] - l[i], a[i].id = i;
    sort(a + 1, a + n, [](const node &a, const node &b) {
        return a.l < b.l;
    });
    sort(q + 1, q + m + 1, [](const node2 &a, const node2 &b) {
        return a.d < b.d;
    });
    int j = 1;
    for (int i = 1; i <= m; ++i) {
        while (j < n && a[j].l <= q[i].d) p.push(a[j++]);
        if (p.empty()) continue;
        if (p.top().r < q[i].d) { cout << "No\n"; return 0; }
        auto x = p.top(); p.pop();
        ans[x.id] = q[i].id;
    }
    if (!p.empty() || j != n) { cout << "No\n"; return 0; }
    cout << "Yes\n";
    for (int i = 1; i < n; ++i) cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}
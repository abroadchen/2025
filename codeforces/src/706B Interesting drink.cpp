//
// Created by Psy.C on 2026/4/19.
//
/**
idx: 查询的原始索引
cn: 查询的值（要比较的阈值）
cnt: 结果（小于等于cn的元素个数）
cmp: 按cn（查询值）升序排序
cmp2: 按idx（原始索引）升序排序
n: 数组a的长度
a[N]: 输入数组
q: 查询数量

upper_bound(a, a + n, d[i].cn): 找到第一个大于d[i].cn的位置
upper_bound(...) - a: 得到该位置的索引
这个索引就是小于等于d[i].cn的元素个数

O(n log n + q log n): 排序 + q次二分查找
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

struct node { int idx, cn, cnt; } d[N];
struct cmp {
    bool operator()(const node &o1, const node &o2) const {
        return o1.cn < o2.cn;
    }
};
struct cmp2 {
    bool operator()(const node &o1, const node &o2) const {
        return o1.idx < o2.idx;
    }
};

int n, a[N], q;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> d[i].cn; d[i].idx = i;
    }
    sort(d, d + q, cmp());
    for (int i = 0; i < q; ++i)
        d[i].cnt = upper_bound(a, a + n, d[i].cn) - a;
    ///按原始索引idx排序，恢复查询的原始顺序
    sort(d, d + q, cmp2());
    for (int i = 0; i < q; ++i) cout << d[i].cnt << '\n';//按原始查询顺序输出结果
    return 0;
}
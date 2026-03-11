//
// Created by Psy.C on 2026/3/11.
//
/**
位置x和价值val
重载 < 运算符：按绝对值大小排序
l: 存储非正数位置的点
r: 存储正数位置的点
按位置分为两组：左侧（x ≤ 0）和右侧（x > 0）
ans: 第一种策略的结果
ans2: 第二种策略的结果
i, j: 两个指针，分别指向左右数组
策略1: 优先选择左侧点，然后交替选择右侧点
按绝对值从小到大选择（因为已排序）
策略2: 优先选择右侧点，然后交替选择左侧点

排序: O(n log n)
遍历: O(n)
总体: O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct node {
    int x, val;
    bool operator<(const node &o) const {
        return abs(x) < abs(o.x);
    }
};
vector<node> l, r;
int n;
int main() {
    fast;
    cin >> n; l.clear(); r.clear();
    for (int i = 0, x, val; i < n; ++i) {
        cin >> x >> val;
        if (x <= 0) l.push_back({x, val});
        else r.push_back({x, val});
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    int ans = 0, i = 0, j = 0, ans2 = 0;
    while (i < l.size()) {
        ans += l[i++].val;
        if (j >= r.size()) break;
        ans += r[j++].val;
    }
    i = 0, j = 0;
    while (j < r.size()) {
        ans2 += r[j++].val;
        if (i >= l.size()) break;
        ans2 += l[i++].val;
    }
    cout << max(ans, ans2) << '\n';
    return 0;
}
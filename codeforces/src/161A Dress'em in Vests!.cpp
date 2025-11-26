//
// Created by Psy.C on 2025/11/26.
//
/*
n: 第一个数组的元素个数（可能是开发者developer）
m: 第二个数组的元素个数（可能是算法algorithm）
x: 下界偏移量
y: 上界偏移量*
 *
*d(n): 存储第一个数组（大小为n）
a(m): 存储第二个数组（大小为m）
 *
*p: 指向数组d的指针（当前开发者索引）
v: 指向数组a的指针（当前算法索引）
ans: 存储匹配结果的向量
 *
 *当两个指针都没越界时继续
*如果当前算法a[v]在开发者d[p]的接受范围内[d[p]-x, d[p]+y]：
将匹配对(p+1, v+1)加入结果（+1是因为题目要求1-indexed）
两个指针都向前移动
*如果当前算法太差（小于下界）：
移动算法指针，尝试下一个更好的算法
*如果当前算法太好（超过上界）：
移动开发者指针，当前开发者无法胜任
 *
 *O(n + m)：每个元素最多被访问一次
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m, x, y; cin >> n >> m >> x >> y;
    vector<int> d(n), a(m);
    for (int i = 0; i < n; ++i) cin >> d[i];
    for (int i = 0; i < m; ++i) cin >> a[i];

    int p = 0, v = 0;
    vector<pair<int,int>> ans;
    while (p < n && v < m) {
        if (a[v] >= d[p] - x && a[v] <= d[p] + y) {
            ans.emplace_back(p + 1, v + 1);
            ++p; ++v;
        } else if (a[v] < d[p] - x) ++v;
        else if (a[v] > d[p] + y) ++p;
    }
    cout << ans.size() << '\n';
    for (const auto & it : ans) {
        cout << it.first << ' ' << it.second << '\n';
    }
    return 0;
}
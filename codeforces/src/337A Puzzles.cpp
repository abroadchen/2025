//
// Created by Psy.C on 2026/1/11.
//
/**
* n：需要选择的元素个数
m：总共有m个元素
f：存储m个元素的向量
 *
 *排序后相邻元素之间的差值更容易处理
 *初始答案为前n个元素的最大值与最小值之差
 *
*从位置1开始滑动窗口
检查从位置i开始的连续n个元素：f[i]到f[i+n-1]
如果新的差值更小，更新答案
循环终止条件保证窗口不会越界
 *
*排序：O(m log m)
滑动窗口：O(m)
总体：O(m log m)
 *
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <ranges>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    vector<int> f(m);
    for (int i = 0; i < m; ++i) cin >> f[i];
    ranges::sort(f);
    int ans = f[n-1] - f[0];
    for (int i = 1; i <= m - n; ++i) if (f[i + n - 1] - f[i] < ans) {
        ans = f[i + n - 1] - f[i];
    }
    cout << ans << '\n';
    return 0;
}
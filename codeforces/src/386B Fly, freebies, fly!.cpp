//
// Created by Psy.C on 2026/1/27.
//
/**
* 读入时间范围 T
mx 用于记录最大连续任务数
 *
*外层循环：i 从0到 n-1，作为窗口左边界
k = upper_bound(...): 使用二分查找找到第一个大于 t[i] + T 的位置
upper_bound 返回迭代器，减去 t.begin() 得到索引
 *
 *k - i + 1: 当前窗口包含的任务数量（从索引 i 到 k）
 *
*时间复杂度
排序：O(n log n)
外层循环：O(n)
内层 upper_bound：O(log n)
总体：O(n log n)
空间复杂度
O(n)，用于存储输入数组
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) cin >> t[i];
    ranges::sort(t);
    int T, mx = 0; cin >> T;
    for (int i = 0, k; i < n; ++i) {
        k = static_cast<int>(upper_bound(t.begin(), t.begin() + n, t[i] + T) - t.begin());
        if (k < n && t[k] > T + t[i]) k--;//k 指向的值超出了范围，回退一步
        if (k == n) k--;//k 达到数组边界，回退一步
        mx = max(mx, k - i + 1);
    }
    cout << mx;
    return 0;
}
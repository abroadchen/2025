//
// Created by Psy.C on 2026/2/2.
//
/**
* 使用 nth_element 函数进行部分排序
a：数组起始位置
a + k - 1：目标位置（第k大元素应该在的位置，数组从0开始所以减1）
a + n：数组结束位置
greater<int>{} ：降序比较器，使数组按从大到小排列
这个函数的作用是找到第k大的元素并放到正确位置，而不需要完全排序整个数组
 *
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k, a[105]; cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    nth_element(a, a + k - 1, a + n, greater<int>{});
    cout << a[k - 1];
    return 0;
}
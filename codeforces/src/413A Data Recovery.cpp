//
// Created by Psy.C on 2026/2/2.
//
/**
* n：序列的总长度
m：已知元素的个数
mn：序列的最小值
mx：序列的最大值
*t[101]：存储已知元素的数组（最大101个元素）
l = 2：边界约束计数器，初始值为2（代表需要满足最小值和最大值约束）
 *r 表示在总长度 n 中，除去已知的 m 个元素后，还剩多少个未知元素
 *
 *如果数组中最大的元素（t[m-1]）已经等于要求的最大值 mx，则不需要额外的空间来放置最大值，因此边界约束减少1
 *如果数组中最小的元素（t[0]）已经等于要求的最小值 mn，则不需要额外的空间来放置最小值，因此边界约束再减少1
 *
 *
*r - l < 0：剩余空间不足以满足边界约束需求
!(mn <= t[0] && t[m-1] <= mx)：已知元素超出了指定的范围
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m, mn, mx; cin >> n >> m >> mn >> mx;
    int t[101], l = 2;
    const int r = n - m;
    for (int i = 0; i < m; ++i) cin >> t[i];
    sort(t, t+m);
    if (t[m-1] == mx) l--;
    if (t[0] == mn) l--;
    if (r - l < 0 || !(mn <= t[0] && t[m-1] <= mx)) cout << "Incorrect";
    else cout << "Correct";
    return 0;
}
//
// Created by Psy.C on 2025/11/25.
//
/*
*n: 数组元素个数
k: 阈值参数
v: 存储输入数据的向量
p: 满足条件的元素计数器
 *
 *v[n - 1 - p]: 从排序后数组的末尾开始向前访问
*p < n: 确保不越界
v[n - 1 - p] > 0: 当前元素必须是正数
v[n - 1 - p] >= v[n - k]: 当前元素必须大于等于第k大的元素
 *
*时间复杂度：O(n log n)（主要消耗在排序上）
空间复杂度：O(n)
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    sort(v.begin(), v.end());//对向量进行升序排序
    int p = 0;
    while (p < n && v[n - 1 - p] > 0 && v[n - 1 - p] >= v[n - k]) ++p;
    cout << p << '\n';
    return 0;
}
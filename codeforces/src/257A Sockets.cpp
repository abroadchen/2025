//
// Created by Psy.C on 2025/12/18.
//
/*
 *f: 已选择的元素个数
 *p: 当前累积的值
 *
*时间复杂度：O(n log n)，主要是排序的时间
空间复杂度：O(1)，只使用了常数额外空间
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m, k, a[52]; cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n, greater<>());//降序排序（从大到小）
    int f = 0, p = k;
    while (f < n && p < m) {
        p += a[f] - 1;//选择当前最大元素，但减去1
        f += 1;//增加选择计数
    }
    cout << (p >= m ? f : -1) << '\n';//如果达到目标则输出选择数，否则输出-1
    return 0;
}
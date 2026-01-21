//
// Created by Psy.C on 2026/1/21.
//
/*
* 排序：O(n log n)
遍历：O(n)
总体：O(n log n)
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, d, m, sum = 0; cin >> n >> d;//折扣值
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    cin >> m;//选择数量
    if (m > n) {
        for (int i = 0; i < n; ++i) sum += a[i];//选择所有n个元素
        sum -= (m - n) * d;//额外选择(m-n)个，每个减去d
    } else {
        ranges::sort(a);
        for (int i = 0; i < m; ++i) sum += a[i];//选择最小的m个元素
    }
    cout << sum;
    return 0;
}
//
// Created by Psy.C on 2026/1/27.
//
/**
 *
 *n（数组长度）、c（常数）、t（结果变量）
*时间复杂度
O(n)，需要遍历数组一次
空间复杂度
O(n)，用于存储数组 d
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, c, t(0); cin >> n >> c;
    vector<int> d(n);
    for (int i = 0; i < n; ++i) cin >> d[i];
    for (int i = 0; i < n - 1; ++i) t = max(t, d[i] - d[i+1] - c);
    cout << t << '\n';
    return 0;
}
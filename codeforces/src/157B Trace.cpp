//
// Created by Psy.C on 2025/11/25.
//
/*
 *圆环面积 = π × R² - π × r² = π × (R² - r²)
*时间复杂度：O(n log n)（主要消耗在排序上）
空间复杂度：O(n)
 */
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr double pi = 3.14159265359;

int main() {
    fast;
    int n; cin>>n;
    vector<int> v(n + 1); v[0] = 0;
    for (int i = 1; i <= n; ++i) cin>>v[i];
    sort(v.begin(), v.end());

    double sum = 0;
    for (int i = n; i > 0; i -= 2) sum += v[i]*v[i]-v[i-1]*v[i-1];
    sum *= pi;
    cout << fixed << setprecision(10) << sum << '\n';
    return 0;
}
//
// Created by Psy.C on 2026/3/24.
//
/**
反向映射：p数组记录的是每个值在原序列中的位置
p[i]：值i在原序列中的位置
p[i-1]：值i-1在原序列中的位置
abs(p[i] - p[i-1])：两者的距离
累加所有相邻数值位置差的绝对值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
int n, p[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; p[x] = i;
    }
    ll ans = 0;
    for (int i = 2; i <= n; ++i)
        ans += abs(p[i] - p[i-1]);
    cout << ans << '\n';
    return 0;
}
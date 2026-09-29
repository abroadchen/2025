//
// Created by Psy.C on 2026/9/29.
//
/***
若 第一个数 a[1] 是偶数 或 最后一个数 a[n] 是偶数 → 直接输出 No。
即：首尾必须都是奇数
若 n 是偶数 → 输出 No。
即 n 必须是奇数
首尾都是奇数 且 n 为奇数 → 输出 Yes
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    if (a[1]%2 == 0 || a[n]%2 == 0) {
        cout << "No"; return 0;
    }
    if (n%2 == 0) { cout << "No"; return 0; }
    cout << "Yes";
    return 0;
}
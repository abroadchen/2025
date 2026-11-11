//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
读入 n, m。
特判 m == 0：直接输出 n n（两个数都等于 n），然后结束。
含义：没有任何"相同对"时，最小值和最大值都是 n（比如每个元素都各自独立）
若 2m >= n：输出 0。
否则输出 n - 2m
用一个空循环求最小的 ans，使得 ans*(ans+1)/2 >= m（即 1+2+...+ans ≥ m）。
输出 n - ans - 1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m, ans;
int main() {
    fast;
    cin >> n >> m;
    if (!m) { cout << n << ' ' << n << '\n'; return 0; }
    if (m*2 >= n) cout << "0"; else cout << n-m*2;
    for (ans = 0; ans*(ans+1)/2 < m; ans++) {}
    cout << ' ' << n-ans-1 << '\n';
    return 0;
}
//
// Created by Psy.C on 2026/3/3.
//
/**
保存当前值：i = n; j = m
更新变量：n = j; m = i%j
新的n = 旧的m
新的m = 旧的n % 旧的m
算法本质：这是欧几里得算法（辗转相除法）的变种
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m, t, ans, i, j;
int main() {
    fast;
    cin >> n >> m;
    if (n < m) { t ^= n ^= m ^= t; }
    while (m != 1 && n%m != 0) {
        ans += n/m;
        i = n; j = m;
        n = j; m = i%j;
    }
    ans += n/m;
    cout << ans << '\n';
    return 0;
}
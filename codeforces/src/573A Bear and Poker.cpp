//
// Created by Psy.C on 2026/3/13.
//
/**
去除所有因数3：只要数字能被3整除，就不断除以3
去除所有因数2：只要数字能被2整除，就不断除以2
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        while (a[i] % 3 == 0) a[i] /= 3;
        while (a[i] % 2 == 0) a[i] /= 2;
    }
    sort(a + 1, a + n + 1);
    n = unique(a + 1, a + n + 1) - a - 1;
    if (n == 1) cout << "YES\n"; else cout << "NO\n";
    return 0;
}
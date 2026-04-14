//
// Created by Psy.C on 2026/4/13.
//
/**
f = e + b - c: 基于e计算f值
h = e + a - d: 基于e计算h值
i = f + a - d: 基于f计算i值（也可以写成i = e + b - c + a - d）
if (...) ans++: 如果f、h、i都在[1,n]范围内，计数器+1
将计数结果乘以n
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n, a, b, c, d, e, f, i, h;
int main() {
    fast;
    cin >> n >> a >> b >> c >> d;
    ll ans = 0;
    for (e = 1; e <= n; ++e) {
        f = e + b - c;
        h = e + a - d;
        i = f + a - d;
        if (f >= 1 && f <= n && h >= 1 && h <= n &&
            i >= 1 && i <= n) ans++;
    }
    ans *= n;
    cout << ans << '\n';
    return 0;
}
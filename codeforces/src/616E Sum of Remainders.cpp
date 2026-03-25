//
// Created by Psy.C on 2026/3/25.
//
/**
枚举所有可能的k/i值相同的连续区间
k/x在[l,r]范围内恒定为k/l
计算并减去 sum_{i=l}^{r} floor(k/i) * i
使用等差数列求和公式：sum_{i=l}^{r} i = (l+r)*(r-l+1)/2

2在模mod下的乘法逆元

O($\sqrt{\min(k,n)}$)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int mod = 1e9 + 7;
ll k, n, ans;
int main() {
    fast;
    cin >> k >> n;
    ans = n%mod*(k%mod)%mod;
    for (ll l = 1, r; l <= n && l <= k; l = r + 1) {
        r = min(k/(k/l), n);
        ans = (ans - k/l%mod*((l+r)%mod)%mod*((r-l+1)%mod)%mod*((mod+1)/2)%mod)%mod;
    }
    cout << (ans + mod) % mod << '\n';
    return 0;
}
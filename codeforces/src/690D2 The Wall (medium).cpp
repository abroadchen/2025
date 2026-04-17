//
// Created by Psy.C on 2026/4/16.
//
/**
dp[i]计算的是组合数C(m+i-1, i)
最终结果是∑(i=1 to n) C(m+i-1, i)
使用快速幂来计算模意义下的逆元，避免除法运算
整体时间复杂度为O(n log mod)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e5+5, mod = 1e6+3;

ll ksm(ll x, ll y) {
    ll s = 1, base = x;
    while (y) {
        if (y&1) s = s * base % mod;
        base = base * base % mod;
        y >>= 1;
    }
    return s;
}

ll dp[N], n, m;
void init() {
    dp[0] = 1;
    for (ll i = 1; i <= n; ++i)
        dp[i] = dp[i-1]*(i+m-1)%mod*ksm(i,mod-2)%mod;
}

int main() {
    fast;
    cin >> n >> m; init();
    ll sum = 0;
    for (ll i = 1; i <= n; ++i) sum = (sum + dp[i]) % mod;
    cout << sum << '\n';
    return 0;
}
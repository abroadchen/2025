//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
x = b[i] - b[i-1] 是相邻两个标记（含边界）间的段长
设 p = ksm(a, x)，则每次乘法因子为：

ans *= p + p*(p-1)/2
其中 p*(p-1)/2 中：

*ksm(2, mod-2) 是费马小定理求 2 的逆元（因为 mod 为质数）。
(..+mod)%mod 保证非负。
化简：

ans *= (2p + p(p-1)) / 2 = (p² + p)/2
所以每次乘的因子是 (a^x)² + a^x 再除以 2，也就是 C(a^x+1, 2)... 等价的 (a^x)(a^x+1)/2
末尾修正

    (ans *= ksm(a, n-(b[m]<<1))) %= mod;
n - (b[m]<<1) 即 n - 2*b[m]。
乘上 a^(n - 2*b[m])。


记 p_i = a^{b_i - b_{i-1}}（i=1..m，b_0=0），答案：
ans = ∏ (p_i² + p_i)/2 × a^(n - 2*b_m)   (mod 998244353)
即：
ans = a^(n - 2*b_m) × ∏ [ a^{(b_i-b_{i-1})} · (a^{(b_i-b_{i-1})}+1) / 2 ]
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;

constexpr int N = 2e5+5, mod = 998244353;

inline ll ksm(ll a, ll b) {
    ll ret = 1;
    while (b) {
        if (b&1) (ret *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return ret;
}

ll n, m, a, b[N], ans(1);
int main() {
    fast;
    cin >> n >> m >> a;
    rep(i,m) cin >> b[i];
    rep(i,m) {
        ll x = b[i] - b[i-1];
        ans *= ksm(a,x) + ((ksm(a,x)*(ksm(a,x)-1)%mod+mod)%mod*ksm(2,mod-2)%mod)%mod;
        ans %= mod;
    }
    (ans *= ksm(a, n-(b[m]<<1))) %= mod;
    cout << ans;
    return 0;
}
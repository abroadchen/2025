//
// Created by Psy.C on 2026/1/11.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300001
#define mod 1000000007
using namespace std;

///(x^y) % mod
///时间复杂度 O(log y)
ll pw(ll x, ll y) {
    auto res = 1ll;
    while (y) {
        if (y&1) res = res*x%mod;
        x = x*x%mod;
        y >>= 1;
    }
    return res;
}

/// C(n,m) = n!/(m!(n-m)!)
/// 费马小定理计算逆元：a^(p-2) ≡ a^(-1) (mod p)
ll fac[N];//存储阶乘值
ll C(const int n, const int m) {
    if (n < m || m < 0) return 0;
    return fac[n] * pw(fac[m], mod - 2) % mod *
        pw(fac[n-m], mod - 2) % mod;
}


int main() {
    fast;
    int n, m, g; cin >> n >> m >> g; fac[0] = 1;
    if (m == 0) {
        cout << (n % 2 == g ? 0 : 1) << '\n';
        return 0;
    }
    n += m;//更新 n 的值
    for (int i = 1; i <= n; ++i) fac[i] = fac[i-1]*i%mod;//计算从 1 到 n 的所有阶乘值
    ll ans = 0;
    for (int i = 1; i <= n - m + 1 && i <= n; ++i) {
        if (const int cnt0 = i == n ? n - 1 : i; cnt0 % 2 != g)
            ans = (ans + C(max(0, n - i), m - 1)) % mod;
    }
    cout << ans;
    return 0;
}
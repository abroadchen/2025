//
// Created by Psy.C on 2026/1/8.
//
/**
 *
* 先计算2^n - 1
再计算(2^n - 1)^(mod-2)，这是求逆元（费马小定理）
因为a^(p-1) ≡ 1 (mod p)，所以a^(p-2)是a的逆元
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll unsigned long long
using namespace std;

ll mod = 1e9 + 7;
ll pw(ll a, ll b) {
    ll ans = 1ll;
    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans % mod;
}

int main() {
    fast;
    string s; ll k; cin >> s >> k;
    const ll n = s.size(),
    a = (pw(2ll, k * n) - 1ll + mod) % mod,//2^(k*n) - 1
    b = (pw((pw(2ll, n) - 1ll + mod) % mod, mod - 2) + mod) % mod;
    const ll t = a * b % mod; ll x = 0ll;
    for (int i = 0; i < s.size(); ++i) if (s[i] == '0' || s[i] == '5') {
        x = (x + pw(2ll, i)) % mod;//统计字符串中'0'和'5'的位置
    }
    ll ans = t * x % mod; ans = (ans + mod) % mod;//防止负数
    cout << ans << '\n';
    return 0;
}
//
// Created by Psy.C on 2025/12/1.
//
/*
*计算 tp = 2^u mod (mod-1)
计算 q = (x^tp - 1) mod mod，加mod防止负数
*计算 y = 2^(v+1) mod (mod-1)
计算 res = ((x^y - 1) * q^(mod-2)) mod mod
这里使用了费马小定理：q^(mod-2) 是 q 在模mod下的逆元
 *
*如果k是奇数，对结果进行额外调整
计算 2^(r-l) mod p 的逆元并乘到结果中
 *
 *a^(2^l + 2^(l+1) + ... + 2^r) mod p
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int t, k, p;
ll l, r;

ll ksm(int a, ll b, const int mod) {
    ll ret = 1;
    for (; b; b >>= 1) {
        if (b & 1) ret = (ret * a) % mod;
        a = static_cast<int>(1ll * a * a % mod);
    }
    return ret;
}

ll f(const int x, const ll u, const ll v, const int mod) {
    if (x % mod == 0) return 1;
    const ll tp = ksm(2, u, mod - 1), q = (ksm(x, tp, mod) - 1 + mod) % mod;
    if (!q) return ksm(2, v - u + 1, mod);
    const ll y = ksm(2, v + 1, mod - 1),
    res = (ksm(x, y, mod) - 1 + mod) % mod *
        ksm(static_cast<int>(q), mod - 2, mod) % mod;
    return res;
}

int main() {
    fast;
    for (cin >> t; t--;) {
        cin >> k >> l >> r >> p;
        if (p == 2) cout << (k % 2 ? 0 : 1) << '\n';
        else {
            ll x = f(k, l, r, p);
            if (k % 2) x = x * ksm(static_cast<int>(ksm(2, r - l, p)), p - 2, p) % p;
            cout << x << '\n';
        }
    }
    return 0;
}
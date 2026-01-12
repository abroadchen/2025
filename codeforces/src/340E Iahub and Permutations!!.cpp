//
// Created by Psy.C on 2026/1/12.
//
/**
* num：数组中-1的数量（需要填入的空位数）
b[a[i]] = 1：标记已存在的数字
*cnt：既在-1位置又不在已有数字集合中的数字个数
这些数字可以自由填入-1位置
 *
*预计算阶乘：fac[i] = i! % mod
预计算阶乘的逆元：inv[i] = (i!)^(-1) % mod
使用费马小定理：a^(-1) ≡ a^(p-2) (mod p)
 *
*第i项：(-1)^i * C(cnt, i) * (num-i)!
ksm(-1, i%2)：容斥符号 (-1)^i
fac[cnt] * inv[cnt-i] % mod * inv[i]：组合数 C(cnt, i)
fac[num-i]：剩余位置的排列数
 *
*总的排列数：num!
减去至少一个数在原位置的排列数
加上至少两个数在原位置的排列数
 *
 *
 *O(n + num)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 2020
#define mod 1000000007
using namespace std;

ll ksm(ll d, ll p) {
    ll ret = 1;
    while (p) {
        if (p&1) ret = ret * d % mod;
        d = d * d % mod;
        p >>= 1;
    }
    return ret;
}


int main() {
    fast;
    ll n, a[N], num = 0, b[N], cnt = 0, fac[N], inv[N]; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] == -1) num++; else b[a[i]] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        if (a[i] == -1 && !b[i]) cnt++;
    }
    fac[0] = 1;
    for (int i = 1; i <= num; ++i) fac[i] = fac[i - 1] * i % mod;
    inv[num] = ksm(fac[num], mod - 2);
    for (ll i = num - 1; i; --i) inv[i] = inv[i+1] * (i + 1) % mod;
    inv[0] = 1;
    ll ans = fac[num];
    for (int i = 1; i <= cnt; ++i)
        ans += ((((ksm(-1, i%2)*fac[cnt])%mod)*inv[cnt-i]%mod)*inv[i]%mod)*fac[num-i]%mod;
    while (ans < 0) ans += mod;
    cout << ans % mod;
    return 0;
}
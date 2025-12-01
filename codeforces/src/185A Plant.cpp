//
// Created by Psy.C on 2025/12/1.
//
/*
*(4^n + 2^n) * 2^(-1) (mod)
其中2^(mod-2)是2在模mod下的逆元
（根据费马小定理：a^(p-1) ≡ 1 (mod p)，所以a^(-1) ≡ a^(p-2) (mod p)）
*快速幂的时间复杂度：O(log b)
总体时间复杂度：O(log n)
空间复杂度：O(log n)（由于递归调用栈）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mod 1000000007
using namespace std;

ll pw(const int a, const ll b) {
    if (b == 0) return 1;//任何数的0次方都是1
    ll res = pw(a, b/2) % mod;
    res *= res % mod;//计算res^2 % mod，即a^(b/2) * a^(b/2) = a^b（当b为偶数时）
    if (b % 2) res *= a % mod;//如果b是奇数，还需要额外乘以a，因为b/2向下取整会丢失一个因子
    return res % mod;
}

int main() {
    fast;
    ll n; cin >> n;
    const ll ans = (pw(4, n) + pw(2, n)) * pw(2, mod - 2);
    cout << ans % mod;
    return 0;
}
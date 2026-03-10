//
// Created by Psy.C on 2026/3/10.
//
/**
递归计算 2^(x/2) % m
平方得到 (2^(x/2))^2 = 2^x
如果x是奇数，再乘以2

fib(2k) = fib(k)^2 + fib(k-1)^2
fib(2k+1) = fib(k)*fib(k+1) + fib(k-1)*fib(k)
使用map缓存结果避免重复计算

如果m=1，结果总是0
如果k ≥ 2^min(l,63)，输出0（避免溢出）
tot = 2^n % m（2的n次方）
z = fib(n+1) % m（第n+1个斐波那契数）
t = (2^n - fib(n+1)) % m（差值）


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll m;
ll ksm(ll x) {
    if (x == 1) return 2%m;
    ll t = ksm(x/2);
    t = t*t%m;
    if (x&1) t = t*2%m;
    return t;
}

map<ll, ll> mp;
ll fib(ll n) {
    if (mp.contains(n)) return mp[n];
    ll k = n/2;
    if (n%2 == 0)
        return mp[n] = (fib(k)*fib(k)%m + fib(k-1)*fib(k-1)%m)%m;
    return mp[n] = (fib(k)*fib(k+1)%m + fib(k-1)*fib(k)%m)%m;
}

ll n, k, l;
int main() {
    fast;
    cin >> n >> k >> l >> m;
    if (m == 1 || k >= 1ull<<min(l, 63ll)) {
        cout << 0 << '\n';
        return 0;
    }
    mp[0] = 1, mp[1] = 1;
    ll tot = ksm(n), z = fib(n+1), t = (tot - z + m) % m, res = 1;
    for (int i = 0; i < l; ++i) {
        if (k&1) res = res*t%m;
        else res = res*z%m;
        k >>= 1;
    }
    cout << res << '\n';
    return 0;
}
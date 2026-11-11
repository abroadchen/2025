//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
分组前缀和 c[0][i] / c[1][i]
c[1][i]：前 i 位中 '1' 的个数；
c[0][i]：前 i 位中 '0' 的个数。
a+b = 区间长度 len。
用前缀和差得到区间内两类计数，O(1) 每次查询
前缀和预处理 O(n)。
每次查询 O(log mod)（快速幂），总 O(n + q·log mod)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+10, mod = 1e9+7;

ll ksm(ll a, ll n) {
    ll res = 1, base = a % mod;
    while (n) {
        if (n&1) res *= base, res %= mod;
        base *= base, base %= mod;
        n >>= 1;
    }
    return res % mod;
}

int n, q, c[2][N];
string s;
int main() {
    fast;
    cin >> n >> q >> s; s = " " + s;
    c[0][0] = c[1][0] = 0;
    for (int i = 1, x; i <= n; i++) {
        x = s[i] - '0';
        c[x][i] = c[x][i-1] + 1; c[x^1][i] = c[x^1][i-1];
    }
    for (int i = 1, l, r; i <= q; i++) {
        cin >> l >> r;
        ll a = c[1][r] - c[1][l-1], b = c[0][r] - c[0][l-1];//区间内 '1' 数 区间内 '0' 数
        cout << (ksm(2,a+b)-ksm(2,b)+mod)%mod << '\n';
    }
    return 0;
}
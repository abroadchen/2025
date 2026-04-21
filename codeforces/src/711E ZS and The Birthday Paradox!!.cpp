//
// Created by Psy.C on 2026/4/20.
//
/**
检查2^n是否大于等于m
如果2^n >= m，返回true，表示特殊情况
计算_n!中因子2的个数
根据Legendre公式：∑(n/2^i) for i=1 to ∞
计算(2^n - 0) × (2^n - 1) × ... × (2^n - (m-1))
这是排列数A(2^n, m)的计算
b = 2^(n*m): 总的可能组合数
k1 = n: 因子n
k2 = get(m-1): (m-1)!中因子2的个数
k = k1 + k2: 总的调整因子
使用N^k作为调整因子
 */
#include <bits/stdc++.h>
#define int __int128
#define ll long long
using namespace std;
constexpr int mod = 1e6+3, N = 500002;
int n, m;
bool check() {
    int x = 1;
    for (int i = 1; i <= n; ++i) {
        x = x*2ll;
        if (x >= m) return false;
    }
    return true;
}
int ksm(int _n, int k) {
    int ans = 1ll;
    while (k) {
        if (k&1ll) ans = ans*_n%mod;
        _n = _n*_n%mod;
        k >>= 1ll;
    }
    return ans;
}
int sub(int _a, int _b) {
    return (_a%mod - _b%mod + mod)%mod;
}
int get(int _n) {
    int sum = 0;
    for (int i = 1; _n/(1ll<<i) > 0; ++i)
        sum += _n/(1ll<<i);
    return sum;
}

signed main(){
    ll tn, tm;
    cin >> tn >> tm; n = tn; m = tm;
    if (check()) {
        cout << 1 << ' ' << 1 << '\n';
        return 0;
    }
    int a = 1;
    for (int i = 1; i <= m; ++i) {
        a = a*sub(ksm(2, n), i-1) % mod;
        if (a == 0) break;
    }
    int b = ksm(2, n*m), k1 = n, k2 = get(m-1), k = k1 + k2;
    cout << (ll)((b*ksm(N, k)%mod-a*ksm(N, k)%mod+mod)%mod) << ' ' <<
        (ll)(b*ksm(N, k)%mod) << '\n';
    return 0;
}
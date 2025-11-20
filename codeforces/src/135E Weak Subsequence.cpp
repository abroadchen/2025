//
// Created by Psy.C on 2025/11/19.
//
/*
 *k^0 + k^1 + k^2 + ... + k^w = (k^(w+1) - 1) / (k - 1)
 *k^1 + k^2 + ... + k^w = (k^(w+1) - k) / (k - 1)
 *
*根据组合数学的知识，k! / (k-z)! 通常表示：
排列数：从k个不同元素中取出z个元素的排列数
降阶乘：k的z次降阶乘，记作 k^(z) = k!/(k-z)!
 *
 */
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 1e6+5, mod = 1e9+7;
int k;
ll fac[N], inv[N];//乘数组fac和累积逆元数组inv

ll pw(ll x, int y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res*x%mod;
        x = x*x%mod;
        y >>= 1;
    }
    return res;
}

ll solve(int w) {
    ll res = (k == 1 ? w : (pw(k, w+1)-k+mod)%mod*pw(k-1,mod-2)%mod),
    kp = pw(k,w), kinv = pw(k, mod - 2);
    for (int i = 1; i <= k; ++i) {
        if (i <= w) {
            kp = kp * kinv % mod;
            ll v = fac[k] * inv[k - i] % mod;
            res = (res + v * v % mod * kp) % mod;
        } else {
            int z = i - w;
            ll v = fac[k - z] * inv[k - i] % mod;//从 (k-i+w) 个元素中选取 (k-i) 个元素的排列数
            res = (res + v * v % mod * fac[k] % mod * inv[k - z]) % mod;
        }
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>k; inv[1] = 1;
    for (int i = 2; i <= k; ++i) {
        inv[i] = (mod - mod / i * inv[mod % i] % mod + mod) % mod;
    }
    inv[0] = fac[0] = 1;
    for (int i = 1; i <= k; ++i) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = inv[i - 1] * inv[i] % mod;
    }
    int w; cin>>w;
    cout << (solve(w) - solve(w - 1) + mod) % mod << '\n';
    return 0;
}
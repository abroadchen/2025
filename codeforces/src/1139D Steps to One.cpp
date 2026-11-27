//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
np：合数标记表。
pr：素数集合。
mu：莫比乌斯函数。质数 μ = -1，含平方因子 μ = 0，否则由互质性质相乘
用经典公式 inv[i] = (mod - mod/i) * inv[mod%i] % mod 线性求出 1..n 的逆元（O(n)）
求 Σ_{i=2}^{n} μ̄(i) · ⌊n/i⌋ · inv[n−⌊n/i⌋] 类的和
mod + s.mu[i] 是为了把 μ 从 {-1,0,1} 转成 {0,1,2} 用于模运算（避免负值）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=2;i<n;i++)
using namespace std;

constexpr int mod = 1e9+7;

struct sieve {
    vector<bool> np;
    vector<int> pr,mu,inv;
    int n;
    void get() {
        np[1] = 1; mu[1] = 1;
        rep(i,n) {
            if (!np[i]) pr.push_back(i), mu[i] = -1;
            for (int p : pr) {
                if (!(i*p < n)) break;
                np[i*p] = 1;
                if (i%p == 0) { mu[i*p] = 0; break; }
                mu[i*p] = mu[i]*mu[p];
            }
        }
        inv[1] = 1;
        rep(i,n) inv[i] = 1ll*(mod-mod/i)*inv[mod%i]%mod;
    }
    sieve(int _n) {
        n = _n, np.assign(n,0), inv.resize(n);
        pr.clear(), mu.resize(n), get();
    }
};

int main() {
    fast;
    int n; cin >> n;
    sieve s(n+1);
    int ans = 1;
    rep(i,n+1) (ans += mod-1ll*(mod+s.mu[i])%mod*(n/i)%mod*s.inv[n-n/i]%mod)%=mod;
    cout << ans << '\n';
    return 0;
}
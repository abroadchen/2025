//
// Created by Psy.C on 2026/1/30.
//
///将 k 个相同物品放入 n 个盒子的方案数是 C(k+n-1, n-1)
#include <iostream>
#include <map>
#include <ranges>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 16500
#define M 15010
#define mod 1000000007
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    map<int, int> mp;//质因子及其指数
    for (int i = 1, xx; i <= n; ++i) {
        cin >> xx; int x = xx;
        for (int j = 2; j <= sqrt(xx); ++j) {
            if (x % j) continue;
            while (x % j == 0) ++mp[j], x /= j;//统计质因子 j 的个数
        }
        if (x > 1) ++mp[x];//剩余部分大于1，也是质因子
    }
    int g[N], inv[N]; g[0] = 1;
    for (int i = 1; i <= M; ++i) g[i] = static_cast<int>(1ll*g[i-1]*i%mod);// i!
    inv[1] = 1; inv[0] = 1;//i 的逆元
    for (int i = 2; i <= M; ++i) inv[i] = static_cast<int>(1ll*inv[mod%i]*(mod-mod/i)%mod);
    for (int i = 2; i <= M; ++i) inv[i] = static_cast<int>(1ll*inv[i-1]*inv[i]%mod);//阶乘的逆元
    ll ans = 1;
    for (const auto &val: mp | views::values) {
        const int d = n + val - 1, u = n - 1;//C(d, u) = C(n+val-1, n-1)
        (ans*=1ll*g[d]*inv[d-u]%mod*inv[u]%mod) %= mod;
    }
    cout << ans << '\n';
    return 0;
}
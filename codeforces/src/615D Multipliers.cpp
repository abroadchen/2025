//
// Created by Psy.C on 2026/3/25.
//
/**
当底数与模数互质时，指数可以对$\phi(mod)$取模，而当模数为素数时，$\phi(p)=p-1$
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int mod = 1e9+7;
ll dfs(ll a, ll n) {
    return n ? dfs(a*a%mod, n>>1)*(n&1 ? a : 1)%mod : 1;
}
int m;
map<ll, ll> mp;///每个数字及其出现次数
int main() {
    fast;
    cin >> m;//数字个数
    for (int i = 1, p; i <= m; ++i) {
        cin >> p; mp[p]++;
    }
    ll ans = 1, d = 1;//计算指数
    //遍历每个不同的数字及其出现次数
    for (auto v : mp) {
        //va是数字值，vb是该数字的出现次数
        ll va = v.first, vb = v.second;
        ans = dfs(ans, vb+1)*dfs(dfs(va, (vb+1)*vb/2), d) % mod;
        d = d * (vb + 1) % (mod - 1);
    }
    cout << ans;
    return 0;
}
//
// Created by Psy.C on 2026/1/30.
//
/// ksm(2, mod-2) 就是用来替代"除以2"的操作
/**
 *
* x*(x-1)/2：后面x个位置中任选2个的组合数
fac[x-2]：后面x-2个位置的排列数
d[i]：p[i]在剩余数字中的排名，决定了能形成多少逆序对
 *
*d[i]*(d[i]-1)/2：p[i]在剩余数字中前面有d[i]个小于它的数，从中选2个的组合
fac[x]：后面x个位置的所有排列方案
 *
*d[i]：当前位置的贡献权重
fac[x]：后续位置的排列数
sum：前面所有d[j]值的累积和，代表之前的累积影响
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 2000005
#define inf 2000000
#define mod 1000000007
using namespace std;

struct node {
    ll nd[N];
    static ll low_bit(const ll x) { return x & -x; }
    void update(ll x, const ll val) {//位置x处增加val值
        if (x <= 0) return;
        while (x <= inf) {
            nd[x] += val;
            x += low_bit(x);
        }
    }
    [[nodiscard]] ll query(ll x) const {//前x个元素的前缀和
        if (x <= 0) return 0;
        ll res = 0;
        while (x) {
            res += nd[x];
            x -= low_bit(x);
        }
        return res;
    }
} tr;

ll ksm(ll x, ll y) {//x^y % mod，时间复杂度O(log y)
    ll res = 1;
    while (y) {
        if (y&1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

int main() {
    fast;
    ll n, p[N]; cin >> n;
    for (ll i = 1; i <= n; ++i) cin >> p[i];
    ll fac[N]; fac[0] = 1;//阶乘数组，fac[i] = i! % mod
    for (ll i = 1; i <= inf; ++i) fac[i] = fac[i-1]*i%mod;
    ll ans = 0, sum = 0;
    for (ll i = 1, g[N], d[N]; i <= n; ++i) {
        //小于等于p[i]的已处理元素数量  p[i]在剩余未使用数字中的排名
        g[i] = tr.query(p[i]); d[i] = p[i] - g[i] - 1ll;
        const ll x = n - i;
        ans = (ans+1ll*((x-1ll)%mod*x%mod*ksm(2, mod-2)%mod)%mod*((x-1ll)*x%mod*ksm(2, mod-2)%mod)%mod*
            fac[x-2]%mod*d[i]%mod)%mod;
        ans = (ans+1ll*fac[x]%mod*((d[i]*(d[i]-1ll)%mod*ksm(2, mod-2)%mod)%mod)%mod)%mod;
        ans = (ans+1ll*d[i]*fac[x]%mod*sum%mod)%mod;
        sum = (sum+1ll*d[i])%mod;
        tr.update(p[i], 1);//标记p[i]已被使用
    }
    ans = (ans + sum)%mod;
    cout << ans << '\n';
    return 0;
}
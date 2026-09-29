//
// Created by Psy.C on 2026/9/29.
//
/**
计算 a^n mod 1e9+7 的快速幂。
n %= mod-1 是利用费马小定理（mod 为素数，a^(mod-1) ≡ 1），把指数先缩小到 mod-1 以内，加速运算。
实际这里主要是用来算 2^k mod mod
读入一棵 n 个点、n-1 条边的树。
deg[] 记录每个点度数。
度数 == 1 的点记为叶子，统计叶子总数 lf
t = n - lf 表示非叶子（内部）节点数。
a1 = lf * 2^(t+1)：与"叶子"有关的组合项。
a2 = t * 2^t：与"非叶子/内部节点"有关的组合项。
答案 = (a1 + a2) % mod
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+10, mod = 1e9+7;

ll ksm(ll a, ll n) {
    n %= mod - 1;
    ll ret = 1;
    while (n) {
        if (n&1) ret=ret*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return ret;
}

int deg[N], lf;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y; deg[x]++, deg[y]++;
    }
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 1) lf++;
    int t = n - lf;
    ll a1 = lf*ksm(2, t+1) % mod, a2 = t*ksm(2, t) % mod;
    cout << (a1+a2)%mod << '\n';
    return 0;
}
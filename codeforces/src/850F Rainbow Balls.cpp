//
// Created by Psy.C on 2026/9/29.
//
/**
c[x]：值 x 出现的次数（输入 m 个数，c[x]++）。
n：所有输入值之和（n += x）。
f[]：按递推求出的"状态值"
读入 m 个数，统计频次 c[x]，并累加总和 n
每轮从 f[i-1]、f[i] 解出 f[i+1]（线性方程，涉及 (i-1)(n-i)、2i(n-i)、n(n-1) 三类系数，最后除以 (i+1)(n-i)）。
同时把 (1/n)·i·f[i]·c[i] 累进 ans，即"值为 i 的贡献 = 概率(1/n)·i·f[i]·个数(c[i])"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int mod = 1e9+7, N = 1e5+10;

int ksm(int x, int y) {
    return y ? (y&1 ? x*ksm(x, y-1)%mod : ksm(x*x%mod, y/2)) : 1;
}

int c[N], n, f[N], ans;
signed main() {
    fast;
    int m; cin>>m;
    for (int i = 1, x; i <= m; ++i) {
        cin >> x; c[x]++; n += x;
    }
    f[1] = 1ll*(n-1)*(n-1)%mod;
    for (int i = 1; i < N-5; ++i) {
        int t = 2ll*i*(n-i)%mod*f[i]%mod;
        t = (t+mod-1ll*(i-1)*(n-i)%mod*f[i-1]%mod)%mod;
        t = (t+mod-1ll*n*(n-1)%mod)%mod;
        t = t*ksm(i+1, mod-2)%mod*ksm(n-i, mod-2)%mod;
        f[i+1] = t;
        ans = (ans + ksm(n, mod-2)*i%mod*f[i]%mod*c[i])%mod;
    }
    cout << ans << '\n';
    return 0;
}
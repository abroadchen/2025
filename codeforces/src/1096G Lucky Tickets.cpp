//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
当 k=1（只有一个可用位置），直接输出 1。
把 n 减半（题面里的对称计数）。
f[x]=1 表示某些"可用/特殊"位置，t 记录最大索引。
把 f 前面连续的一串 0 全部去掉，整体左移，简化后续 GF 处理，并同步调整 t。
inv 数组：1..t·n 的模逆，用于递推时的除法。
g[0]=1 作初始
定义生成函数 G(x) = ∑ g[i]·x^i，F(x) = ∑ f[i]·x^i。
两个卷积其实源自某个 GF 方程，典型如：
G(x) = 1 + n·x·F'(x)·G(x) - x·G'(x)·F(x) 之类的形式。
逐项看：

tmp += (j+1)·f[j+1]·g[i-j]——这对应 F'(x)·G(x) 的第 i 项系数（因为 (j+1)f[j+1] 正是 F 的导数项，g[i-j] 是 G 的系数）。
乘上 n。
tmp -= (j+1)·g[j+1]·f[i-j]——这对应 G'(x)·F(x) 的第 i 项系数。
g[i+1] = tmp / (i+1)——因为 G'(x) 的系数是 (i+1)g[i+1]，除以 (i+1) 还原出 g[i+1]。
所以这一过程解决的是：

对 GF 方程 G'(x) = n·F'(x)·G(x) - G'(x)·…  或等价的递推，由 f 逐项解出 g 的每个系数。 其中 ans 累加 ∑ g[i]² 作为最终结果
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i = j; i <= k; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e6+5, mod = 998244353;

int n, k, f[N], t, sz, inv[N], g[N];
ll ans = 1;
int main() {
    fast;
    cin >> n >> k;
    if (k == 1) { putchar('1'); return 0; }
    n >>= 1;
    int x;
    rep(i,1,k) { cin >> x; f[x] = 1, t = max(t,x); }
    //找到第一个 1（即 f 开头连续 0 的长度），sz 记录该长度
    for (int i = 0; i <= t && f[i] == 0; ++i) sz = max(sz, i+1);
    if (sz > 0) {
        rep(i,0,t) f[i] = f[i+sz];
        t -= sz;
    }
    inv[1] = g[0] = 1;
    int q = t*n;
    rep(i,2,q) inv[i] = (ll)(mod-mod/i)*inv[mod%i]%mod;
    for (int i = 0; i != q; ++i) {
        int tmp = 0;
        rep(j,0,min(i,t-1)) tmp = (tmp+(ll)(j+1)*f[j+1]%mod*g[i-j])%mod;
        tmp = (ll)tmp*n%mod;
        for (int j = max(0,i-t); j != i; ++j)
            tmp = (tmp-(ll)(j+1)*g[j+1]*f[i-j])%mod;
        g[i+1] = (ll)tmp*inv[i+1]%mod;
        ans += (ll)g[i+1]*g[i+1]%mod;
    }
    cout << ans%mod;
    return 0;
}
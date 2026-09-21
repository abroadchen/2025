//
// Created by Psy.C on 2026/9/21.
//
/**
DP 用两个数组 g（收集状态）和 f（展开状态）交替推进。
涉及大量组合数 C、阶乘 fac/ifac、2 的幂、1/2 幂、match（双阶乘/配对计数）、h[x]（一个生成函数核
构造 pre[1]、pre[2] 前缀和，分别统计区间内 a 值等于 1、等于 2 的个数
match[2k] = 双阶乘 (2k-1)!! = (2k-1)(2k-3)···1，这是 k 对元素完全配对的方案数。
wp[i]=(1/2)^i、pw[i]=2^i
对每个 x，求和 i 从 0 到 x/2：
系数 (x-i) 偶数 ? +1 : -1（带符号，(-1)^(x-i)）。
C(x,2i)：从 x 个中选 2i 个。
match[2i]：那 2i 个的完全配对方案数（2i-1)!!。
pw[i] = 2^i。
组合起来 h[x] 是一个带符号的配对生成函数，和"把 x 个元素中的一部分两两配对"有关
第一阶段：g → f（"配对/去重"展开）
从状态 g[i][p] 出发，枚举 k（与 p 同奇偶，因为排列要合法），把 p 个"可配对元素"中：
选 k 个放到"保留"位置（乘 C(p,k)·fac[k] 即排列 k 个元素），
剩下的 p-k 个两两配对（乘 match[p-k]）。
得到 f[i][k]
第二阶段：f → g（推进到更远位置）
从 f[i][j] 跳到下标 i+j，统计该段内值为 1（c1 个）、值为 2（c2 个）。
枚举 x（决定有多少个"2 被处理掉"），新状态可配对元素数 p = c1 + 2*(c2-x)。
累乘 wp[c2]（(1/2)^c2）、C(c2,x)、h[x]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e3+5, mod = 1e9+7;

inline ll ksm(ll x, ll y) {
    ll res = 1;
    while (true) {
        if (y&1) res=res*x%mod;
        if (!(y>>=1)) return res;
        x=x*x%mod;
    }
}
ll inv(ll x) { return ksm(x, mod-2); }
ll fac[N<<1], ifac[N<<1];
ll C(int x, int y) {
    return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

void get(int mx) {
    fac[0] = 1;
    for (int i = 1; i <= mx; ++i) fac[i] = fac[i-1]*i%mod;
    ifac[mx] = inv(fac[mx]);
    for (int i = mx; i >= 1; --i) ifac[i-1] = ifac[i]*i%mod;
}


int a[N], pre[3][N];
ll wp[N], pw[N], match[N<<1], h[N<<1], f[N][N], g[N][N<<1];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 2; i <= n; ++i) a[i]--;//从 i=2 起每个值减1
    for (int i = 1; i <= n; ++i)
        pre[1][i] = pre[1][i-1]+(a[i]==1), pre[2][i] = pre[2][i-1]+(a[i]==2);
    get(2*n+1); wp[0] = 1, pw[0] = 1;
    for (int i = 1; i <= n; ++i) wp[i] = wp[i-1]*inv(2)%mod, pw[i] = pw[i-1]*2%mod;
    match[0] = 1;
    for (int i = 2; i <= 2*n+2; i += 2) match[i] = match[i-2]*(i-1)%mod;
    for (int x = 0; x <= 2*n+1; ++x)
        for (int i = 0; i <= x/2; ++i)
            (h[x] += (((x-i)&1) ? mod-1 : 1)*C(x, 2*i)%mod*match[2*i]%mod*pw[i]) %= mod;
    f[1][a[1]] = 1;//起点：第1个位置，保留 a[1] 个
    for (int i = 1; i <= n; ++i) {
        for (int p = 0; p <= 2*i+1; ++p) if (g[i][p])
            for (int k = (p&1); k <= min(p, n-i); ++k)
                (f[i][k] += g[i][p]*C(p, k)%mod*match[p-k]%mod*fac[k]) %= mod;
        for (int j = 1; j <= n-i; ++j) if (f[i][j]) {
            //区间(i,i+j]内值为1的个数 区间(i,i+j]内值为2的个数
            int c1 = pre[1][i+j]-pre[1][i], c2 = pre[2][i+j]-pre[2][i];
            for (int x = 0; x <= c2; ++x) {
                int p = c1 + 2*(c2-x);//新的"可配对元素"数量
                (g[i+j][p] += f[i][j]*wp[c2]%mod*C(c2, x)%mod*h[x]) %= mod;
            }
        }
    }
    cout << f[n][0] << '\n';//推进到最后，保留0个
    return 0;
}
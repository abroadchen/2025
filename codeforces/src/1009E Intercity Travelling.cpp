//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
n：数组长度。
a[]：输入的数值。
b[k] = 2^k mod mod：预处理的 2 的幂，用于对子序列数量快速计数。
ans：累加结果。
mod = 998244353：一个常用质数（幂可快速取模，且是 NTT-friendly 的模数）
b[i] = 2^i mod mod，通过递推 b[i] = b[i-1]*2 快速得到。
语义：b[k] 表示"从某 k 个元素中任选（子集）共有 2^k 种方案"——这是下面所有子序列计数的基石
累加位置 i 的元素作为"非子序列首元素"时的贡献。拆解因子：

(n-i)：位置 i 之后有 n-i 个元素。对这部分，首元素要么是 i 前面的某个位置……
b[n-i-1] = 2^(n-i-1)
b[n-i] = 2^(n-i)：位置 i 之后有 n-i 个元素，可自由选择是否加入子序列——2^(n-i) 种。
含义：若 a[i] 是子序列首元素,它后面的任意子集都可以随意加入，共 2^(n-i) 种子序列，其中 a[i] 作为首元素出现。因此 a[i] 的贡献是 a[i] * 2^(n-i)，对所有 i 累加

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 1e6+5, mod = 998244353;

int n, a[N], b[N], ans;
signed main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    b[0] = 1;
    rep(i,n) b[i] = b[i-1]*2%mod;
    rep(i,n-1) ans = (ans+(n-i)*b[n-i-1]%mod*a[i]%mod)%mod;
    rep(i,n) ans = (ans+a[i]*b[n-i]%mod)%mod;
    cout << ans;
    return 0;
}
//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
n ≤ 110（注意 N=110，但 n 实际受 a[i] 长度限制或读入约束）。
b[i] = 2^i mod mod：二进制第 i 位的位权。
读入 a[1..n]，每项为 0/1/2。
f[0][0][0][0]=1：初始状态。
可确证：b[i] 是 2 的幂取模，a[i]∈{0,1,2}，f 初始为 1
i：处理到前 i 位；
j：某种异或/奇偶累计值（0/1）；
k、l：两个进位标志（0/1）。
转移按 a[i+1] 的值分支。整体结构像「两个二进制数相加时逐位决定每位取 0/1/2」，k、l 是两个数的进位，j 是某结果位。

分支 1：if (a[i+1] != 0) ——第 i+1 位可选填 0 以外的更高值……

分支 2：if (a[i+1] != 1) ——第 i+1 位可选填 1 以外的值……
每个转移乘以一个 2 的幂 b[i] 或 b[i-1] 作为方案数（该位可选的取值组合数带来的权重）。
k 为真时，第一位相关转移用 b[i-1]（少一个选择度，因为进位已占了一格选择），否则用 b[i]。
j 的翻转 j^1 表示该步改变了累计的异或/奇偶
最终答案 = 所有 f[n][p][k][l] 之和（要求最终异或累计 j == p），k、l 任意
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=0; i<n; i++)
#define int long long
using namespace std;

constexpr int N = 110, mod = 1e9+7;

int n, p, a[N], b[N], i, j, k, l, f[N][2][2][2], res;
signed main() {
    fast;
    cin >> n >> p; b[0] = 1;
    for (i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = (b[i-1]<<1)%mod;
    }
    f[0][0][0][0] = 1;
    rep(i,n) rep(j,2) rep(k,2) rep(l,2) {
        if (!f[i][j][k][l]) continue;
        int t = f[i][j][k][l];
        if (a[i+1] != 0) {
            if (k) {
                (f[i+1][j][k][l] += t*b[i-1]%mod)%=mod;
                (f[i+1][j^1][k][true] += t*b[i-1]%mod)%=mod;
            }
            else (f[i+1][j^1][k][true] += t*b[i]%mod)%=mod;
        }
        if (a[i+1] != 1) {
            if (l) {
                (f[i+1][j][k][l] += t*b[i-1]%mod)%=mod;
                (f[i+1][j^1][true][l] += t*b[i-1]%mod)%=mod;
            }
            else (f[i+1][j^1][true][l] += t*b[i]%mod)%=mod;
        }
    }
    rep(k,2) rep(l,2) (res += f[n][p][k][l])%=mod;
    cout << res;
    return 0;
}
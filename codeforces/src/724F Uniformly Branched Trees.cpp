//
// Created by Psy.C on 2026/4/24.
//
/**
f[i][j][k]: 可能表示前i个元素，使用j种颜色，限制条件下k的某种状态的数量
g[i][j]: 辅助计算数组
in[i]: i的模逆元缓存
f[1][0][i] = 1: 当只有1个元素且0种颜色限制时，方案数为1

第一层转移:
f[i][j][k] += f[i-l*k][j-l][k-1] * g[k][l]
这像是在统计某种组合方案数，考虑将i分解为若干个大小为k的块
第二层转移:
计算前缀和，f[i][j][k] 变成前缀和形式
g数组更新:
g[i][1] = f[i][d-1][n]
g[i][j] = g[i][j-1] * (f[i][d-1][n] + j - 1) / j
这像是组合数或下降幂的计算

基本情况:
如果n ≤ 2，答案是1
一般情况:
ans = f[n][d][n/2]，这可能是某种对称计数的结果
偶数修正:
当n是偶数且大于2时，减去重复计算的部分
(f[n/2][d-1][n/2]-1)*f[n/2][d-1][n/2]/2 可能是在去除对称重复


时间复杂度: O(n³d) 或 O(n²d²)
空间复杂度: O(n²d)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1007, M = 11;

int mod;
int inv(int x) {
    int i = 1, y = mod - 2;
    for (; y; y>>=1, x=1ll*x*x%mod)
        if (y&1) i = 1ll*i*x%mod;
    return i;
}

int n, d, f[N][M][N], g[N][M], in[M];
int main() {
    fast;
    cin >> n >> d >> mod;
    for (int i = 0; i <= n; ++i) f[1][0][i] = 1;
    for (int i = 1; i <= d; ++i) g[1][i] = 1;
    for (int i = 1; i <= d; ++i) in[i] = inv(i);
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= d; ++j) {
            for (int k = 1; k < i; ++k)
                for (int l = 1; l <= j && l*k <= i; ++l)
                    f[i][j][k] = (f[i][j][k] + 1ll*f[i-l*k][j-l][k-1]*g[k][l])%mod;
            for (int k = 1; k <= n; ++k)
                f[i][j][k] = (f[i][j][k] + f[i][j][k-1])%mod;
        }
        g[i][1] = f[i][d-1][n];
        for (int j = 2; j <= d; ++j)
            g[i][j] = 1ll*g[i][j-1]*(f[i][d-1][n] + j - 1)%mod*in[j]%mod;
    }
    int ans;
    if (n <= 2) ans = 1; else ans = f[n][d][n/2];
    if (n > 2 && !(n&1))
        ans = (ans - 1ll*(f[n/2][d-1][n/2]-1)*f[n/2][d-1][n/2]%mod*in[2]%mod+mod)%mod;
    cout << ans << '\n';
    return 0;
}
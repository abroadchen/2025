//
// Created by Psy.C on 2026/3/12.
//
/**
c[N][N]: 存储组合数C(i,j)的二维数组
f[N][N]: 动态规划数组，存储第二类斯特林数S(i,j)
C(i,0)表示从i个元素中选0个的方法数，为1
C(i,i)表示从i个元素中选i个的方法数，为1
从i个元素中选j个 = 不选第i个元素的情况 + 选第i个元素的情况

S(0,0)=1
第二类斯特林数S(n,k)表示将n个不同元素划分为k个非空子集的方法数
S(i,j) = j*S(i-1,j) + S(i-1,j-1)
递推思路：
j*S(i-1,j)：将第i个元素放入已有的j个子集中之一
S(i-1,j-1)：将第i个元素单独作为一个新子集
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 4005, mod = 1e9+7;
ll n, c[N][N], f[N][N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) c[i][0] = c[i][i] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j < i; ++j)
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            f[i][j] = (1ll*f[i-1][j]*j%mod + f[i-1][j-1])%mod;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= i; ++j)
            ans = (ans + f[i][j]*c[n][i]) % mod;
    cout << ans << '\n';
    return 0;
}
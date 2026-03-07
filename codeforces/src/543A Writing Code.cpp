//
// Created by Psy.C on 2026/3/7.
//
/**
n：物品数量
m：阶段数（或某种限制）
b：背包容量
mod：模数
v[N]：存储物品的价值/重量
dp[2][N][N]：三维动态规划数组（滚动数组优化）
flag：滚动数组的索引（0或1）
对于每个物品i，首先在dp[flag][i][v[i]]位置加1（表示选择当前物品）
然后计算前缀和，dp[flag][i][j]表示考虑前i个物品，容量为j时的方案数

循环m-1次，每次代表一个阶段
flag ^= 1：切换滚动数组（0变1，1变0）
对于每个物品i和容量j：
dp[flag][i][j] = dp[flag][i-1][j]：继承不选当前物品的方案数
如果容量足够(j >= v[i])，再加上选择当前物品的方案数
dp[flag^1][i][j-v[i]]：上一阶段用容量j-v[i]的方案数
所有运算都在模mod意义下
在最后一阶段，考虑所有物品，所有容量0到b的方案数总和
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 505;
int n, m, b, mod, v[N], dp[2][N][N], flag;
int main() {
    fast;
    cin >> n >> m >> b >> mod;
    for (int i = 1; i < n+1; ++i) cin >> v[i];
    for (int i = 1; i < n+1; ++i) {
        dp[flag][i][v[i]]++;
        for (int j = 0; j < m+1; ++j)
            dp[flag][i][j] += dp[flag][i-1][j];
    }
    for (int x = 1; x < m; ++x) {
        flag ^= 1;
        for (int i = 1; i < n+1; ++i)
            for (int j = 0; j < b+1; ++j) {
                dp[flag][i][j] = dp[flag][i-1][j];
                if (j >= v[i])
                    dp[flag][i][j] = (dp[flag][i][j]+dp[flag^1][i][j-v[i]])%mod;
            }
    }
    int sum = 0;
    for (int j = 0; j < b+1; ++j) sum = (sum+dp[flag][n][j])%mod;
    cout << sum << '\n';
    return 0;
}
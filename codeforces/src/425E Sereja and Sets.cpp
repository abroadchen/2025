//
// Created by Psy.C on 2026/2/4.
//
/**
* 转移逻辑：
i：上一个选择的行号
j：已选择的连通块数量
k：当前选择的行号（k > i）
j+1：当前连通块数量
转移方程：
f[i][j]：之前的方案数
p[i*(k-i)]：第i+1到k行的前i列的任意选择方案数
(p[k-i]-1+mod)%mod：第i+1到k行的后(k-i)列至少选择一个的方案数
(p[k-i]-1) 表示非空子集
f[i][j] * (前i列的任意选择) * (后(k-i)列的非空选择)
 *
*枚举最后一行的位置
f[i][m]：选择m个连通块的方案数
p[i*(n-i)]：剩余位置的任意选择方案数
 *
*预处理：O(n²)
DP转移：O(n³)
答案计算：O(n)
总体：O(n³)
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 505
#define mod 1000000007
using namespace std;


signed main() {
    fast;
    int n, m; cin >> n >> m;
    int p[N*N]{}; p[0] = 1;
    for (int i = 1; i <= n*n; ++i) p[i] = (p[i-1]+p[i-1])%mod;//2^i
    int f[N][N]{}; f[0][0] = 1;//前i行中选择j个连通块的方案数
    for (int i = 0; i < n; ++i) for (int j = 0; j <= i; ++j)
        for (int k = i + 1; k <= n; ++k)
            f[k][j+1] = (f[k][j+1] + f[i][j]*p[i*(k-i)]%mod*(p[k-i]-1+mod)%mod)%mod;
    int ans = 0;
    for (int i = m; i <= n; ++i)
        ans = (ans + f[i][m]*p[i*(n-i)]%mod)%mod;
    cout << ans << '\n';
    return 0;
}
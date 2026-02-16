//
// Created by Psy.C on 2026/2/16.
//
/**
r, g: 红球和绿球数量
d: 最大层数
dp[2][N]: 滚动数组，节省空间
等差数列求和 1+2+...+d = d*(d+1)/2 ≤ r+g
解不等式得：d ≤ (-1 + √(1+8*(r+g))) / 2

滚动数组技巧：
i&1: i%2 的位运算优化
dp[0] 和 dp[1] 交替使用，节省空间
状态转移：
dp[i][j]: 用前i层放置j个红球的方案数
dp[i&1][j] = dp[(i-1)&1][j]: 不在第i层放红球
if (j-i >= 0) dp[i&1][j] += dp[(i-1)&1][j-i]: 在第i层放i个红球

d*(d+1)/2: 前d层总共能放的球数
d*(d+1)/2-g: 至少需要放的红球数
max(0, d*(d+1)/2-g): 确保非负

O(d * r)，其中d ≈ √(r+g)
总体约为 O(√(r+g) * r)
 */
#include <bits/stdc++.h>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-5
using namespace std;
constexpr int N = 200005, mod = 1e9+7;
int r, g, d, dp[2][N];

int main() {
    fast;
    cin >> r >> g;
    d = floor((-1.+sqrt(1.+8.*(r+g))+eps)/2.); dp[0][0] = 1;//0层0红球的方案数为1
    for (int i = 1; i <= d; ++i)
        for (int j = 0; j <= r; ++j) {
            dp[i&1][j] = dp[(i-1)&1][j];
            if (j-i >= 0) dp[i&1][j] += dp[(i-1)&1][j-i];
            dp[i&1][j] %= mod;
        }
    int ans = 0;
    for (int i = max(0, d*(d+1)/2-g); i <= r; ++i)
        ans = (ans + dp[d&1][i]) % mod;
    cout << ans << '\n';
    return 0;
}
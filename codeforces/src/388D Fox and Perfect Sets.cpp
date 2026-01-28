//
// Created by Psy.C on 2026/1/28.
//
/**
* p2[N]: 2的幂次数组
d[N]: n的二进制表示
cnt: 二进制位数
dp[N][N][2]: DP状态数组
p2[0] = 1: 2^0 = 1
 *
*状态转移分析：
[i][j][0]: 第i位，j个1，不紧贴上界
[i][j][1]: 第i位，j个1，紧贴上界
转移1: dp[i+1][j+1][0] += dp[i][j][0]

从不紧贴状态转移，当前位填1
转移2: dp[i+1][j][0] += dp[i][j][0] * p2[j]

从不紧贴状态转移，当前位填0，乘以2^j（可能的组合数）
转移3: if (d[i+1]==1) dp[i+1][j+1][1] += dp[i][j][1]

当上界允许时，从紧贴状态转移，当前位填1
转移4: dp[i+1][j][d[i+1]==0] += dp[i][j][1] * (...)

从紧贴状态转移到不紧贴状态
转移5: if (d[i+1]==1) dp[i+1][j][1] += dp[i][j][1] * (...)

从紧贴状态转移到紧贴状态

dp[cnt][i][0]: 处理完所有位，有i个1，不紧贴上界的方案数

 *
*时间复杂度
O(log²n)，其中log n是二进制位数
空间复杂度
O(log²n)，用于DP数组
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 110
#define mod 1000000007
using namespace std;

signed main() {
    fast;
    int n; cin >> n;
    int p2[N], d[N], cnt = 0, dp[N][N][2]; p2[0] = 1;
    for (int i = 1; i <= 100; ++i) p2[i] = p2[i-1]*2%mod;//2^i
    while (n != 0) d[++cnt] = n % 2, n /= 2;//将n转换为二进制表示，存储在 d[1..cnt] 中
    reverse(d + 1, d + cnt + 1);//使其高位在前
    dp[0][0][1] = 1;//处理到第i位，有j个1，k表示是否紧贴上界的方案数
    for (int i = 0; i < cnt; ++i) for (int j = 0; j <= i; ++j) {//枚举当前已有的1的个数
        dp[i+1][j+1][0] = (dp[i+1][j+1][0]+dp[i][j][0])%mod;
        dp[i+1][j][0] = (dp[i+1][j][0]+dp[i][j][0]*p2[j])%mod;
        if (d[i+1]==1) dp[i+1][j+1][1] = (dp[i+1][j+1][1]+dp[i][j][1])%mod;
        dp[i+1][j][d[i+1]==0] = (dp[i+1][j][d[i+1]==0]+dp[i][j][1]*(j==0?1:p2[j-1]))%mod;
        if (d[i+1]==1) dp[i+1][j][1] = (dp[i+1][j][1]+dp[i][j][1]*(j==0?0:p2[j-1]))%mod;
    }
    int sum = 0;
    for (int i = 0; i <= cnt; ++i) sum = (sum + dp[cnt][i][0] + dp[cnt][i][1]) % mod;
    cout << sum;
    return 0;
}
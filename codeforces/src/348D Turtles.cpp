//
// Created by Psy.C on 2026/1/14.
//
/**
* n, m: 网格维度（行数和列数）
mp[N][N]: 表示网格地图的二维数组（1 = 可通行，0 = 障碍物）
s[N]: 读取每行的临时字符数组
dp[N][N], t[N][N]: 初始化为零的DP表
 *
*从1到n循环遍历每一行
将整行作为字符串s读取
转换每个字符：如果是.（可通行），设置mp[i][j+1] = 1
重要: 使用1索引坐标表示网格（j+1）
 *
*初始化起点：到达(1,1)的一种方法
计算从左上角到每个单元格的路径数，只使用向右/向下移动
仅当单元格可通行时(mp[i][j] == 1)才计算
路径数 = 上方来的路径 + 左边来的路径
 *
*dp[n-1][m]*t[n][m-1]: 一条路径从 (1,1) 到 (n-1,m)，另一条从 (1,1) 到 (n,m-1) 的路径对总数

dp[n][m-1]*t[n-1][m]: 一条路径从 (1,1) 到 (n,m-1)，另一条从 (1,1) 到 (n-1,m) 的路径对总数

最终结果: 通过容斥原理计算不相交路径的数量
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 3005
#define mod 1000000007
using namespace std;



int main() {
    fast;
    int n, m, mp[N][N]; cin >> n >> m; char s[N];
    ll dp[N][N] = {}, t[N][N] = {};
    memset(mp, 0, sizeof(mp));
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        for (int j = 0; j < m; ++j) if (s[j] == '.') mp[i][j+1] = 1;
    }
    dp[1][1] = 1; t[1][1] = 1;
    for (int i = 1; i <= n; ++i) for (int j = 2; j <= m; ++j) if (mp[i][j]) {
        dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % mod;
    }
    for (int i = 2; i <= n; ++i) for (int j = 1; j <= m; ++j) if (mp[i][j]) {
        t[i][j] = (t[i-1][j] + t[i][j-1]) % mod;
    }
    cout << ((dp[n-1][m]*t[n][m-1])%mod-(dp[n][m-1]*t[n-1][m])%mod+mod)%mod;
    return 0;
}
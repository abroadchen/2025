//
// Created by Psy.C on 2026/2/3.
//
/**
* vector t(...)：创建二维向量 t
vector(n+1, 0)：创建大小为 n+1、初始值为 0 的一维向量
vector t(m+1, ...)：创建 m+1 行，每行是 vector(n+1, 0)
结果：创建 (m+1) × (n+1) 的二维数组，索引从1开始使用，初始化为0
 *
*dp[j]：当前列的旧值（上一行的结果）
dp[j-1]：前一列的当前值
max(dp[j], dp[j-1])：取当前位置或前一位置的最大值
+ t[i][j]：加上当前格子的值
当前位置的最大和 = max(从上方来, 从左方来) + 当前值

时间复杂度：O(m×n) 空间复杂度：O(m×n + n) ≈ O(m×n)
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= (n); ++i)
using namespace std;


int main() {
    fast;
    int m, n, i, j; cin >> m >> n;
    vector t(m+1, vector(n+1, 0));
    rep(i,m) rep(j,n) cin >> t[i][j];
    vector dp(n+1, 0);
    rep(i,m) {//逐行处理
        rep(j,n) dp[j] = max(dp[j], dp[j-1]) + t[i][j];//逐列更新
        cout << dp[n] << ' ';//第i行处理完后的最大路径和
    }
    cout << '\n';
    return 0;
}
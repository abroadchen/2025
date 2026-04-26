//
// Created by Psy.C on 2026/4/25.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1007;
int n, m, a[N][N], dp[N][N][4], ans;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) cin >> a[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (!a[i][j]) {//只对值为0的位置进行处理
                dp[i][j][0] = dp[i-1][j][0]|a[i-1][j];//向上
                dp[i][j][1] = dp[i][j-1][1]|a[i][j-1];//向左
                ans += dp[i][j][0] + dp[i][j][1];
            }
    for (int i = n; i >= 1; --i)
        for (int j = m; j >= 1; --j)
            if (!a[i][j]) {
                dp[i][j][2] = dp[i+1][j][2]|a[i+1][j];//向下
                dp[i][j][3] = dp[i][j+1][3]|a[i][j+1];//向右
                ans += dp[i][j][2] + dp[i][j][3];
            }
    cout << ans;
    return 0;
}
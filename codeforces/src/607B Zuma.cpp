//
// Created by Psy.C on 2026/3/22.
//
/**
单个元素的区间只需要1次操作
len: 枚举区间长度，从2到n
l: 枚举左端点
r: 右端点，r = l + len - 1
状态转移:

如果a[l] == a[r]且区间长度>2：dp[l][r] = dp[l+1][r-1]
两端相同，可以同时消除，只需考虑内部区间
如果a[l] == a[r]且区间长度=2：dp[l][r] = 1
两个相同元素可以一次性消除
枚举分割点k，尝试dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r])
将区间[l,r]分成[l,k]和[k+1,r]两部分分别处理
时间复杂度：O(n³)，空间复杂度：O(n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 505;
int n, a[N], dp[N][N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    memset(dp, 0x3f, sizeof dp);
    for (int i = 1; i <= n; ++i) dp[i][i] = 1;
    for (int len = 2; len <= n; ++len)
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            if (a[l] == a[r] && len > 2)
                dp[l][r] = dp[l+1][r-1];
            else if (a[l] == a[r]) dp[l][r] = 1;
            for (int k = l; k < r; ++k)
                dp[l][r] = min(dp[l][r],
                    dp[l][k] + dp[k+1][r]);
        }
    cout << dp[1][n] << '\n';
    return 0;
}
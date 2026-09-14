//
// Created by Psy.C on 2026/9/14.
//
/**
把相邻整数的差取绝对值，得到新数组
之后所有 DP 都基于这个长度为 n-1 的差值数组进行。原数组最后一位 a[n] 不再参与
dp[i][0]：以 a[i] 结尾、且当前该元素被赋予负号（-）‍的最佳子段和。
dp[i][1]：以 a[i] 结尾、且当前该元素被赋予正号（+）‍的最佳子段和。
之所以分两维，是因为序列要求正负号交替——即"选中的相邻元素一正一负"
dp[1][1] = a[1]：从第 1 位、符号为 + 开始。
dp[1][0] = 0：从第 1 位、符号为 - 开始 → 视作"不选 / 空前缀"，贡献 0

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
ll a[N], dp[N][2];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i < n; ++i) a[i] = abs(a[i]-a[i+1]);
    dp[1][1] = a[1]; dp[1][0] = 0;
    ll ans = a[1];
    for (int i = 2; i < n; ++i) {
        if (i%2) {//i 为奇数
            dp[i][0] = dp[i-1][0] - a[i];//负号：延续负号段 + 减 a[i]
            dp[i][1] = max(a[i], dp[i-1][1] + a[i]);//正号：延续正号段 + 加 a[i]
            ans = max(ans, max(dp[i][0], dp[i][1]));
        } else {
            dp[i][0] = max(a[i], dp[i-1][0] + a[i]);//负号：从 i 重新开始 或 延续 + 减(加) a[i]
            dp[i][1] = dp[i-1][1] - a[i];//正号：延续正号段 - a[i]
            ans = max(ans, max(dp[i][0], dp[i][1]));
        }
    }
    cout << ans << '\n';
    return 0;
}
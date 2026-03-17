//
// Created by Psy.C on 2026/3/16.
//
/**
dp[i+1] 表示以 a[i+1] 结尾的最长连续非降序列的长度
如果 a[i] <= a[i+1]，则可以延续前面的序列，长度为 dp[i] + 1
否则，重新开始计数，长度为 0
dp 记录的是我们"走过"了多少个相邻元素之间的间隔，而序列长度比间隔数多1
时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, a[N], dp[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n-1; ++i) {
        dp[i+1] = a[i] <= a[i+1] ? dp[i] + 1 : 0;
        ans = max(ans, dp[i+1]);
    }
    cout << ans + 1 << '\n';
    return 0;
}
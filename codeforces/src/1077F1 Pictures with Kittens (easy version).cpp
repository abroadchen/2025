//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
n个数, k=最多连续间隔, x=最多选几个
dp[i][j] = 从前 i 个数中，选择 j 个元素，且最后一个被选的是 a[i]（或"以 i 结尾"）时的最大和
枚举当前位置 i，已选数量 j（不超过 x）。
从 p ∈ [i-k, i-1] 转移：dp[i][j] = max(dp[p][j-1] + a[i])。
含义：选上 a[i] 作为第 j 个元素，且上一个被选元素的下标 p 与 i 的距离不超过 k
最后在 [n-k+1, n] 区间内取 dp[i][x]，即最后一个被选的元素距离 n 不超过 k（保证最后一个元素和末尾之间留出 k 的间隙）。
若 < 0（无解，因为初始化为负无穷），输出 -1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 205, inf = 0x3f3f3f3f;

int n, k, x, a[N], dp[N][N];
void solve() {
    cin >> n >> k >> x;
    rep(i,n) cin >> a[i];
    memset(dp, -0x3f, sizeof dp); dp[0][0] = 0;
    rep(i,n) rep(j,min(i,x))
        for (int p = max(0ll,i-k); p <= i-1; p++)
            dp[i][j] = max(dp[i][j], dp[p][j-1]+a[i]);
    int ans = -inf;
    for (int i = max(0ll,n-k)+1; i <= n; i++)
        ans = max(ans, dp[i][x]);
    if (ans < 0) ans = -1;
    cout << ans << '\n';
}


signed main() {
    fast;
    solve();
    return 0;
}
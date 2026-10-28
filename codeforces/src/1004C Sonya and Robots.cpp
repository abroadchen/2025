//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
从右往左遍历。
vis[x] 标记元素 x 是否在当前位置之后出现过。
dp[i] = 从下标 i 到 n 这一段里不同元素的个数。
若 a[i] 在后缀中已出现过，则 dp[i] 与后面的 dp[i+1] 相同（不增加新种类）。
否则说明 a[i] 是该后缀中首次暴露的元素，不同元素数 +1，并标记 vis[a[i]]，dp[i] = dp[i+1]+1。
递推边界 dp[n+1]=0（空后缀没有不同元素）。
dp[i] 的最终含义：a[i..n] 中不同值的种类数
从左往右遍历。
v2[x] 标记元素 x 是否已作为"首次出现"处理过。
只用 v2 保证每个元素只在它第一次出现的位置被计入一次（后面的重复出现不重复加）。
对每个"首次出现"位置 i，累加 dp[i+1] = 从 i+1 到 n 的不同元素个数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 3e5+5;

int n, a[N], vis[N], v2[N];
ll dp[N];

void init() {
    memset(dp, 0, sizeof(dp));
    memset(a, 0, sizeof(a));
    memset(vis, 0, sizeof(vis));
    memset(v2, 0, sizeof(v2));
}

int main() {
    fast;
    while (cin >> n) {
        init();
        for (int i = 1; i <= n; i++) cin >> a[i];
        dp[n+1] = 0;
        for (int i = n; i >= 1; i--) {
            if (vis[a[i]] != 0) dp[i] = dp[i+1];
            else {
                dp[i] = dp[i+1] + 1;
                vis[a[i]] = 1;
            }
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            if (!v2[a[i]]) {
                ans += dp[i+1];
                v2[a[i]] = 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
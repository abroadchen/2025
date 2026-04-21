//
// Created by Psy.C on 2026/4/20.
//
/**
n: 元素总数
m: 颜色种类数
k: 不同颜色段数
c[N]: 每个元素的预设颜色（0表示未预设）
p[N][N]: 每个元素染成每种颜色的代价
dp[i][j][l] 表示：前i个元素中，恰好形成j段连续相同颜色序列，且第i个元素染成颜色l的最小代价

如果第1个元素已经有预设颜色，那么dp[1][1][c[1]] = 0
否则，对所有颜色i，dp[1][1][i] = p[1][i]（染成该颜色的代价）

遍历所有颜色，找出前n个元素恰好分成k段的最小代价
如果仍为无穷大，说明无法达成目标，输出-1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 107;
constexpr ll inf = 1e18;
int n, m, k, c[N], p[N][N], i, j, l, q;
ll dp[N][N][N];
int main() {
    fast;
    cin >> n >> m >> k;
    for (i = 1; i <= n; ++i) cin >> c[i];
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            cin >> p[i][j];
    for (i = 0; i <= n; ++i)
        for (j = 0; j <= k; ++j)
            for (l = 0; l <= m; ++l)
                dp[i][j][l] = inf;
    if (c[1]) dp[1][1][c[1]] = 0;
    else
        for (i = 1; i <= m; ++i) dp[1][1][i] = p[1][i];
    for (i = 2; i <= n; ++i)//遍历每个元素
        for (j = 1; j <= k; ++j) {//遍历段数
            if (c[i]) {//当前元素有预设颜色
                //同色段：延续前一段的颜色
                dp[i][j][c[i]] = min(dp[i][j][c[i]], dp[i-1][j][c[i]]);
                //异色段：新开一个颜色段
                for (l = 1; l <= m; ++l)
                    if (l != c[i]) dp[i][j][c[i]] = min(dp[i][j][c[i]], dp[i-1][j-1][l]);
            } else {
                //尝试给当前元素染成颜色l
                for (l = 1; l <= m; ++l) {
                    //同色段：延续前一段的颜色l
                    dp[i][j][l] = min(dp[i][j][l], dp[i-1][j][l]+p[i][l]);
                    //异色段：从其他颜色转到颜色l，形成新的段
                    for (q = 1; q <= m; ++q)
                        if (q != l)
                            dp[i][j][l] = min(dp[i][j][l], dp[i-1][j-1][q]+p[i][l]);
                }
            }
        }
    ll mn = inf;
    for (i = 1; i <= m; ++i) mn = min(mn, dp[n][k][i]);
    if (mn != inf) cout << mn << '\n'; else cout << "-1\n";
    return 0;
}
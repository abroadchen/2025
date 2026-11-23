//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
区间 [i,j] 同时只涂一个点（i==j）时花费 0（单个点算已经就绪）。
其余 inf（未到达）
从当前已涂区间 [i,j] 向外扩展一格（左或右），新端点颜色若与当前端点颜色不同则代价 +1。

c = 当前区间的边界颜色（若走左边 k=0 则边界是 a[i]，走右边 k=1 则边界是 a[j]）。
向左扩：转移到 dp[i-1][j][0]，若 c != a[i-1] 则代价加 1。
向右扩：转移到 dp[i][j+1][1]，若 c != a[j+1] 则代价加 1。
upd 是取 min 的封装。
之所以需要第三维 k（用 0/1 记录扩展方向），是因为从两端扩展时，"当前端点颜色"取决于上一次是从哪端扩进来的，用来正确判断与下一次扩展的新端点是否同色
整个区间 [1,n] 已涂完，取最后一步从左端或从右端收尾的最小值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 5005, inf = 0x3f3f3f3f;

int n, dp[N][N][2];
void init() { rep(i,n) rep(j,n) dp[i][j][0] = dp[i][j][1] = i == j ? 0 : inf; }
void upd(int &a, int b) { a = min(a, b); }

int a[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i]; init();
    rep(j,n) for (int i = j; i >= 1; i--) for (int k = 0; k <= 1; k++) {
        int c = k ? a[j] : a[i];
        if (i > 1) upd(dp[i-1][j][0],dp[i][j][k]+(c!=a[i-1]));
        if (j < n) upd(dp[i][j+1][1],dp[i][j][k]+(c!=a[j+1]));
    }
    cout << min(dp[1][n][0],dp[1][n][1]) << '\n';
    return 0;
}
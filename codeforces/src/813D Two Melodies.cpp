//
// Created by Psy.C on 2026/9/21.
//
/**
dp[i][j]：某种状态（典型：已处理到两端 i、j 的最长合法长度）。
mxm[r]：记录所有 dp[i][k] 中 modulus7=r 的最大值。
mxn[v]：记录值为 v 的所有下标中 dp 的最大值
外层 i 从 0 到 n，内层 j 从 i+1 到 n，不断扩展右侧 j，并用 dp[i][j] 与 dp[j][i] 对称维护。

关键转移用 max4 取四类来源再 +1：

dp[i][0]：基准（空/初始状态）。
mxm[a[j]%7]：与 a[j] 模 7 同余的已处理节点中的最大 dp。
mxn[a[j]-1]、mxn[a[j]+1]：与 a[j] 数值相邻(差 1)的节点中的最大 dp。
即：往序列末尾追加 a[j] 时，要求它与已选序列末端的值满足模7同余 或 数值连续(±1)，取满足条件时的最长长度 +1。
由于转移只依赖前缀信息（mxm/mxn 在 j 用完后立即更新），使得总复杂度 O(n²)（n ≤ 5000）可行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e3+10, M = 1e5+1e2;
int n, a[N];
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
}
int max4(int a, int b, int c, int d) {
    return max(max(a, b), max(c, d));
}
void up(int& x, int y) { x = max(x, y); }

int dp[N][N], mxm[7], mxn[M];
void get() {
    int ans = -1;
    memset(dp, 0, sizeof dp);
    for (int i = 0; i <= n; ++i) {
        memset(mxn, 0, sizeof mxn);
        memset(mxm, 0, sizeof mxm);
        for (int j = 1; j <= i; ++j) {
            up(mxm[a[j]%7], dp[i][j]);
            up(mxn[a[j]], dp[i][j]);
        }
        for (int j = i+1; j <= n; ++j) {
            dp[i][j] = max4(dp[i][0], mxm[a[j]%7], mxn[a[j]-1], mxn[a[j]+1])+1;
            up(mxm[a[j]%7], dp[i][j]);
            up(mxn[a[j]], dp[i][j]);
            up(ans, dp[i][j]);
            dp[j][i] = dp[i][j];//对称状态
        }
    }
    cout << ans << '\n';
}

int main() {
    fast;
    in(); get();
    return 0;
}
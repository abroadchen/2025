//
// Created by Psy.C on 2026/9/24.
//
/**
读入订单数 n、司机数 k、公共出发点 S。
a[] 订单位置、b[] 每辆车（在城里的）初始位置。
排序：把订单和司机都排序。这是关键的贪心前提——最优分配一定可保持相对顺序（排序后，把第 i 个订单分配给某个司机时，只考虑已排序的顺序），使得可用简单 DP。
dp[i][j] 含义：考虑了前 i 个订单、并且允许使用前 j 个司机时，完成这些订单所需的最小"最大单车耗时"。
初始全 inf；dp[0][i] = 0：没有订单时，无论多少司机，最大耗时都是 0。
外层：处理每个订单 i。
内层：j 从 i 到 k（因为要送 i 个订单至少需要 i 个司机，所以 j 从 i 开始）。
转移分两种选择，取较小者：

选择 1：不用第 j 个司机
前 i 个订单只用前 j-1 个司机完成，第 j 个司机完全不用
选择 2：用第 j 个司机送第 i 个订单
前 i-1 个订单由前 j-1 个司机完成（耗时 dp[i-1][j-1]）。
第 i 个订单由第 j 个司机送：该司机从 S 出发 → 到自己的位置 b[j]（耗时 abs(b[j]-S)）‍→ 再送往订单 a[i]（耗时 abs(a[i]-b[j])），总耗时 abs(a[i]-b[j]) + abs(b[j]-S)。
整个分配的最大耗时 = max(前面 i-1 单的最大耗时, 当前这单司机耗时) → 取 max。
而我们要的是"全部过程中的最小值" → 两种选择取 min。
这样 dp[i][j] 就是在"前 j 个司机处理前 i 个订单"前提下的最小可能最大耗时
用全部 k 个司机送完全部 n 个订单时，最大的那台车的耗时最小可能值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2005, inf = 2e9+10;


int n, k, S, a[N], b[N], dp[N][N];
int main() {
    fast;
    cin >> n >> k >> S;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= k; ++i) cin >> b[i];
    sort(a+1, a+n+1); sort(b+1, b+k+1);
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= k; ++j) dp[i][j] = inf;
    for (int i = 0; i <= k; ++i) dp[0][i] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= k; ++j)
            dp[i][j] = min(dp[i][j-1], max(dp[i-1][j-1], abs(a[i]-b[j])+abs(b[j]-S)));
    cout << dp[n][k] << '\n';
    return 0;
}
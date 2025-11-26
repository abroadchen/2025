//
// Created by Psy.C on 2025/11/25.
//
/*
*n: 任务数量
k: 允许跳过的任务数
t[i]: 第i个任务的开始时间
d[i]: 第i个任务的持续时间
dp[i][j]: 前i个任务中跳过j个任务时的最小结束时间
 *
 *执行第i个任务
*dp[i-1][j] + d[i]：紧接着前一个任务执行
t[i] + d[i] - 1：在任务规定时间开始执行 //第i个任务的结束时间
取较大值确保不早于任务开始时间
 *跳过第i个任务（如果还有跳过名额）
 *继承跳过j-1个任务时的状态
 *
*i-1: 考虑前i-1个任务
j-1: 允许跳过j-1个任务
整体含义: 在前i-1个任务中跳过j-1个任务时能达到的最小结束时间
 *
 *执行当前任务
 *在前i-1个任务跳过j个的基础上，执行第i个任务
 *跳过当前任务（如果还有跳过名额）
*在前i-1个任务跳过j-1个的基础上，跳过第i个任务
这意味着总共跳过j个任务（前j-1个 + 当前这1个）
 *
 *
*dp[i-1][j]: 前i-1个任务中跳过j个任务时的结束时间
d[i]: 第i个任务的持续时间
dp[i-1][j] + d[i]: 紧跟在前一个任务之后执行第i个任务的结束时间
 *min(dp[i][j], dp[i-1][j-1]) 表示在执行当前任务和跳过当前任务两种策略中选择更优的一种
 *
*t[i + 1]: 第(i+1)个任务的开始时间
dp[i][k]: 前i个任务中跳过k个任务时的最小结束时间
dp[i][k] + 1: 前i个任务完成后，下一个可用时间点
t[i + 1] - (dp[i][k] + 1): 从任务完成到下一个任务开始的空闲时间
*对于每个任务分割点i，计算前i个任务完成后到第(i+1)个任务开始前的空闲时间
在所有这些空闲时间段中找到最大的一个
 *
 *
*时间复杂度：O(n × k)
空间复杂度：O(n × k)
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 4005;
int n, k;
vector<int> t(N), d(N);

int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> t[i] >> d[i];
    t[n + 1] = 86401;//设置结束哨兵（86400秒 = 24小时）
    if (n == 0) { cout << "86400" << '\n'; return 0; }
    vector<vector<int>> dp(N, vector<int>(N, 0x3f));
    dp[0][0] = 0;//0个任务，跳过0个，时间为0
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= min(i, k); ++j) {
            dp[i][j] = max(dp[i - 1][j] + d[i], t[i] + d[i] - 1);
            if (j > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = max(ans, t[i + 1] - dp[i][k] - 1);
    cout << ans << '\n';
    return 0;
}
//
// Created by Psy.C on 2025/12/20.
//
/*
*声明三维DP数组dp[N][N][N]，用于存储概率值
初始化dp[0][0][0] = 1.0，表示初始状态的概率为1
 *
*i：处理前i个元素
j：当前状态下的某种计数（不超过i）
k：累积的某种值（不超过p）
状态转移方程：
dp[i][j][k] += dp[i-1][j][k] * (i - j) / i：
表示第i个元素不被选中的情况
概率为(i-j)/i，即从i个元素中不选择特定j个元素的概率  在前i个位置中，已经有j个位置被选中了，剩下(i-j)个位置未被选中
if (k - a[i] >= 0) dp[i][j][k] += dp[i-1][j-1][k-a[i]] * j / i：
表示第i个元素被选中的情况
前提是k >= a[i]（确保索引非负） 当前的目标累积值必须至少包含第i个元素的价值
概率为j/i，即从i个元素中选择特定元素的概率
 *
*遍历所有有效的i（1到n）和j（1到p）组合
将dp[n][i][j]累加到结果中  在n个物品中恰好选择i个物品，且这些物品的总价值恰好为j的概率
 *
*有n个元素，每个元素有一个权重a[i]
通过某种随机过程选择元素
dp[i][j][k]表示处理前i个元素，选择了j个元素，累计权重为k的概率
最终计算满足条件的所有状态的概率之和
 *
 *
*我们从前i-1个元素中选择了j个元素（状态dp[i-1][j][k]）
现在考虑第i个元素，它不被选中的概率是 (i-j)/i
因为在前i个位置中，已经有j个位置被选中了，剩下(i-j)个位置未被选中
所以第i个元素不被选中的概率是 (i-j)/i
*我们从前i-1个元素中选择了(j-1)个元素（状态dp[i-1][j-1][k-a[i]]）
第i个元素被选中的概率是 j/i
因为我们要在总共i个位置中选择j个位置，第i个位置被选中的概率就是 j/i
 *
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 66
using namespace std;


int main() {
    fast;
    double dp[N][N][N]; dp[0][0][0] = 1.;
    int n, a[N], p; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    cin >> p;
    for (int i = 1; i <= n; ++i) for (int j = 0; j <= i; ++j) for (int k = 0; k <= p; ++k) {
        dp[i][j][k] += dp[i-1][j][k] * (i - j) / i;
        if (k - a[i] >= 0) dp[i][j][k] += dp[i-1][j-1][k-a[i]] * j / i;
    }
    double ans = 0.;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= p; ++j) ans += dp[n][i][j];
    cout << fixed << setprecision(5) << ans << '\n';
    return 0;
}
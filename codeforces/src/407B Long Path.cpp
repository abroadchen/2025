//
// Created by Psy.C on 2026/2/1.
//
/**
* n：序列长度
pre[N]：前缀数组，存储限制条件
dp[N]：动态规划数组，dp[i]表示前i个位置的方案数
初始化dp[1] = 0
 *
*当前位置的前缀限制是最大值
每次新增2种选择，所以方案数加2
 *
*dp[i-1]*2：前一状态的方案数乘以2（每个方案可扩展2种）
+2：新增的基础方案数
-dp[pre[i-1]]：减去不合法的方案（避免违反前缀限制）
 *
*时间复杂度：O(n)
空间复杂度：O(n)
 *
*后处理一步：dp[n+1]是对dp[n]的最终处理
哨兵节点：n+1位置作为计算的终点
完整统计：包含所有n个元素后的完整方案数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1010
#define mod 1000000007
using namespace std;


int main() {
    fast;
    int n, pre[N]; cin >> n;
    ll dp[N]={};
    for (int i = 1; i <= n; ++i) cin >> pre[i]; dp[1] = 0;
    for (int i = 2; i <= n + 1; ++i) {
        if (pre[i-1] == i-1) dp[i] = (dp[i-1] + 2) % mod; else {
            dp[i] = (dp[i-1]*2%mod + 2 - dp[pre[i-1]]) % mod;
            dp[i] = (dp[i] + mod) % mod;//处理负数情况，确保结果为正
        }
    }
    cout << dp[n+1];//处理完所有n个限制后的最终状态
    return 0;
}
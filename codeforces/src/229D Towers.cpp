//
// Created by Psy.C on 2025/12/10.
//
/*
sum[N]：前缀和数组
dp[N]：动态规划数组，dp[i]表示处理前i个元素的最小代价
lst[N]：记录到达位置i时最后一组的和*
 *
*sum[i] - sum[j] >= lst[j]：当前组的和要大于等于前一组的和（递增约束）
dp[i] >= dp[j] + i - j - 1：找到了更优的解
 *i - j - 1表示从位置j+1到位置i需要添加的分隔符数量
 *
 *
 *从前驱状态（位置j）转移到当前状态（位置i）
 *
 *O(n²)：两层嵌套循环
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 5010
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    int sum[N], dp[N], lst[N];
    for (int i = 1, a; i <= n; ++i) {
        cin>>a;
        sum[i] = sum[i-1]+a;
        dp[i] = lst[i] = 1<<30;//1073741824
    }
    for (int i = 1; i <= n; ++i) for (int j = 0; j < i; ++j) {
        if (sum[i] - sum[j] >= lst[j] && dp[i] >= dp[j] + i - j - 1) {
            dp[i] = dp[j] + i - j - 1;
            if (lst[i] > sum[i] - sum[j]) lst[i] = sum[i] - sum[j];
        }
    }
    cout << dp[n] << '\n';
    return 0;
}
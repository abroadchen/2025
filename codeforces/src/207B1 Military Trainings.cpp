//
// Created by Psy.C on 2025/12/6.
//
/*
 *
*从max(0, i - a[i])到i-1的范围内寻找最优前驱节点j
从j跳到i需要一步，所以是dp[j] + 1
取所有可能转移中的最小值更新dp[i]
 *
 *时间复杂度为O(n³)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000000
using namespace std;

constexpr int inf = 1e7;
int a[N], dp[N];

int main() {
    fast;
    int n; cin>>n;
    ll ans = 0;
    for (int i = 0; i < n; ++i) cin>>a[i];
    for (int k = 0; k < n; ++k) {
        dp[0] = 0;//起点距离为0
        for (int i = 1; i < n; ++i) {
            dp[i] = inf;//当前位置的dp值初始化为无穷大
            for (int j = max(0, i - a[i]); j < i; ++j)
                dp[i] = min(dp[j] + 1, dp[i]);
        }
        ans += dp[n-1];//到达最后一个位置的最短距离累加到总答案中
        for (int i = n; i > 0; --i) a[i] = a[i - 1];//数组元素向右循环移动一位
        a[0] = a[n];//原来最后的元素放到开头
    }
    cout << ans;
    return 0;
}
//
// Created by Psy.C on 2026/2/4.
//
/**
* 对于异或前缀和，有一个重要的周期性模式：

dp[4k] = 4k
dp[4k+1] = 1
dp[4k+2] = 4k+3
dp[4k+3] = 0
 *
*预处理：O(N)，建立前缀和数组
主计算：O(n)，循环n-1次
总体：O(N)，其中N是最大可能值
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
using namespace std;


int main() {
    fast;
    int dp[N];
    for (int i = 1; i < N; ++i) dp[i] = dp[i-1]^i;//从1到i的所有整数的异或和
    int n; cin >> n;
    int ans = 0;
    for (int i = 0, p; i < n; ++i) {
        cin >> p;
        ans = ans^p;//对角线元素（i^i=0)
    }
    for (int i = 2; i <= n; ++i) {
        const int r = n % i;
        if (const int div = n / i; div&1) ans = ans^dp[i-1];//循环节
        ans = ans^dp[r];//将剩余部分异或到结果中
    }
    cout << ans << '\n';
    return 0;
}
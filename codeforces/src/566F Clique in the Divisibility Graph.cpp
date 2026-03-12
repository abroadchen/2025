//
// Created by Psy.C on 2026/3/12.
//
/**
dp[i]表示以数字i结尾的最长倍数序列长度
遍历数组中的每个元素
x = a[i]: 当前处理的数字
倍数更新循环: j从2开始，遍历x的所有倍数
x*j是x的倍数
dp[x*j] = max(dp[x*j], dp[x] + 1): 如果x*j存在，更新其最长序列长度
dp[x]++: 单独处理数字x本身（以x结尾的长度至少为1）
ans = max(ans, dp[x]): 更新全局最大值

设数组中最大值为M：
外层循环：O(n)
内层循环：对于每个a[i]，循环次数约为 M/a[i]
总体复杂度：O(M log M)，因为 ∑(M/a[i]) ≈ M × (∑1/a[i]) ≤ M × ln(M)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;

int n, a[N], mx, dp[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i], mx = max(mx, a[i]);
    for (int i = 1, x; i <= n; ++i) {
        x = a[i];
        for (int j = 2; j <= mx/x; ++j)
            dp[x*j] = max(dp[x*j], dp[x] + 1);
        dp[x]++;
        ans = max(ans, dp[x]);
    }
    cout << ans;
    return 0;
}
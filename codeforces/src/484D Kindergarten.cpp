//
// Created by Psy.C on 2026/2/17.
//
/**
pre始终指向最近的极值点
在每个位置i，可以选择从pre-1或pre转移过来
只有遇到新的极值点才更新pre

时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+7;
int n;
ll dp[N], a[N];

int main() {
    fast;
    cin >> n; dp[0] = 0ll;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; dp[i] = 0ll;
    }
    for (int i = 2, pre = 1; i <= n; ++i) {//pre: 前一个关键位置（极值点）
        dp[i] = max(dp[pre-1] + abs(a[i] - a[pre]),
            dp[pre] + abs(a[i] - a[pre+1]));
        if (a[i-1] <= a[i] && a[i] >= a[i+1]) pre = i;//局部最大值
        if (a[i-1] >= a[i] && a[i] <= a[i+1]) pre = i;//局部最小值
    }
    cout << dp[n] << '\n';
    return 0;
}
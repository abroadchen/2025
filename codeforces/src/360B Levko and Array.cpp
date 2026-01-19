//
// Created by Psy.C on 2026/1/19.
//
///O(n² × log(max_value))，其中n²来自DP过程，log(max_value)来自二分搜索
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2005
using namespace std;

int n, a[N], dp[N], k;
bool ok(const int x) {//给定阈值x是否可行
    for (int i = n; i > 0; --i) {
        dp[i] = n - i - 1;//从位置i到最后位置的"代价"
        for (int j = i + 1; j <= n; ++j)//从后面的位置j转移
            if (abs(a[j] - a[i]) <= x * 1ll * (j - i))//从i到j的"成本"是否在允许范围内 变化率
                dp[i] = min(dp[i], dp[j] + j - i - 1);//选择最优转移方案
        if (dp[i] + i <= k) return true;//从位置i开始的最优解满足约束
    }
    return false;
}

int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int l = 0, r = 2e9;
    while (l < r) {
        if (const int mid = l + ((r - l) >> 1); ok(mid)) r = mid; else l = mid + 1;
    }
    cout << r;//最小可行阈值
    return 0;
}
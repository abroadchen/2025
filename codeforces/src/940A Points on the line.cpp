//
// Created by Psy.C on 2026/10/17.
//
/**
N=105：元素上限；inf：极小值用（这里负无穷取 -0x3f3f3f3f）；n：元素个数；d：阈值；a[N]：数组
读入 n、d 和数组 a。
sort(a, a+n)：原地升序排序。
ans = -inf：记录能保留的最长连续子段长度，初值负无穷。
双重循环枚举 i（左端点）、j（右端点）：
条件 a[j]-a[i] <= d：排序后 a[j] ≥ a[i]，这个差就是该连续子段 [i..j] 的最大值与最小值之差。只要这个"跨度 ≤ d"，这段元素就"相互差距可控、能同时保留/分组"。
满足则 ans = max(ans, j-i+1)：更新最长满足条件的连续段长度（元素个数 = j-i+1）。
输出 n - ans：总元素数减去最大可保留段长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 105, inf = 0x3f3f3f3f;

int n, d, a[N];
int main() {
    fast;
    cin >> n >> d;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    int ans = -inf;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (a[j] - a[i] <= d)
                ans = max(ans, j-i+1);
    cout << n - ans << '\n';
    return 0;
}
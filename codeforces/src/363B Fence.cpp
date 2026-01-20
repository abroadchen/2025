//
// Created by Psy.C on 2026/1/19.
//
/**
* 从位置1开始滑动窗口（窗口左端点）
i + k - 1 < n：确保窗口不越界
sum -= a[i-1]：移除窗口左边的元素
sum += a[i+k-1]：添加窗口右边的新元素
i+k-1：当前窗口的右端点
如果当前窗口和更小，更新最小和mn和索引idx

时间复杂度
O(n)：只需要遍历数组一次
空间复杂度
O(n)：存储输入数组
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000006
using namespace std;


int main() {
    fast;
    int n, k, a[N], idx = 0; cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    ll sum = 0;
    for (int i = 0; i < k; ++i) sum += a[i];
    ll mn = sum;
    for (int i = 1; i + k - 1 < n; ++i) {
        sum -= a[i-1];
        sum += a[i+k-1];
        if (sum < mn) { idx = i; mn = sum; }
    }
    cout << idx + 1 << '\n';
    return 0;
}
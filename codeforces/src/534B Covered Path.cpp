//
// Created by Psy.C on 2026/3/4.
//
/**
v1: 第一个速度的初始值
v2: 第二个速度的初始值
t: 总时间步数
d: 每个时间步的最大速度变化量
d1[N]: 从初始速度v1开始递增的速度数组
d2[N]: 从末尾速度v2开始向前递增的速度数组

将d1[1]初始化为v1（第1时刻的最高速度）
从第2时刻开始，每个时刻的最大速度比前一时刻多d
这代表从初始速度v1开始，每步最多增加d的速度上限
将d2[t]初始化为v2（第t时刻的最高速度）
从第t-1时刻开始向前，每个时刻的最大速度比后一时刻多d
这代表从末尾速度v2开始，向前每步最多增加d的速度上限
遍历每个时间步
对于每个时间步i，取正向和反向计算出的速度上限的较小值
累加所有时间步的速度值得到最大总距离
时间复杂度为O(t)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;
int v1, v2, t, d, d1[N], d2[N];
int main() {
    fast;
    cin >> v1 >> v2 >> t >> d;
    d1[1] = v1;
    for (int i = 2; i <= t; ++i) d1[i] = d1[i-1] + d;
    d2[t] = v2;
    for (int i = t-1; i >= 1; --i) d2[i] = d2[i+1] + d;
    int ans = 0;
    for (int i = 1; i <= t; ++i) ans += min(d1[i], d2[i]);
    cout << ans << '\n';
    return 0;
}
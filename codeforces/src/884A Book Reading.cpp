//
// Created by Psy.C on 2026/10/8.
//
/**
n：天数。
m：还需要完成的目标总"秒数"（或剩余任务量）。
t[i]：第 i 天当天已经占用的秒数
每天有 86400 秒。
第 d 天能投入到目标任务的秒数 = 86400 - t[d]（当天被其他事占用了 t[d] 秒）。
从第 0 天开始逐天累减 m，直到 m <= 0（任务完成）或天数用尽（d == n）。
输出 d：即完成任务时已经过了多少天（下标从 0 开始，输出的是"第 d+1"天完成的概念，但代码直接输出循环计数器 d）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
int n, m, t[N];
int main() {
    fast;
    while (cin >> n >> m) {
        for (int i = 0; i < n; ++i) cin >> t[i];
        int d = 0;
        while (m > 0 && d < n) {
            m -= 86400 - t[d];
            d++;
        }
        cout << d << '\n';
    }
    return 0;
}
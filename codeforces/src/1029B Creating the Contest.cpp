//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
n：数的个数；pre：上一个数；d：当前数；
cnt：当前连续段的长度；mx：历史最长连续段长度
从第二个数开始逐一读入，判断 d <= 2*pre：
满足 → 当前段长度 cnt+1，并更新 mx；
不满足 → 段断掉，cnt 重置为 1。
每步把 pre 更新为当前值，继续向后
若 mx == -1（理论上不会出现，因初始为 1 且至少有一个段）输出 1，否则输出最长段 mx。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, pre, d, cnt(1), mx(1);
int main() {
    fast;
    cin >> n >> pre;//先读第一个数作为 pre
    for (int i = 0; i < n-1; i++) {
        cin >> d;//读下一个数
        if (d <= 2*pre) {//当前数 ≤ 上一数的2倍 → 可接续
            cnt++;
            mx = max(mx, cnt);
        } else cnt = 1;//否则断开，重置段长
        pre = d;//更新 pre
    }
    if (mx == -1) cout << "1\n"; else cout << mx << '\n';
    return 0;
}
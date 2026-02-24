//
// Created by Psy.C on 2026/2/23.
//
/**
cur表示当前选择的起始位置
这行代码确保下一个选择的位置至少比当前区间左端点小x
在当前区间[l,r]中，从位置cur开始到r结束，共有(r-cur+1)个可选择的点
将cur更新为当前区间的右端点+1，为处理下一个区间做准备
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, x;
int main() {
    fast;
    cin >> n >> x;
    int ans = 0;
    for (int i = 0, cur = 1, l, r; i < n; ++i) {
        cin >> l >> r;
        while (cur + x <= l) cur += x;//满足最小间隔约束
        ans += r - cur + 1;
        cur = r + 1;//处理区间的连续性
    }
    cout << ans << '\n';
    return 0;
}
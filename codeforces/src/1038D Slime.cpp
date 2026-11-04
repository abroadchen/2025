//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
读入所有数，同时累加绝对值之和 ans，并记录最小、最大值
只有一个数时，结果就是它本身（没有相邻运算，直接输出）
两个数时，结果是两者的绝对值差 |a-b|
若最小值 > 0（全为正值）：把 ans 减去 2*最小值。
若最大值 < 0（全为负值）：把 ans 减去 2*|最大值|。
有正有负时，ans 保持不变
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 5e5+5, inf = 0x3f3f3f3f;

int n;
ll pre[N];
int main() {
    fast;
    cin >> n;
    ll mn = inf, mx = -inf, ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> pre[i];
        ans += abs(pre[i]);
        mn = min(mn, pre[i]); mx = max(mx, pre[i]);
    }
    if (n == 1) { cout << pre[0] << '\n'; return 0; }
    if (n == 2) {
        cout << max(pre[0]-pre[1], pre[1]-pre[0]) << '\n';
        return 0;
    }
    if (mn > 0) ans -= 2*mn;
    else if (mx < 0) ans -= 2*abs(mx);
    cout << ans << '\n';
    return 0;
}
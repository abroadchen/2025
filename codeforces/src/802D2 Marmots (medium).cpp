//
// Created by Psy.C on 2026/9/18.
//
/**
s：总和 → 用于算均值。
mx：最大值。
mn：最小值
x：均值。
cnt：落在 [x/2, 3x/2]（即 |a[i]-x| <= x/2）内的元素个数。
若 cnt > N*0.75（即偏离均值的元素占比超过 75%，聚集度足够高）→ 输出 round(x)（四舍五入后的均值）。
否则 → 输出 (mx+mn)/2（最大值与最小值的中点，即"中宽值/中点估计"）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 250;
int a[N+5];
int main() {
    fast;
    int q; cin >> q;
    while (q--) {
        int s = 0, mx = INT_MIN, mn = INT_MAX;
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
            if (a[i] > mx) mx = a[i];
            if (a[i] < mn) mn = a[i];
            s += a[i];
        }
        double x = s/250.0;
        int cnt = 0;
        for (int i = 0; i < N; ++i)
            if (fabs(a[i]-x) <= x/2) cnt++;
        if (cnt > N*0.75) cout << int(round(x)) << '\n';
        else cout << int((mx+mn)/2) << '\n';
    }
    return 0;
}
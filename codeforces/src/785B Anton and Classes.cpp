//
// Created by Psy.C on 2026/9/13.
//
/**
a1：第一组线段右端点最大值（初始 0）
b1：第一组线段左端点最小值（初始 inf）
a2、b2：第二组同理
每条线段用一对 (a, b) 表示，假设 a 是右端点、b 是左端点？这里其实把它当作 [b, a]（b 左 a 右）：
取所有线段里最大的右端点 a1；
取所有线段里最小的左端点 b1
对第二组同样操作，得到 a2（最大右端点）、b2（最小左端点）
计算两种可能的最大"跨组间距"：
a1 - b2：第一组最大右端点 − 第二组最小左端点
a2 - b1：第二组最大右端点 − 第一组最小左端点
取较大者；若 > 0 输出，否则输出 0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int inf = 2e9;
int main() {
    fast;
    int n; cin >> n;
    int a1 = 0, a2 = 0, b1 = inf, b2 = inf;
    for (int i = 0, a, b; i < n; ++i) {
        cin >> a >> b;
        if (a > a1) a1 = a;
        if (b < b1) b1 = b;
    }
    int m; cin >> m;
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        if (a > a2) a2 = a;
        if (b < b2) b2 = b;
    }
    int mx = max(a1-b2, a2-b1);
    if (mx > 0) cout << mx; else cout << "0";
    return 0;
}
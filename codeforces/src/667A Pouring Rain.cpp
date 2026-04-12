//
// Created by Psy.C on 2026/4/12.
//
/**
杯子直径、水的高度、倒水速度、漏水速度
S: 底面积
v1: 有效注水速度（净流入速度）
v2: 漏水速度
ans: 答案（填满杯子所需时间）

半径 = d/2，面积 = π × r² = π × (d/2)²
这里写成d/2.*d/2.*pi是为了确保浮点运算
倒水体积速度 ÷ 底面积 = 水位上升高度速度
总高度 ÷ 净上升速度 = 所需时间

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pi acos(-1.)
using namespace std;

int d, h, v, e;
double S, v1, v2, ans;
int main() {
    fast;
    cin >> d >> h >> v >> e;
    S = d/2.*d/2.*pi; v1 = v/S, v2 = e; ans = h/(v1-v2);
    if (v1 <= v2 || ans - 10000 > 0.0001)
        cout << "NO\n";
    else
        cout << "YES\n" << ans << '\n';
    return 0;
}
//
// Created by Psy.C on 2025/12/2.
//
/*
*计算两个圆心之间的距离的平方：
使用距离公式：d² = (x1-x2)² + (y1-y2)²
*如果两圆心距离大于等于两半径之和，说明两圆外离或外切：
ans = 圆心距 - 半径1 - 半径2（即两圆之间的最短距离）
*否则如果两半径差的绝对值大于圆心距，说明一圆包含另一圆：
ans = |r1 - r2| - d（即内含时的间隙距离）
 */
#include <iomanip>
#include <iostream>
#include <cmath>
#include <cstdlib>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    double x1, x2, y1, y2, r1, r2, ans = 0;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    double d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    d = sqrt(d);
    if (d >= r1 + r2) ans = d - r1 - r2;
    else if (abs(r1 - r2) > d) ans = abs(r1 - r2) - d;
    cout << fixed << setprecision(18) << ans / 2;
    return 0;
}
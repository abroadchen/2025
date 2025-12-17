//
// Created by Psy.C on 2025/12/16.
//
/*
 *
*y1, y2：可能是平台或墙壁的y坐标
yw：水面或某个水平面的y坐标
xb, yb：球的初始位置坐标
r：球的半径
*a：从y1位置到水面，扣除两个半径的距离
b：从yb位置到水面，扣除一个半径的距离
x：根据相似三角形原理计算的反射点x坐标
l：从(y1+r)到(x, yw-r)的距离
ans：某个临界长度
 *
*计算球从起点到水面反射后能否到达目标区域
通过几何光学的反射定律计算反射点
检查球是否会因为太大而无法通过某个缝隙
 */
#include <iomanip>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    double y1, y2, yw, xb, yb, r;
    cin >> y1 >> y2 >> yw >> xb >> yb >> r;
    const double a = yw - y1 - 2 * r,//上半部分的有效高度
    b = yw - yb - r,//下半部分的有效高度
    x = a * xb / (a + b),//根据相似三角形计算的x坐标
    l = sqrt(x * x + a * a),//斜边长度
    ans = x * (y2 - y1 - r) / l;//某个投影长度
    if (r - ans > 0) cout << "-1" << '\n';
    else cout << fixed << setprecision(10) << x;
    return 0;
}
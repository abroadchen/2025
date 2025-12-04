//
// Created by Psy.C on 2025/12/3.
//
/*
 *x坐标、y坐标、速度v、半径r
 *p(追逐者)、q(被追逐者/圆)、h(中间计算点)、d(原点)
*len: 圆周长
a: 角度
l, r, mid: 二分搜索边界和中点
l1, l2, l3: 距离平方
a1: 夹角
 */
#include <iomanip>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
#define pi acos(-1)
using namespace std;

struct node { db x, y, v, r; } p, q, h, d;
db len, a, l, r, mid, l1, l2, l3, a1;

db dis(const node& u, const node& v) {
    return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
}
bool cross(const node& u, const node& v) {
    const db d1 = fabs(u.x * v.y - v.x * u.y) / dis(u,v);//两圆心连线到原点的距离
    if (a1 < 1e-10 || d1 - q.r > -1e-10) return true;//夹角接近0或距离差接近0
    return false;
}

bool ok(const db t) {//在时间t内能否追上
    const db x = p.v * t + a; db t1;//追逐者在时间t时的角度位置
    h.x = p.r * cos(x); h.y = p.r * sin(x);//追逐者在时间t时的坐标位置
    l1 = q.x * q.x + q.y * q.y; l2 = h.x * h.x + h.y * h.y;//各点到原点的距离平方和两点间距离平方
    l3 = (q.x - h.x) * (q.x - h.x) + (q.y - h.y) * (q.y - h.y);
    a1 = acos((l1+l2-l3)/(2*sqrt(l1)*sqrt(l2))) - //两个圆之间的夹角差
        acos(q.r/sqrt(l1)) - acos(q.r/sqrt(l2));
    if (cross(q, h)) t1 = dis(h, q);//如果两圆相交，距离就是直线距离
    else t1 = sqrt(l1 - q.r * q.r) + sqrt(l2 - q.r * q.r) +
        len * a1 / (2 * pi);//沿着圆弧的距离之和
    t1 /= q.v;//被追逐者走这段距离所需时间
    if (t1 < t) return false;//如果被追逐者用时少于追逐者用时，说明追不上
    return true;

}

int main() {
    fast;
    while (cin >> p.x >> p.y >> p.v) {
        cin >> q.x >> q.y >> q.v >> q.r;
        len = 2 * pi * q.r;//被追逐者所在圆的周长
        p.r = sqrt(p.x * p.x + p.y * p.y);//追逐者所在圆的半径
        d.x = d.y = 0;//设置原点坐标
        a = acos(p.x / p.r);//追逐者的初始角度（考虑象限）
        if (p.y < 0) a = -a;
        p.v /= p.r;//转换速度为角速度
        l = 0, r = 1e10;
        while (r - l > 1e-12) {//寻找最小追上时间
            mid = (l + r) * 0.5;
            if (ok(mid)) l = mid;
            else r = mid;
        }
        cout << fixed << setprecision(9) << l << '\n';
    }
    return 0;
}
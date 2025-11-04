//
// Created by Psy.C on 2025/11/4.
//
/*
*定义常量N为30（多边形最大顶点数）
定义精度常量eps为1e-8（用于浮点数比较
 *
*符号函数：判断浮点数的符号
如果绝对值小于eps，认为是0
否则返回1(正数)或-1(负数)
*计算两条线段的叉积
用于判断线段是否相交或平行
*计算线段ab和线段cd的交点
如果两线段平行(叉积为0)，返回无效结果
*使用克拉默法则求解线段交点
参数方程：点在线段上的位置参数
*检查交点是否在线段内部(参数在[0,1)范围内)
如果是有效交点，返回交点坐标和true
否则返回无效结果
 *
*读取起点s和终点e
读取多边形顶点数n
读取多边形的所有顶点
*查找起点到终点的线段与多边形边的交点
flag记录找到的交点数量
a,la存储第一个交点及其边索引
b,lb存储第二个交点及其边索引
 *如果交点少于2个，说明线段在多边形外部，直接输出直线距离
 *确保a是离起点更近的交点
 *
 *初始方案：s→a→b→a→b→e（绕多边形一圈）
*方案1：沿多边形顺时针方向绕行
路径：s→a→polygon[la+1]→...→polygon[lb]→b→e
*方案2：沿多边形逆时针方向绕行
路径：s→a→polygon[la]→...→polygon[lb+1]→b→e
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const int N = 30;
const double eps = 1e-8;

struct Point {
    double x, y;
    Point(double x=0, double y=0) : x(x), y(y) {}
    void read() { scanf("%lf%lf", &x, &y); }
};
Point polygon[N];

int sgn(double x) {
    if (fabs(x) < eps) return 0;
    return x > 0 ? 1 : -1;
}

double cross(const Point &a, const Point &b, const Point &c, const Point &d) {
    return (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
}

pair<Point, bool> get(const Point& a, const Point& b, const Point& c, const Point& d) {
    if (sgn(cross(a, b, c, d)) == 0) return {Point(0, 0), false};
    double a1 = b.x - a.x, b1 = c.x - d.x, c1 = c.x - a.x,
    a2 = b.y - a.y, b2 = c.y - d.y, c2 = c.y - a.y,
    t = a1 * b2 - a2 * b1,
    x = (c1 * b2 - c2 * b1) / t, y = (c2 * a1 - c1 * a2) / t;
    if (sgn(x) >= 0 && sgn(x - 1) < 0 &&
        sgn(y) >= 0 && sgn(y - 1) < 0) {
        return {Point(a.x + x * (b.x - a.x), a.y + x * (b.y - a.y)),true};
    } else {
        return {Point(0, 0), false};
    }
}

double dist(const Point &a, const Point &b) {
    return hypot(a.x - b.x, a.y - b.y);
}

int main() {
    Point s, e; s.read(); e.read();
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) polygon[i].read();
    int flag(0), la, lb;
    Point a, b;
    for (int i = 0; i < n; ++i) {
        pair<Point, bool> t = get(s, e, polygon[i], polygon[(i + 1) % n]);
        if (t.second) {
            if (flag == 0) {
                a = t.first;
                la = i;
            } else {
                b = t.first;
                lb = i;
            }
            flag++;
        }
    }
    if (flag < 2) { printf("%.10lf\n", dist(s, e)); return 0; }
    if (sgn(dist(s, a) - dist(s, b)) > 0) { swap(a, b); swap(la, lb); }
    double ans = dist(s, a) + dist(a, b) * 2 + dist(b, e);

    double s1 = dist(s, a) + dist(a, polygon[(la + 1) % n]);
    for (int i = (la + 1) % n; i != lb; i = (i + 1) % n) {
        s1 += dist(polygon[i], polygon[(i + 1) % n]);
    }
    s1 += dist(polygon[lb], b) + dist(b, e);
    ans = min(ans, s1);

    double s2 = dist(s, a) + dist(a, polygon[la]);
    for (int i = la; i != (lb + 1) % n; i = (i + n - 1) % n) {
        s2 += dist(polygon[i], polygon[(i + n - 1) % n]);
    }
    s2 += dist(polygon[(lb + 1) % n], b) + dist(b, e);
    ans = min(ans, s2);
    printf("%.10lf\n", ans);
    return 0;
}
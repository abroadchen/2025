//
// Created by Psy.C on 2025/10/31.
//

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-7;// 定义浮点数比较的精度阈值

struct Point {
    double x, y;
    Point(double x=0.0, double y=0.0): x(x), y(y) {}
};
Point operator+(Point a, Point b) { return Point(a.x+b.x, a.y+b.y); }
Point operator-(Point a, Point b) { return Point(a.x-b.x, a.y-b.y); }
Point operator*(Point a, double b) { return Point(a.x*b, a.y*b); }
Point operator/(Point a, double b) { return Point(a.x/b, a.y/b); }
double operator*(Point a, Point b) { return a.x*b.x+a.y*b.y; }
double det(Point a, Point b, Point c) {//三点构成的向量叉积
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
//点的输入流运算符重载
istream& operator>>(istream& in, Point& a) { return in >> a.x >> a.y; }

// 直线1: 过点a和b 直线2: 过点c和d
Point cp(Point a, Point b, Point c, Point d) {
    double a1 = det(a, c, b), a2 = det(a, b, d);//叉积计算交点参数
    return (c * a2 + d * a1) / (a1 + a2);//参数方程计算交点坐标
}
//符号函数：负数返回-1，正数返回1，零附近返回0
int sgn(double x) { return x < -eps ? -1 : int(x > eps); }


int n, i, ll, rr;//n:点数, i:循环变量, ll,rr:整数范围边界
Point a, b, c, t;//a,b,c:处理中的点, t:临时点
double l, r, y;//l,r:当前有效x范围的左右边界, y:当前水平线y坐标

int main() {

    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    cin >> a >> b;
    //初始化水平扫描线的x范围和y坐标
    l = min(a.x, b.x), r = max(a.x, b.x);//l,r是当前有效x区间
    y = a.y;//初始水平线y坐标
    for (i = 3; i <= n; ++i) {
        cin >> c;//读取下一个点
        if (b.y == c.y) {//如果当前线段是水平的（b和c的y坐标相同）
            //检查这条水平线段是否在整个区域下方
            if (det(c, b, Point(l, y)) < 0) {
                cout << 0 << endl;
                return 0;
            }
        }
        //计算当前水平线y=y与线段bc的交点
        t = cp(Point(l, y), Point(r, y), c, b);
        //如果点(l,y)在线段bc的左侧（即线段bc阻挡了左边界）
        if (sgn(det(c, b, Point(l, y))) < 0) l = max(t.x, l);//更新左边界为交点x坐标和原左边界的较大值
        //如果点(r,y)在线段bc的右侧（即线段bc阻挡了右边界）
        if (sgn(det(c, b, Point(r, y))) < 0) r = min(t.x, r);//更新右边界为交点x坐标和原右边界的较小值
        //更新处理窗口：将当前线段作为新的参考线段
        a = b;
        b = c;
    }
    //计算在最终有效区间[l,r]内的整数点个数
    ll = ceil(l), rr = floor(r);//向上取整得到左边界整数点 向下取整得到右边界整数点
    if (ll > rr) cout << 0 << endl;
    else cout << rr - ll + 1 << endl;
    return 0;
}
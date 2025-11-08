//
// Created by Psy.C on 2025/9/21.
//

#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
typedef double db;

struct Node {
    db x1, y1, x2, y2, k, b;// 起点(x1,y1)，终点(x2,y2)，斜率k，截距b
} a[5];// 存储线段的数组

db pp = 0.001;// 旋转角度
db eps = 1e-7;
db XX, YY;// 存储交点坐标的全局变量
// 对点坐标进行旋转变换
void trans(db& x, db& y, db pp) {
    db xx = x * cos(pp) - y * sin(pp);
    db yy = x * sin(pp) + y * cos(pp);
    x = xx;
    y = yy;
}
// 判断两条线段是否相交（不包括重合情况）
bool cross(Node a, Node b) {
    if (fabs(a.k - b.k) < eps) return false;// 如果两条线段平行，则不相交
    db X = (a.b - b.b) / (b.k - a.k);// 计算两条直线的交点
    db Y = X * a.k + a.b;
    XX = X;// 保存交点坐标
    YY = Y;
    // 检查交点是否在两条线段的范围内
    if (((X > min(a.x1, a.x2) - eps) && (X < max(a.x1, a.x2) + eps)) &&
        ((X > min(b.x1, b.x2) - eps) && (X < max(b.x1, b.x2) + eps)) &&
        ((Y > min(a.y1, a.y2) - eps) && (Y < max(a.y1, a.y2) + eps)) &&
        ((Y > min(b.y1, b.y2) - eps) && (Y < max(b.y1, b.y2) + eps))) {
        return true;
    } else {
        return false;
    }
}
// 判断两条线段是否重合
bool cross2(Node a, Node b) {
    // 如果两条线段斜率和截距都相等，则可能重合
    if ((fabs(a.k - b.k) < eps) && (fabs(a.b - b.b) < eps)) {
        if (min(b.x1, b.x2) - eps < max(a.x1, a.x2)) {// 检查x坐标范围是否有重叠
            return true;
        } else {
            return false;
        }
    }
    return false;
}

int main() {

    for (int i = 1; i <= 3; ++i) {
        scanf("%lf%lf%lf%lf", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
        trans(a[i].x1, a[i].y1, pp);
        trans(a[i].x2, a[i].y2, pp);
        a[i].k = (a[i].y1 - a[i].y2) / (a[i].x1 - a[i].x2);
        a[i].b = a[i].y1 - a[i].x1 * a[i].k;
    }
    // 检查前两条线段是否不重合且不相交，同时第一条和第三条线段也不相交
    if (!cross2(a[1], a[2]) && (!cross(a[1], a[2]) && !cross(a[1], a[3]))) {
        printf("YES\n");
        return 0;
    }

    Node c, d;
    c.k = (-1.0 / (a[3].k)); c.b = a[1].y1 - a[1].x1 * c.k;// 垂直线段
    d.k = a[3].k; d.b = a[3].k * a[1].x1 + a[3].b * 2 - a[1].y1;// 平行线段
    // 计算两条新线段的交点
    db X = (c.b - d.b) / (d.k - c.k), Y = X * c.k + c.b;
    Node t;// 创建临时线段
    t.x1 = X; t.y1 = Y; t.x2 = a[1].x2; t.y2 = a[1].y2;
    t.k = (Y - a[1].y2) / (X - a[1].x2);
    t.b = Y - X * t.k;

    if (!cross(t, a[3])) {// 检查临时线段与第三条线段是否不相交
        printf("NO\n");
        return 0;
    }
    // 更新临时线段
    t.x1 = XX; t.y1 = YY;
    t.x2 = a[1].x1; t.y2 = a[1].y1;
    t.k = (YY - a[1].y1) / (XX - a[1].x1);
    t.b = YY - XX * t.k;

    if (cross(t, a[2])) {// 检查临时线段与第二条线段是否相交
        printf("NO\n");
        return 0;
    }
    // 再次更新临时线段
    t.x2 = a[1].x2; t.y2 = a[1].y2;
    t.k = (t.y1 - a[1].y2) / (t.x1 - a[1].x2);
    t.b = t.y1 - t.x1 * t.k;

    if (cross(t, a[2])) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    return 0;
}
//
// Created by Psy.C on 2026/4/2.
//
/**
计算两圆交点的函数
x: 从圆a圆心到两圆心连线与公共弦交点的距离
z: 交点到中点的距离
u: 从a到b的单位向量
mid: 两交点连线的中点
swap(u.x, u.y), u.x *= -1: 获得垂直向量（旋转90度）

检查半径为mid的圆是否满足条件
创建以p为圆心，mid为半径的圆o
遍历所有其他圆，找到与圆o相交的圆
计算交点，并记录相对于圆o圆心的角度和标识
如果没有交点，返回false
按角度排序
使用栈来匹配交点（类似括号匹配）
如果栈不为空，说明存在不匹配的区间，返回true

读入n和l
设置p点在(l,0)，q点在(-l,0)
读入每个圆的圆心，半径设为该圆心到q点的距离
如果ok(mid)为true，说明半径可以更小，收缩右边界
否则增大左边界

时间复杂度：O(n²log(1/ε))，其中ε是精度要求
 */
#include <bits/stdc++.h>
#define eps 1e-10
using namespace std;
constexpr int N = 2e5+5;
struct pt { double x, y; } p, q;
pt operator+(pt a, pt b) { return {a.x + b.x, a.y + b.y}; }
pt operator-(pt a, pt b) { return {a.x - b.x, a.y - b.y}; }
pt operator*(pt a, double b) { return {a.x * b, a.y * b}; }
double operator*(pt a, pt b) { return a.x * b.y - a.y * b.x; }
double mo(pt a) { return sqrt(a.x * a.x + a.y * a.y); }///计算向量模长
pt unite(pt a) { return a*(1./mo(a)); }///单位化向量
double dist(pt a, pt b) { return mo(b - a); }///计算两点距离
double pang(pt a) { return atan2(a.y, a.x); }/// 计算向量与x轴夹角

struct circle { pt o; double r; } a[N];
pair<pt, pt> intersect(circle a, circle b) {
    double d = dist(a.o, b.o),
    x = (a.r*a.r + d*d - b.r*b.r)/(2*d), z = sqrt(a.r*a.r-x*x);
    pt u = unite(b.o - a.o), mid = a.o + u*x;
    swap(u.x, u.y), u.x *= -1;
    return {mid+u*z, mid-u*z};
}

int n;
bool ok(double mid) {
    circle o = {p, mid};
    vector<pair<double, int>> res;
    int tot = 0;
    for (int i = 1; i <= n; ++i) {
        double d = dist(o.o, a[i].o);
        if (o.r + a[i].r > d && fabs(o.r - a[i].r) < d) {
            tot++;
            auto [fst, snd] = intersect(o, a[i]);
            res.emplace_back(pang(fst - o.o), tot);
            res.emplace_back(pang(snd - o.o), tot);
        }
    }
    if (res.empty()) return false;
    ranges::sort(res);
    static int st[N]; int top = 0;
    for (auto val: res | views::values) {
        if (st[top] == val) top--;
        else st[++top] = val;
    }
    return top != 0;
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = x*10+(ch&15);
    if (f) x = -x;
}

double l;
int main() {
    rd(n), rd(l);
    p = {l, 0}, q = {-l, 0};
    for (int i = 1; i <= n; ++i) {
        rd(a[i].o.x), rd(a[i].o.y);
        a[i].r = dist(a[i].o, q);
    }
    double l = 0, r = dist(p, q);
    while (r - l >= eps) {
        double mid = (l + r) / 2;
        if (ok(mid)) r = mid; else l = mid;
    }
    printf("%.8lf\n", (l+r)/2);
    return 0;
}
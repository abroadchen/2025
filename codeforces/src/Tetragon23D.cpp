//
// Created by Psy.C on 2025/9/19.
//
/*
 *定义测试用例数量T
 *符号函数：判断浮点数x的符号
 *
*重载^运算符：实现向量叉积运算
重载*运算符：实现向量点积运算
 *
*构造函数：通过一个点和角度构造直线
如果角度是π/2(90度)，则构造垂直线 （方向向量为(0,1)）
否则根据角度的正切值构造直线
 *
*计算直线的角度
使用atan2函数计算角度
调整角度范围到[0, π)
 *
*判断两条直线是否平行
通过计算方向向量的叉积是否为0来判断
 *
 *
*判断点p与直线的关系
计算向量(s->p)与向量(s->e)的叉积符号
返回1表示点在直线左侧，2表示右侧，3表示在线上
 *
*判断两直线的相交关系
如果两直线平行，检查第一条直线的起点是否在第二条直线上，返回布尔值
如果不平行，返回2表示相交
 *
*计算两直线的交点
使用参数方程法计算交点坐标
 *
*检查函数：判断三点是否能构成特定几何关系
m1是点m关于点l的对称点
line1是连接l和m1的直线，line2是连接k和l的直线
line3是line1的中垂线，line4是line2的中垂线
 *
*如果两中垂线相交
计算交点b，然后根据对称关系计算其他点
检查四边形abcd是否为凸四边形（通过判断所有相邻边叉积符号是否一致）
 *
 *
 *
 *
 *
 */
#include <cmath>
#include <cstdio>
using namespace std;

static const double eps=1e-2;
static const double pi=acos(-1.0);
int T;

int sgn(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}


struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    void input() { scanf("%lf%lf", &x, &y); }
    Point operator+(const Point &o) const { return Point(x+o.x, y+o.y); }
    Point operator-(const Point &o) const { return Point(x - o.x, y - o.y); }
    double operator^(const Point &o) const { return x * o.y - y * o.x; }
    double operator*(const Point &o) const { return x * o.x + y * o.y; }
} k, l, m, a, b, c, d;

struct Line {
    Point s, e;
    Line() {}
    Line(Point s, Point e) : s(s), e(e) {}

    Line(Point p, double angle) {
        s = p;
        if (sgn(angle - pi / 2) == 0) e = (s + Point(0, 1));
        else e = (s + Point(1, tan(angle)));
    }

    double angle() {
        double k = atan2(e.y - s.y, e.x - s.x);
        if (sgn(k) < 0) k += pi;
        if (sgn(k - pi) == 0) k -= pi;
        return k;
    }

    bool parallel(Line v) { return sgn((e-s)^(v.e-v.s)) == 0; }

    int relation(Point p) {
        int c = sgn((p-s)^(e-s));
        if (c < 0) return 1;
        else if (c > 0) return 2;
        else return 3;
    }
    int linecrossline(Line v) {
        if ((*this).parallel(v)) return v.relation(s) == 3;
        return 2;
    }

    Point crosspoint(Line v) {
        double a1 = (v.e-v.s)^(s-v.s);
        double a2 = (v.e-v.s)^(e-v.s);
        return Point((s.x*a2-e.x*a1)/(a2-a1), (s.y*a2-e.y*a1)/(a2-a1));
    }
};

bool check(Point k, Point l, Point m) {
    Point m1 = Point(2 * l.x - m.x, 2 * l.y - m.y);
    Line line1 = Line(l, m1), line2 = Line(k, l);
    Line line3 = Line(Point((l.x + m1.x)/2, (l.y + m1.y)/2),
        sgn(line1.angle() - pi/2)>=0?line1.angle()-pi/2:line1.angle()+pi/2);
    Line line4 = Line(Point((l.x + k.x)/2, (l.y + k.y)/2),
        sgn(line2.angle() - pi/2) >= 0?line2.angle()-pi/2:line2.angle()+pi/2);
    if (line3.linecrossline(line4) == 2) {
        b = line3.crosspoint(line4);
        a = Point(2*k.x-b.x, 2*k.y-b.y);
        c = Point(2*l.x-b.x, 2*l.y-b.y);
        d = Point(2*m.x-c.x, 2*m.y-c.y);
        return sgn((a-b)^(a-c))>0 && sgn((b-c)^(b-d))>0 && sgn((c-d)^(c-a))>0 &&
            sgn((d-a)^(d-b))>0 || sgn((a-b)^(a-c))<0 && sgn((b-c)^(b-d))<0 &&
                sgn((c-d)^(c-a))<0 && sgn((d-a)^(d-b))<0;
    }
    return false;
}

int main() {

    scanf("%d",&T);
    while(T--) {
        k.input(); l.input(); m.input();
        if (sgn((k - l) ^ (k - m)) && (check(k, l, m) || check(m, k, l) || check(l, m, k)))
            printf("YES\n%.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n", a.x,a.y,b.x,b.y,c.x,c.y,d.x,d.y);
        else puts("NO\n");
    }
    
    return 0;
}
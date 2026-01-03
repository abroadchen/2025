/**
 *
* 普通函数通常无法访问类的私有成员
通过 friend 声明后，函数可以访问类的所有成员（包括私有成员）
如果不是友元函数，就需要通过 getter 方法访问
 */

#include <iomanip>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define N 110
#define pi acos(-1)
using namespace std;

struct node {
    double x, y;
    node() = default;
    node(const double x, const double y) : x(x), y(y) {}
    friend node operator+(const node& o1, const node& o2) { return node(o1.x + o2.x, o1.y + o2.y); }
    friend node operator-(const node& o1, const node& o2) { return node(o1.x - o2.x, o1.y - o2.y); }
    friend  double operator*(const node& o1, const node& o2) { return o1.x * o2.y - o1.y * o2.x; }
    friend node operator*(const node& o, const double r) { return node(o.x * r, o.y * r); }
    friend node rotate(const node& o, const double a) {//按原点旋转a角度
        return node(o.x * cos(a) - o.y * sin(a), o.x * sin(a) + o.y * cos(a));
    }
} p[N];

struct line {
    node p, v;//p为线上一点，v为方向向量
    line() = default;
    line(const node& o1, const node& o2) : p(o1), v(o2) {}
    friend node get(const line& l1, const line& l2) {
        const node u = l1.p - l2.p;
        const double t = l2.v * u / (l1.v * l2.v);
        return l1.p + l1.v * t;//返回交点坐标
    }
};

int main() {
    fast;
    int n, i; cin >> n;
    if (n <= 4) return cout << "No solution\n", 0;
    node v(-1, 0);//初始化方向向量
    double len = 450.; const double a = 2. * pi / n;//初始长度450，a为圆心角(2π/n)
    for (i = 1; i < n; ++i) {//构建多边形的前n-1个点
        constexpr double d = 0.005;//步长增量
        p[i] = p[i - 1] + v * len;//当前点坐标，从上一点沿v方向移动len距离
        len += d;//长度递增
        v = rotate(v, -a);//将方向向量逆时针旋转a角度(负号表示逆时针)
    }
    //最后一个点，为从p[n-1]出发方向为v的直线与x轴的交点
    p[n] = get(line(p[n-1], v), line(node(0, 0), node(1, 0)));
    for (i = n; i; --i) cout << fixed << setprecision(10) << p[i].x << ' ' << p[i].y << '\n';
    return 0;
}
//
// Created by Psy.C on 2025/11/16.
//
/*
*N: 最大点数
eps: 浮点数精度误差容忍值
n: 点的数量
m: 平面的数量
 *
*三维点结构体p3：
加法、减法、数乘、除法运算符重载
叉积运算符*（向量叉乘）
点积运算符|（向量点乘）
输入输出流运算符重载
 *
*sq(): 计算向量的平方长度（点积）
mag(): 计算向量的模长
unit(): 计算单位向量
 *
*坐标系结构体co：
o: 原点
dx, dy, dz: 三个坐标轴的单位向量
构造函数：根据三个点建立局部坐标系
pos2d(): 将三维点投影到该坐标系的二维平面上
 *
*圆结构体：
o: 圆心
r: 半径
contains(): 判断点是否在圆内（含边界）
 *
*perp(): 计算向量的垂直向量
cir(): 通过三点确定的圆（外接圆算法）
 *
*对于每个平面ax + by + cz = 0：
找到平面上的三个点来定义坐标系
根据a,b,c的不同情况选择合适的基点
 *
*建立该平面的局部坐标系
将所有三维点投影到该平面上成为二维点
随机打乱点的顺序（用于随机增量算法）
 *
*最小圆覆盖算法（随机增量法）：
初始圆：以第一个点为圆心，半径为0
对每个新点：
如果已在圆内，跳过
否则，以该点为圆心重新开始
检查前面所有点，必要时扩展圆：
两点定圆（直径圆）
三点定圆（外接圆)
 *
 *期望O(n)，最坏情况O(n³)
 */
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>
using namespace std;

const int N = 905;
const double eps = 1e-9;
int n, m;

struct p3 {
    double x, y, z;
    p3 operator+(p3 p) { return {x + p.x, y + p.y, z + p.z}; }
    p3 operator-(p3 p) { return {x - p.x, y - p.y, z - p.z}; }
    p3 operator*(double k) { return {x * k, y * k, z * k}; }
    p3 operator/(double k) { return {x / k, y / k, z / k}; }
    p3 operator*(p3 p) { return {y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x}; }
    double operator|(p3 p) { return x * p.x + y * p.y + z * p.z; }
    friend istream& operator>>(istream& is, p3& p) {
        is >> p.x >> p.y >> p.z;
        return is;
    }
    friend ostream& operator<<(ostream& os, p3& p) {
        os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
        return os;
    }
} x[N];

struct p2 {
    double x, y;
    p2 operator+(p2 p) { return {x + p.x, y + p.y}; }
    p2 operator-(p2 p) { return {x - p.x, y - p.y}; }
    p2 operator*(double k) { return {x * k, y * k}; }
    p2 operator/(double k) { return {x / k, y / k}; }
    double operator*(p2 p) { return x * p.y - y * p.x; }
    double operator|(p2 p) { return x * p.x + y * p.y; }
    friend istream& operator>>(istream& is, p2& p) {
        is >> p.x >> p.y;
        return is;
    }
    friend ostream& operator<<(ostream& os, p2& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};


template<class T>
double sq(T p) { return p|p; }

template<class T>
double mag(T p) { return sqrt(sq(p));}

template<class T>
T unit(T v) { return v / mag(v); }

struct co {
    p3 o, dx, dy, dz;
    co(p3 p, p3 q, p3 r) : o(p) {
        dx = unit(q - p);
        dz = unit(dx * (r - p));
        dy = dz * dx;
    }
    p2 pos2d(p3 p) { return {(p - o)|dx, (p - o)|dy}; }
};

struct circle {
    p2 o; double r;
    circle(p2 o, double r) : o(o), r(r) {}
    bool contains(p2 p) { return mag(o - p) <= r + eps; }
};

p2 perp(p2 v) { return {-v.y, v.x}; }

circle cir(p2 a, p2 b, p2 c) {
    b = b - a; c = c - a;
    p2 o = a + perp(b * sq(c) - c * sq(b)) / (b * c) / 2;
    return circle(o, mag(a - o));
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> x[i];
    for (int i = 0, a, b, c; i < m; ++i) {
        cin >> a >> b >> c;
        vector<p3> res; res.push_back({0, 0, 0});
        if (a != 0) {
            res.push_back({-1. * b / a, 1, 0});
            res.push_back({-1. * c / a, 0, 1});
        } else if (b != 0) {
            res.push_back({1, -1. * a / b, 0});
            res.push_back({0, -1. * c / b, 1});
        } else if (c != 0) {
            res.push_back({1, 0, -1. * a / c});
            res.push_back({0, 1, -1. * b / c});
        }
        co C(res[0], res[1], res[2]);
        vector<p2> p(n);
        for (int i = 0; i < n; ++i) p[i] = C.pos2d(x[i]);
        random_shuffle(p.begin(), p.end());
        circle ans(p[0], 0);
        for (int i = 1; i < n; ++i) {
            if (ans.contains(p[i])) continue;
            ans = circle(p[i], 0);
            for (int j = 0; j < i; ++j) {
                if (ans.contains(p[j])) continue;
                ans = circle((p[i]+p[j])/2, mag(p[i]-p[j])/2);
                for (int k = 0; k < j; ++k) {
                    if (ans.contains(p[k])) continue;
                    ans = cir(p[i], p[j], p[k]);
                }
            }
        }
        cout << setprecision(50) << ans.r << '\n';
    }
    return 0;
}
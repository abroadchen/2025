//
// Created by Psy.C on 2026/2/8.
//

#include <iostream>
#include <cmath>
#include <random>
#define db double
#define N 2005
using namespace std;

inline db sqr(const db x) { return x * x; }

struct node {
    db x, y;
    explicit node(const db x=0, const db y=0) : x(x), y(y) {}
    friend node operator+(const node &a, const node &b) {
        return node(a.x + b.x, a.y + b.y);
    }
    friend node operator-(const node a, const node b) {
        return node(a.x - b.x, a.y - b.y);
    }
    //向量与标量的乘除法
    friend node operator*(const node a, const db b) {
        return node(a.x * b, a.y * b);
    }
    friend node operator/(const node a, const db b) {
        return node(a.x / b, a.y / b);
    }
    friend db det(const node a, const node b) {
        return a.x * b.y - a.y * b.x;
    }
    friend db operator*(const node a, const node b) {
        return a.x * b.x + a.y * b.y;
    }
    friend db dist(const node a, const node b) {
        return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
    }
    void read() {
        db a, b; scanf("%lf%lf", &a, &b);
        x = a; y = b;
    }
} p[N];

int n;
db ans = 0;
inline db get(const node a) {//点a到所有给定点的次近距离
    db mn1 = 1e30, mn2 = 1e30;//mn1: 最近距离，mn2: 次近距离
    for (int i = 1; i <= n; ++i) {
        if (db d = dist(a, p[i]); d < mn1) mn2 = mn1, mn1 = d;
        else mn2 = min(mn2, d);
    }
    if (mn2 > ans) ans = max(ans, mn2);
    return mn2;
}

int w, h;// 矩形区域的宽和高
inline bool ok(const node a) {//点a是否在矩形区域内[0,w]×[0,h]
    return a.x >= 0 && a.x <= w && a.y >= 0 && a.y <= h;
}

const db pi = acos(-1.);
inline void solve() {
    // 随机生成初始点（在矩形内均匀分布）
    auto a = node((rand()%1000)/1000.*(db)w, (rand()%1000)/1000.*(db)h);
    db res = get(a);//初始点的次近距离
    //初始温度设为矩形对角线长度 温度按0.995比例衰减
    for (db T = sqrt((db)w*w+(db)h*h); T > 1e-15; T *= .995) {//模拟退火
        const db ang = rand()%100/100.*2*pi;//随机方向角度
        const node b = a + node(cos(ang) * T, sin(ang) * T);//在随机方向移动距离T
        if (!ok(b)) continue;//新点是否在区域内
        const db cur = get(b);
        if (const db delta = cur - res; delta > 0) a = b, res = cur;//贪心接受更好的解
    }
}

int main() {
    srand(time(0));
    scanf("%d%d%d", &w, &h, &n);
    for (int i = 1; i <= n; ++i) p[i].read();
    constexpr int q = 10;
    for (int i = 1; i <= q; ++i) solve();
    printf("%.15lf\n", ans);
    return 0;
}
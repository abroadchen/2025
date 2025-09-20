//
// Created by Psy.C on 2025/9/20.
//
/*
*点在多边形内判断 _in()：

使用向量叉积计算点到多边形各边的有向面积
如果点在多边形内，这些有向面积之和等于多边形面积
 *
*线段相交计算 cross()：

使用克拉默法则求解两直线交点
判断交点是否在线段范围内
 *
*轨迹检查 check()：

从起点沿某个方向发射射线，找到与多边形的第一个交点
 *
 *检查沿飞机速度方向的射线是否与多边形相交。
 *计算飞机和降落伞速度的组合效果
 *当飞机速度和降落伞速度不平行时的特殊处理
 *
 *自由落体时间 = 飞行高度 / 自由落体速度
 */

#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef long double ld;

const ld eps = 1e-13;

int n, m;
int x[10001], y[10001];
int x1, y1, z1, x2, y2, z2, f;

int _in(ll xx, ll yy) {
    ll sum = 0, rl = 0;
    for (int i = 0; i < n; ++i) {
        sum += abs((x[i] - xx) * (y[i + 1] - yy) - (x[i + 1] - xx) * (y[i] - yy));
        rl += x[i] * y[i + 1] - x[i + 1] * y[i];
    }
    if (sum != abs(rl)) return 0;
    return 1;
}

int cross(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4, ll y4, ld *t, int r1, int r2) {
    ll a = x2 - x1, b = x3 - x4, c = x3 - x1, d = y2 - y1, e = y3 - y4, f = y3 - y1;
    if (a * e - b * d != 0) {
        ll Q = (a * e - b * d), T = (c * e - b * f), S = (a * f - c * d);
        if (Q < 0) { T = -T; S = -S; Q = -Q; }
        int ok = 1;
        if (r1 & 1) ok &= int(T>=0);
        if (r1 & 2) ok &= int(T<=Q);
        if (r2 & 1) ok &= int(S>=0);
        if (r2 & 2) ok &= int(S<=Q);
        if (ok) { *t = (ld)T/Q; return 1; }
    }
    return 0;
}


int check(ll x1, ll y1, ll x2, ll y2, ld *t, int r1, int r2) {
    if (_in(x1, y1)) { *t = 0; return 1; }
    int ok = 0;
    ld nt;
    *t = 1e20;
    for (int i = 0; i < n; ++i) {
        if (cross(x1, y1, x2, y2, x[i], y[i], x[i + 1], y[i + 1], &nt, r1, r2)) {
            *t = min(*t, nt);
            ok = 1;
        }
    }
    return ok;
}


int _in2(ld xx, ld yy) {
    ld sum = 0, rl = 0;
    for (int i = 0; i < n; ++i) {
        sum += fabs((x[i] - xx) * (y[i + 1] - yy) - (x[i + 1] - xx) * (y[i] - yy));
        rl += x[i] * y[i + 1] - x[i + 1] * y[i];
    }
    if (fabs(sum - abs(rl)) > eps) return 0;
    return 1;
}

int cross2(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3, ld x4, ld y4, ld *t, int r1, int r2) {
    ld a = x2 - x1, b = x3 - x4, c = x3 - x1, d = y2 - y1, e = y3 - y4, f = y3 - y1;
    if (a * e - b * d != 0) {
        ld Q = (a * e - b * d), T = (c * e - b * f), S = (a * f - c * d);
        if (Q < 0) { T = -T; S = -S; Q = -Q; }
        int ok = 1;
        if (r1 & 1) ok &= int(T > -eps * Q);
        if (r1 & 2) ok &= int(T < Q * (1 + eps));
        if (r2 & 1) ok &= int(S > -eps * Q);
        if (r2 & 2) ok &= int(S < Q * (1 + eps));
        if (ok) { *t = (ld)T/Q; return 1; }
    }
    return 0;
}


int check2(ld x1, ld y1, ld x2, ld y2, ld *t, int r1, int r2) {
    if (_in2(x1, y1)) { *t = 0; return 1; }
    int ok = 0;
    ld nt;
    *t = 1e20;
    for (int i = 0; i < n; ++i) {
        if (cross2(x1, y1, x2, y2, x[i], y[i], x[i + 1], y[i + 1], &nt, r1, r2)) {
            *t = min(*t, nt);
            ok = 1;
        }
    }
    return ok;
}

int vect(int x1, int y1, int x2, int y2) {
    return x1 * y2 - x2 * y1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
    int X, Y; scanf("%d%d", &X, &Y);
    for (int i = 0; i < n; ++i) { x[i] -= X; y[i] -= Y; }
    x[n] = x[0]; y[n] = y[0];
    scanf("%d%d%d", &x1, &y1, &z1);
    scanf("%d", &f); f = -f;
    scanf("%d%d%d", &x2, &y2, &z2); z2 = -z2;

    int x3 = x1 * z2 + x2 * z1, y3 = y1 * z2 + y2 * z1;
    ld t1 = 1e20, t2 = 1e20, t, tt;

    if (check(0, 0, x1, y1, &t, 1, 3)) {
        check2(x1 * t + x2 * ((z1 * t)/z2), y1 * t + y2 * ((z1 * t)/z2), x1 * t, y1 * t, &tt, 3, 3);
        tt *= ((z1 * t)/f);
        if (t1 > t + eps || fabs(t - t1) < eps && t2 > tt + eps) { t1 = t; t2 = tt; }
    }

    if (check(0, 0, x3, y3, &t, 1, 3)) {
        t *= z2;
        check2(x1 * t + x2 * ((z1 * t)/z2), y1 * t + y2 * ((z1 * t)/z2), x1 * t, y1 * t, &tt, 3, 3);
        tt *= ((z1 * t)/f);
        if (t1 > t + eps || fabs(t - t1) < eps && t2 > tt + eps) { t1 = t; t2 = tt; }
    }

    if (vect(x1, y1, x2, y2) != 0) {
        ld T = 1e20, r;
        for (int i = 0; i < n; ++i)
            if (cross(0, 0, x1, y1, x[i], y[i], x[i] - x2 * z1, y[i] - y2 * z1, &r, 1, 1))
                T = min(T, r);
        if (T < 5e19) {
            ld t = T, tt;
            if (check2(x1 * T + x2 * ((z1 * T)/z2), y1 * T + y2 * ((z1 * T)/z2), x1 * T, y1 * T, &tt, 3, 3)) {
                tt *= ((z1 * T)/f);
                if (t1 > t + eps || fabs(t - t1) < eps && t2 > tt + eps) { t1 = t; t2 = tt; }
            }
        }
    }

    if (t1 > 5e19) printf("-1 -1\n");
    else printf("%.15f %.15f\n", (double)t1, (double)t2);

    return 0;
}
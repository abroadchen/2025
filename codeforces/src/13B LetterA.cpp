//
// Created by Psy.C on 2025/9/15.
//

#include <ios>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const long double eps = 1e-8;
const long double pi = acos(-1);
int sgn(double x) { if (fabs(x) < eps) return 0; return x > 0 ? 1 : -1; }

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    void input() { cin >> x >> y; }
    double distance(Point o) { return hypot(x - o.x, y - o.y); }
    double rad(Point a, Point b) { Point p = *this; return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p))); }
    bool operator==(Point o) const { return sgn(x - o.x) == 0 && sgn(y - o.y) == 0;}
    Point operator-(const Point &o) const { return Point(x - o.x, y - o.y); }
    double operator^(const Point &o) const { return x * o.y - y * o.x; }
    double operator*(const Point &o) const { return x * o.x + y * o.y; }
};

struct Line {
    Point s, e;
    Line() {}
    Line(Point _s, Point _e) : s(_s), e(_e) {}
    void input() { s.input(); e.input(); }
    bool operator==(Line o) { return (s == o.s) && (e == o.e); }

    bool pointonseg(Point o) { return sgn((o - s) ^ (e - s)) == 0 && sgn((o - s) * (o - e)) <= 0; }

    double length() { return s.distance(e); }
    double dispointtoline(Point o) { return fabs((o - s) ^ (e - s)) / length(); }
    double dispointtoseg(Point o) {
        if (sgn((o - s) * (e - s)) < 0 || sgn((o - e) * (s - e)) < 0)
            return min(o.distance(s), o.distance(e));
        return dispointtoline(o);
    }
    double dissegtoseg(Line o) {
        return min(min(dispointtoseg(o.s), dispointtoseg(o.e)), min(o.dispointtoseg(s), o.dispointtoseg(e)));
    }
    Point crosspoint(Line o) {
        double a1 = (o.e - o.s) ^ (s - o.s);
        double a2 = (o.e - o.s) ^ (e - o.s);
        return Point((s.x * a2 - e.x * a1) / (a2 - a1), (s.y * a2 - e.y * a1) / (a2 - a1));
    }


    int segcrossseg(Line v) {
        int d1 = sgn((e - s) ^ (v.s - s));
        int d2 = sgn((e - s) ^ (v.e - s));
        int d3 = sgn((v.e - v.s) ^ (s - v.s));
        int d4 = sgn((v.e - v.s) ^ (e - v.s));
        if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return 2;
        return  (d1 == 0 && sgn((v.s - s) * (v.s - e)) <= 0) ||
                (d2 == 0 && sgn((v.e - s) * (v.e - e)) <= 0) ||
                (d3 == 0 && sgn((s - v.s) * (s - v.e)) <= 0) ||
                (d4 == 0 && sgn((e - v.s) * (e - v.e)) <= 0);
    }
};

bool check(Line l, Line l1, Line l2) {
    if (!l.segcrossseg(l1) || !l.segcrossseg(l2) || !l1.segcrossseg(l2)) return false;
    if ((l1.pointonseg(l.e) && l2.pointonseg(l.s)) || (l1.pointonseg(l.s) && l2.pointonseg(l.e))) {
        if (sgn(l1.dissegtoseg(l2)) == 0) {
            Point P = l1.crosspoint(l2), A = l.s, B = l.e;
            if (l1.e == l2.e) P = l1.e;
            else if (l1.e == l2.s) P = l1.e;
            else if (l1.s == l2.e) P = l1.s;
            else if (l1.s == l2.s) P = l1.s;
            else return false;
            double x, y, xx, yy;
            if (l1.pointonseg(l.e) && l2.pointonseg(l.s)) {
                x = l.e.distance(l1.e), y = l.e.distance(l1.s);
                xx = l.s.distance(l2.e), yy = l.s.distance(l2.s);
            } else {
                x = l.e.distance(l2.e), y = l.e.distance(l2.s);
                xx = l.s.distance(l1.e), yy = l.s.distance(l1.s);
            }
            if (x > y) swap(x, y);
            if (xx > yy) swap(xx, yy);
            return sgn(pi / 2.0 - P.rad(A, B)) >= 0 && sgn(4 * x - y) >= 0 && sgn(4 * xx - yy) >= 0;
        } else return false;
    } else return false;
}

void solve() {
    int o; cin >> o;
    while (o--) {
        Line l[4];
        for (int i = 1; i <= 3; ++i) l[i].input();
        if (!l[3].segcrossseg(l[1]) || !l[3].segcrossseg(l[2]) || !l[1].segcrossseg(l[2])) {cout << "NO" << '\n'; continue;}
        if (check(l[1], l[2], l[3])) {cout << "YES" << '\n'; continue;}
        if (check(l[2], l[1], l[3])) {cout << "YES" << '\n'; continue;}
        if (check(l[3], l[1], l[2])) {cout << "YES" << '\n'; continue;}
        cout << "NO" << '\n';
    }
}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    
    return 0;
}
//
// Created by Psy.C on 2025/9/13.
//


#include <ios>
#include <iostream>
#include <cmath>
#define point complex<double>
using namespace std;
const double eps=1e-13;

struct Point {
    double x,y;
    Point() {}
    Point(double a, double b) { x=a, y=b; }
    void input() { cin >> x >> y; }
    double dist(Point& a) { return hypot(x-a.x, y-a.y); }
};

double ta, tb, AB, AC, BC, AU, UB, UC, lm, rm, w;
Point A, B, C;


double eval(double k) {
    Point U = Point(k * B.x + (1 - k) * C.x, k * B.y + (1 - k) * C.y);
    AU = A.dist(U); UB = U.dist(B); UC = U.dist(C);
    if (AU + UB < ta && AU + UC < tb) return min(ta - UB, tb - UC);

    double l = 0, r = 1;
    while (fabs(l - r) > eps) {
        w = (l + r) * 0.5;
        Point V = Point(w * U.x + (1 - w) * A.x, w * U.y + (1 - w) * A.y);
        if (w * AU + V.dist(B) < ta && w * AU + V.dist(C) < tb) l = w;
        else r = w;
    }
    return (l + r) * 0.5 * AU;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.setf(ios::fixed);
    cout.precision(20);
    cin >> ta >> tb;
    A.input(); C.input(); B.input();
    AB = A.dist(B); AC = A.dist(C); BC = B.dist(C);
    ta += AB + 1e-12; tb += AC + 1e-12;

    if (tb > AB + BC) {
        cout << min(tb, ta + BC);
        return 0;
    }

    double l = 0, r = 1;
    while (fabs(l - r) > eps) {
        lm = (2 * l + r) / 3; rm = (2 * r + l) / 3;
        if (eval(lm) > eval(rm)) r = rm; else l = lm;
    }
    cout << eval((l + r) * 0.5);
    return 0;
}
//
// Created by Psy.C on 2025/9/11.
//


#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

double find_time2(double w, double x, double a, double v) {
    double x2 = (v * v - w * w) / (2 * a);
    if (x2 <= x) {
        double t1 = (x - x2) / v;
        return (v - w) / a + t1;
    }
    double maxv = sqrt(2 * a * x + w * w);
    return (maxv - w) / a;
}


double a, v, l, d, w;

int main() {
    while (~scanf("%lf%lf%lf%lf%lf", &a, &v, &l, &d, &w)) {
        double t = sqrt((2.0 * d) / a);
        double V = a * t;
        V = min(v, V);
        if (V <= w) {
            printf("%.10lf\n", find_time2(0, l, a, v));
            continue;
        }
        double x1 = v * v / (2 * a);
        double x2 = (v * v - w * w) / (2 * a);
        if (x1 + x2 <= d) {
            double t3 = (d - x1 - x2) / v;
            printf("%.10lf\n", v / a + (v - w) / a + t3 + find_time2(w, l - d, a, v));
            continue;
        }
        double v1 = sqrt(a * d + w * w / 2);
        double t1 = v1 / a, t2 = (v1 - w) / a;
        printf("%.10lf\n", t1 + t2 + find_time2(w, l - d, a, v));
    }

    return 0;
}
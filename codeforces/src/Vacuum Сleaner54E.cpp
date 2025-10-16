//
// Created by Psy.C on 2025/10/16.
//

#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 40010;
int n;

class vec {
public:
    double x, y;
    vec() {}
    vec(double dx, double dy) : x(dx), y(dy) {}
    double operator*(const vec& o) const { return x * o.y - y * o.x; }
    double operator^(const vec& o) const { return x * o.x + y * o.y; }
    vec operator-(const vec& o) const { return vec(x - o.x, y - o.y); }
    vec operator/(const double& o) const { return vec(x / o, y / o); }
    double len() { return sqrt(x * x + y * y); }
} p[N];
int nxt(int x) { return (x + 1) % n; }

double solve() {
    double ret(1e18), s(0);
    for (int i = 0, j = 1; i < n; ++i) {
        while (((p[nxt(j)] - p[j]) ^ (p[nxt(i)] - p[i])) > 0) {
            s += fabs((p[j] - p[i]) * (p[nxt(j)] - p[i]));
            j = nxt(j);
        }
        double c = (p[i] - p[j]).len(),
        a = ((p[i] - p[nxt(i)]) * (p[i] - p[j])) / (p[i] - p[nxt(i)]).len(),
        b = sqrt(c * c - a * a);
        ret = min(ret, fabs(fabs(s) - fabs(a * b)));
        s -= fabs((p[j] - p[i]) * (p[nxt(i)] - p[i]));
    }
    return ret / 2;
}


int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
    double ans = solve();
    reverse(p, p + n);
    ans = min(ans, solve());
    printf("%.12lf\n", ans);
    return 0;
}
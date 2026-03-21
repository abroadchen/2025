//
// Created by Psy.C on 2026/3/22.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-7
using namespace std;
constexpr int N = 1e5+5;

struct node { double x, y; } p[N];
double operator*(node a, node b) { return a.x * b.y - b.x * a.y; }
node operator+(node a, node b) { return node(a.x + b.x, a.y + b.y); }
node operator-(node a, node b) { return node(a.x - b.x, a.y - b.y); }
node operator*(node a, double b) { return node(a.x * b, a.y * b); }
double dis(node a, node b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
bool cmp(node a, node b) {
    if (abs((a - p[1])*(b - p[1])) < eps) {
        return dis(p[1], a) < dis(p[1], b);
    }
    return (a - p[1]) * (b - p[1]) > 0;
}
node add(node a, node b, node c, node d) {
    auto x = a - c;
    double y = d*x/(b*d);
    return a + b*y;
}

int main() {
    fast;

    return 0;
}
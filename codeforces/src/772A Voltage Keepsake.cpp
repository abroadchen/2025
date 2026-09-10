//
// Created by Psy.C on 2026/9/9.
//

#include <bits/stdc++.h>
#define ll long long
#define eps 1e-6
using namespace std;
template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, p, *a, *b;
ll s;
void init() {
    rd(n), rd(p);
    a = new int[n+1], b = new int[n+1];
    for (int i = 1; i <= n; ++i) {
        rd(a[i]), rd(b[i]);
        s += a[i];
    }
}

bool check(double mid) {
    double ans = 0.0;
    for (int i = 1; i <= n; ++i)
        if (a[i]*mid >= b[i])
            ans += a[i]*mid - b[i];
    return ans < p*mid;
}

inline int cmp(double x, double y) {
    if (fabs(x - y) < eps) return 0;
    if (x - y < 0) return -1;
    return 1;
}

constexpr ll inf = 1e16;
inline void solve() {
    if (s <= p) { puts("-1"); return; }
    double l = 0, r = inf;
    int cnt = 0;
    while (cmp(l, r) == -1 && cnt < 128) {
        double mid = (l + r) / 2;
        cnt++;
        if (check(mid)) l = mid; else r = mid;
    }
    printf("%.6lf", l);
}

int main() {
    init(); solve();
    return 0;
}
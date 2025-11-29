//
// Created by Psy.C on 2025/11/29.
//

#include <iomanip>
#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-12
#define kb 1.38e-23
using namespace std;

constexpr int N = 45, M = 100, T = 1e4;
int n1, n2, n3, d1, d2, n, a[N], m;
double r1, r2, r3, res, ff;

inline double get() {
    double sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] != 3) continue;
        int x = i;
        if (x > m) x -= m;
        double L3 = x - r3, R3 = x + r3;
        for (int j = 1; j <= n; ++j) {
            if (a[j] == 3) continue;
            int y = j;
            const int t = a[j];
            if (y > m) y -= m;
            if (t == 1) {
                double L1 = y - r1, R1 = y + r1;
                sum += max(0., d1 * (min(R1, R3) - max(L1, L3)));
            } else if (t == 2) {
                double L2 = y - r2, R2 = y + r2;
                sum += max(0., d2 * (min(R2, R3) - max(L2, L3)));
            }
        }
    }
    return res + sum;
}

static mt19937 gen(random_device{}());
inline int mr(const int mx) {
    uniform_int_distribution<int> dis(1, mx);
    return dis(gen);
}
inline double md() {
    uniform_real_distribution<double> dis(0., 1.);
    return dis(gen);
}

inline void f() {
    double t = T;
    if (t > eps) {
        double ans = 0;
        int x = mr(n), y = mr(n);
        while (a[x] == a[y]) x = mr(n), y = mr(n);
        swap(a[x], a[y]);
        const double ret = get();
        if (ret > ans) {
            ans = ret;
            ff = max(ff, ans);
        } else if (md() < exp((ans - ret) / t / kb)) {
            swap(a[x], a[y]);
        } else ans = ret;
        t *= 0.99;
    }
}

int main() {
    fast;
    cin >> n1 >> n2 >> n3;
    cin >> r1; r1 = sqrt(r1 * r1 - 1);
    cin >> r2; r2 = sqrt(r2 * r2 - 1);
    cin >> r3; r3 = sqrt(r3 * r3 - 1);
    cin >> d1 >> d2;
    res = 2 * n1 * r1 * d1 + 2 * n2 * r2 * d2;
    if (n3 == 0) return cout << fixed << setprecision(10) << res, 0;
    n = n1 + n2 + n3;
    for (int i = 1; i <= n; ++i) {
        if (n1) a[i] = 1, n1--;
        else if (n2) a[i] = 2, n2--;
        else if (n3) a[i] = 3, n3--;
    }
    m = n / 2 + 1; n = m * 2;
    shuffle(a + 1, a + n + 1, mt19937(random_device()()));
    for (int i = 1; i <= M; ++i) f();
    cout << fixed << setprecision(10) << ff << '\n';
    return 0;
}
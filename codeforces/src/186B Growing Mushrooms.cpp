//
// Created by Psy.C on 2025/12/1.
//

#include <iomanip>
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
using namespace std;

struct node { double h; int id; } w[N];

int main() {
    fast;
    int n, t1, t2; double k; cin >> n >> t1 >> t2 >> k;
    k /= 100; k = 1 - k;
    for (int i = 1, a, b; i <= n; ++i) {
        cin >> a >> b;
        w[i].h = max((a * t1) * k * 1. + b * t2 * 1.,
            (b * t1) * k * 1. + a * t2 * 1.);
        w[i].id = i;
    }
    sort(w + 1, w + n + 1, [](const node &a, const node &b) {
        if (a.h == b.h) return a.id < b.id;
        return a.h > b.h;
    });
    for (int i = 1; i <= n; ++i) cout << w[i].id << ' ' << fixed <<
        setprecision(2) << w[i].h << '\n';
    return 0;
}
//
// Created by Psy.C on 2026/2/8.
//

#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[510], n, m;

int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    double ans = 0;
    for (int i = 1, x, y, z; i <= m; ++i) {
        cin >> x >> y >> z;
        double t = 1.*(a[x]+a[y])/z;
        ans = max(ans, t);
    }
    cout << fixed << setprecision(15) << ans << '\n';
    return 0;
}
//
// Created by Psy.C on 2026/1/24.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
#define N 1000000
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    const int m = N / k;
    ld a[N+5]={};
    for (int z = 1, y1; z <= n; ++z) {
        cin >> y1;
        ld ans = 0;
        for (int i = 0, y2; i < k; ++i) {
            cin >> y2;
            const ld kk = static_cast<ld>((y2 - y1)) / m;
            for (int t = 0; t <= m; ++t) {
                if (const ld tmp = y1 + kk * t; tmp > a[i*m+t]) {
                    ans += tmp - a[i*m+t];
                    a[i*m+t] = tmp;
                }
            }
            y1 = y2;
        }
        ans /= m;
        cout << ans << '\n';
    }
    return 0;
}
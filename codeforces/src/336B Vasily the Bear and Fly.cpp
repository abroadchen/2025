//
// Created by Psy.C on 2026/1/11.
//

#include <iomanip>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    double m, r; cin >> m >> r;
    double ans = (m * (m + 1) * (m + 2) / 3 - m) * 2;
    ans += (sqrt(2.) - 2) * ((m*m - m) + (m*m - m - (m-1)*2));
    ans /= m*m;
    ans *= r;
    cout << setprecision(7) << ans << '\n';
    return 0;
}